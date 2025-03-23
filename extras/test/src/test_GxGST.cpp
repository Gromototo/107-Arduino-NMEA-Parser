#include <string.h>
#include <string>
#include <catch.hpp>
#include <nmea/GxGST.h>

static nmea::GstData data;

SCENARIO("Extracting satellite system from valid GxGST message", "[GxGST-01]")
{
  WHEN("GPS")
  {
    std::string const GPGST = "$GPGST,123456.789,1.1,2.2,3.3,45.0,0.5,0.6,0.7*41\r\n";
    nmea::GxGST::parse(const_cast<char *>(GPGST.c_str()), data);
    REQUIRE(data.source == nmea::GstSource::GPS);
  }
}

TEST_CASE("Extracting position time from valid GxGST message", "[GxGST-02]")
{
  std::string const GPGST = "$GPGST,123456.789,1.1,2.2,3.3,45.0,0.5,0.6,0.7*41\r\n";
  nmea::GxGST::parse(const_cast<char *>(GPGST.c_str()), data);
  REQUIRE(data.time_utc.hour == 12);
  REQUIRE(data.time_utc.minute == 34);
  REQUIRE(data.time_utc.second == 56);
  REQUIRE(data.time_utc.microsecond == 789);
}

SCENARIO("Extracting RMS deviation from valid GxGST message", "[GxGST-03]")
{
  std::string const GPGST = "$GPGST,123456.789,1.1,2.2,3.3,45.0,0.5,0.6,0.7*41\r\n";
  nmea::GxGST::parse(const_cast<char *>(GPGST.c_str()), data);
  REQUIRE(data.RMS_Deviation == Approx(1.1));
}

SCENARIO("Extracting major/minor axis deviation from valid GxGST message", "[GxGST-04]")
{
  std::string const GPGST = "$GPGST,123456.789,1.1,2.2,3.3,45.0,0.5,0.6,0.7*41\r\n";
  nmea::GxGST::parse(const_cast<char *>(GPGST.c_str()), data);
  REQUIRE(data.MajorAxisDeviation == Approx(2.2));
  REQUIRE(data.MinorAxisDeviation == Approx(3.3));
}

SCENARIO("Extracting orientation from valid GxGST message", "[GxGST-05]")
{
  std::string const GPGST = "$GPGST,123456.789,1.1,2.2,3.3,45.0,0.5,0.6,0.7*41\r\n";
  nmea::GxGST::parse(const_cast<char *>(GPGST.c_str()), data);
  REQUIRE(data.Orient == Approx(45.0));
}

SCENARIO("Extracting lat/lon/alt deviation from valid GxGST message", "[GxGST-06]")
{
  std::string const GPGST = "$GPGST,123456.789,1.1,2.2,3.3,45.0,0.5,0.6,0.7*41\r\n";
  nmea::GxGST::parse(const_cast<char *>(GPGST.c_str()), data);
  REQUIRE(data.LatDeviation == Approx(0.5));
  REQUIRE(data.LonDeviation == Approx(0.6));
  REQUIRE(data.AltDeviation == Approx(0.7));
}

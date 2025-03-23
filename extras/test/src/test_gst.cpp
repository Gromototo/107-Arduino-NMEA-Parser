/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

 #include <catch.hpp>

 #include <nmea/util/gst.h>
 
 /**************************************************************************************
  * TEST CODE
  **************************************************************************************/
 
 TEST_CASE ("Testing 'gst_isGPGST(...)' with valid and invalid GPGST NMEA messages", "[gst_isGPGST-01]")
 {
   WHEN ("a valid GPGST NMEA message")
     REQUIRE (nmea::util::gst_isGPGST("$GPGST") == true);
   WHEN ("a invalid GPGST NMEA message")
     REQUIRE (nmea::util::gst_isGPGST("$GAGST") == false);
 }
 
 TEST_CASE ("Testing 'gst_isGLGST(...)' with valid and invalid GLGST NMEA messages", "[gst_isGLGST-01]")
 {
   WHEN ("a valid GLGST NMEA message")
     REQUIRE (nmea::util::gst_isGLGST("$GLGST") == true);
   WHEN ("a invalid GLGST NMEA message")
     REQUIRE (nmea::util::gst_isGLGST("$GAGST") == false);
 }
 
 TEST_CASE ("Testing 'gst_isGAGST(...)' with valid and invalid GAGST NMEA messages", "[gst_isGAGST-01]")
 {
   WHEN ("a valid GAGST NMEA message")
     REQUIRE (nmea::util::gst_isGAGST("$GAGST") == true);
   WHEN ("a invalid GAGST NMEA message")
     REQUIRE (nmea::util::gst_isGAGST("$GLGST") == false);
 }
 
 TEST_CASE ("Testing 'gst_isGNGST(...)' with valid and invalid GNGST NMEA messages", "[gst_isGNGST-01]")
 {
   WHEN ("a valid GNGST NMEA message")
     REQUIRE (nmea::util::gst_isGNGST("$GNGST") == true);
   WHEN ("a invalid GNGST NMEA message")
     REQUIRE (nmea::util::gst_isGNGST("$GAGST") == false);
 }
 
 TEST_CASE ("Testing 'gst_isGxGST(...)' with valid and invalid G(P|L|A|N)GST NMEA messages", "[gst_isGxGST-01]")
 {
   WHEN ("a valid G(P|L|A|N)GST NMEA message")
   {
     REQUIRE (nmea::util::gst_isGxGST("$GPGST") == true);
     REQUIRE (nmea::util::gst_isGxGST("$GLGST") == true);
     REQUIRE (nmea::util::gst_isGxGST("$GAGST") == true);
     REQUIRE (nmea::util::gst_isGxGST("$GNGST") == true);
   }
   WHEN ("a invalid G(P|L|A|N)GST NMEA message")
     REQUIRE (nmea::util::gst_isGxGST("$GIGST") == false);
 }
 
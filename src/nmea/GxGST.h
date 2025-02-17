/**
 * This software is distributed under the terms of the MIT License.
 * Author: Rodrigue LEITAO--PEREIRA DIAS <rodlpd51@gmail.com>
 * Contributors: https://github.com/107-systems/107-Arduino-NMEA-Parser/graphs/contributors.
 */

#ifndef ARDUINO_NMEA_GXGST_H_
#define ARDUINO_NMEA_GXGST_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include "Types.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace nmea
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class GxGST
{

public:

  static void parse(char * gxgst, GstData & data);

private:

  GxGST() { }
  GxGST(GxGST const &) { }

  enum class ParserState : int
  {
    MessageId,
    UTCPositionFix,
    RMS_Deviation,
    MajorAxisDeviation,
    MinorAxisDeviation,
    Orient,
    LatDeviation,
    LonDeviation,
    AltDeviation,
    Checksum,
    Done
  };

  static ParserState handle_MessageId                    (char const * token, GgaSource & source);
  static ParserState handle_UTCPositionFix               (char const * token, Time & time_utc);
  static ParserState handle_RMS_Deviation                (char const * token, float & RMS_Deviation);
  static ParserState handle_MajorAxisDeviation           (char const * token, float & MajorAxisDeviation);
  static ParserState handle_MinorAxisDeviation           (char const * token, float & MinorAxisDeviation);
  static ParserState handle_Orient                       (char const * token, float & Orient);
  static ParserState handle_LatDeviation                 (char const * token, float & LatDeviation);
  static ParserState handle_LonDeviation                 (char const * token, float & LonDeviation);
  static ParserState handle_AltDeviation                 (char const * token, float & AltDeviation);
  static ParserState handle_Checksum                     (char const * token);
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* nmea */

#endif /* ARDUINO_NMEA_GXGST_H_ */

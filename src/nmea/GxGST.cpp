/**
 * This software is distributed under the terms of the MIT License.
 * Author: Rodrigue LEITAO--PEREIRA DIAS <rodlpd51@gmail.com>
 * Contributors: https://github.com/107-systems/107-Arduino-NMEA-Parser/graphs/contributors.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "GxGST.h"

#include <string.h>

#ifdef ARDUINO_ARCH_ESP32
#  include <stdlib_noniso.h>
#endif

#ifdef ARDUINO_ARCH_RENESAS
extern "C" char * _EXFUN(strsep,(char **, const char *));
#endif

#include "util/gst.h"
#include "util/common.h"
#include "util/checksum.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace nmea
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void GxGST::parse(char * gxgst, GstData & data)
{
  ParserState state = ParserState::MessageId;

  /* Replace the '*' sign denoting the start of the checksum
   * with a ',' in order to be able to tokenize all elements
   * including the one before the checksum.
   */
  *strchr(gxgst, '*') = ',';

  for (char * token = strsep(&gxgst, ",");
       token != nullptr;
       token = strsep(&gxgst, ","))
  {
    ParserState next_state = state;

    switch(state)
    {
    case ParserState::MessageId:                     next_state = handle_MessageId                    (token, data.source);               break;
    case ParserState::UTCPositionFix:                next_state = handle_UTCPositionFix               (token, data.time_utc);             break;
    case ParserState::RMS_Deviation:                 next_state = handle_RMS_Deviation                (token, data.RMS_Deviation);        break;
    case ParserState::MajorAxisDeviation:            next_state = handle_MajorAxisDeviation           (token, data.MajorAxisDeviation);   break;
    case ParserState::MinorAxisDeviation:            next_state = handle_MinorAxisDeviation           (token, data.MinorAxisDeviation);   break;
    case ParserState::Orient:                        next_state = handle_Orient                       (token, data.Orient);               break;
    case ParserState::LatDeviation:                  next_state = handle_LatDeviation                 (token, data.LatDeviation);         break;
    case ParserState::LonDeviation:                  next_state = handle_LonDeviation                 (token, data.LonDeviation);         break;
    case ParserState::AltDeviation:                  next_state = handle_AltDeviation                 (token, data.AltDeviation);         break;
    case ParserState::Checksum:                      next_state = handle_Checksum                     (token);                            break;
    case ParserState::Done:                                                                                                               break;
    };

    state = next_state;
  }
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

GxGST::ParserState GxGST::handle_MessageId(char const * token, GstSource & source)
{
  if (util::gst_isGPGST(token))
    source = GstSource::GPS;
  else if (util::gst_isGLGST(token))
    source = GstSource::GLONASS;
  else if (util::gst_isGAGST(token))
    source = GstSource::Galileo;
  else if (util::gst_isGNGST(token))
    source = GstSource::GNSS;

  return ParserState::UTCPositionFix;
}

GxGST::ParserState GxGST::handle_UTCPositionFix(char const * token, Time & time_utc)
{
  if (strlen(token))
    util::parseTime(token, time_utc);
  else
    time_utc = INVALID_TIME;

  return ParserState::RMS_Deviation;
}

GxGST::ParserState GxGST::handle_RMS_Deviation(char const * token, float & RMS_Deviation)
{
  if (strlen(token))
    RMS_Deviation = atof(token);
  else
  RMS_Deviation = NAN;

  return ParserState::MajorAxisDeviation;
}

GxGST::ParserState GxGST::handle_MajorAxisDeviation(char const * token, float & MajorAxisDeviation)
{
  if (strlen(token))
    MajorAxisDeviation = atof(token);
  else
    MajorAxisDeviation = NAN;

  return ParserState::MinorAxisDeviation;
}

GxGST::ParserState GxGST::handle_MinorAxisDeviation(char const * token, float & MinorAxisDeviation)
{

  if (strlen(token))
    MinorAxisDeviation = atof(token);
  else
    MinorAxisDeviation = NAN;

  return ParserState::Orient;
}

GxGST::ParserState GxGST::handle_Orient(char const * token, float & Orient)
{
  if (strlen(token))
    Orient = atof(token);
  else
    Orient = NAN;

  return ParserState::LatDeviation;
}

GxGST::ParserState GxGST::handle_LatDeviation(char const * token, float & LatDeviation)
{
  if (strlen(token))
    LatDeviation = atof(token);
  else
    LatDeviation = NAN;

  return ParserState::LonDeviation;
}

GxGST::ParserState GxGST::handle_LonDeviation(char const * token, float & LonDeviation)
{
  if (strlen(token))
    LonDeviation = atof(token);
  else
    LonDeviation = NAN;

  return ParserState::AltDeviation;
}

GxGST::ParserState GxGST::handle_AltDeviation(char const * token, float & AltDeviation)
{

  if (strlen(token))
  AltDeviation = atof(token);
else
  AltDeviation = NAN;

  return ParserState::Checksum;
}

GxGST::ParserState GxGST::handle_Checksum(char const * /* token */)
{
  return ParserState::Done;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* nmea */

/**
 * This software is distributed under the terms of the MIT License.
 * Author: Rodrigue LEITAO--PEREIRA DIAS <rodlpd51@gmail.com>
 * Contributors: https://github.com/107-systems/107-Arduino-NMEA-Parser/graphs/contributors.
 */

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include "gst.h"

#include <string.h>
#include <stdlib.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace nmea
{

namespace util
{

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

bool gst_isGPGST(char const * nmea)
{
  return (strncmp(nmea, "$GPGST", 6) == 0);
}

bool gst_isGLGST(char const * nmea)
{
  return (strncmp(nmea, "$GLGST", 6) == 0);
}

bool gst_isGAGST(char const * nmea)
{
  return (strncmp(nmea, "$GAGST", 6) == 0);
}

bool gst_isGNGST(char const * nmea)
{
  return (strncmp(nmea, "$GNGST", 6) == 0);
}



bool gst_isGxGST(char const * nmea)
{
  return (gst_isGPGST(nmea) || gst_isGLGST(nmea) || gst_isGAGST(nmea) || gst_isGNGST(nmea));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* util */

} /* nmea */

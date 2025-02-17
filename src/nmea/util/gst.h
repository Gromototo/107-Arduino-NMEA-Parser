/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2020 LXRobotics.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/107-Arduino-NMEA-Parser/graphs/contributors.
 */

#ifndef ARDUINO_NMEA_UTIL_GST_H_
#define ARDUINO_NMEA_UTIL_GST_H_

/**************************************************************************************
 * INCLUDES
 **************************************************************************************/

#include "../Types.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace nmea
{

namespace util
{

/**************************************************************************************
 * FUNCTION DECLARATION
 **************************************************************************************/

bool  gst_isGPGST(char const * nmea);
bool  gst_isGLGST(char const * nmea);
bool  gst_isGAGST(char const * nmea);
bool  gst_isGNGST(char const * nmea);
bool  gst_isGxGST(char const * nmea);

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* util */

} /* nmea */

#endif /* ARDUINO_NMEA_UTIL_GST_H_ */

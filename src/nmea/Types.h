/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2020 LXRobotics.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/107-Arduino-NMEA-Parser/graphs/contributors.
 */

 #ifndef ARDUINO_MTK3333_NMEA_TYPES_H_
 #define ARDUINO_MTK3333_NMEA_TYPES_H_
 
 /**************************************************************************************
  * INCLUDE
  **************************************************************************************/
 
 #include <time.h>
 #include <math.h>
 
 /**************************************************************************************
  * NAMESPACE
  **************************************************************************************/
 
 namespace nmea
 {
 
 /**************************************************************************************
  * TYPEDEF
  **************************************************************************************/
 
 typedef struct
 {
   int hour;
   int minute;
   int second;
   int microsecond;
 } Time;
 
 typedef struct
 {
   int day;
   int month;
   int year;
 } Date;
 
 enum class RmcSource
 {
   Unknown, GPS, Galileo, GLONASS, GNSS, BDS
 };
 
 typedef struct
 {
   RmcSource source;
   Time time_utc;
   bool is_valid;
   float latitude;
   float longitude;
   float speed;
   float course;
   float magnetic_variation;
   Date date;
 } RmcData;
 
 enum class FixQuality
 {
     Invalid = 0,   // Pas de fix
     GPS_Fix = 1,   // Fix standard
     DGPS_Fix = 2,  // Fix différentiel (SBAS/WAAS)
     RTK_Fixed = 4, // Fix RTK centimétrique
     RTK_Float = 5, // RTK flottant
     Dead_Reckoning = 6 // Position estimée
 };
 
 typedef RmcSource GgaSource;
 typedef RmcSource GstSource;
 
 typedef struct
 {
   GgaSource source;
   Time time_utc;
   float latitude;
   float longitude;
   FixQuality fix_quality;
   int num_satellites;
   /* HDOP = Horizontal dilution of position */
   float hdop;
   /* Antenna altitude above/below mean sea level (Geoid). */
   float altitude;
   /* Geoidal separation N
    *  where
    *    h = N + H
    *  and
    *    h = height above ellipsoid
    *    H = elevation, orthometric height
    *    N = geoidal separation (some books call this the geoidal height)
    */
   float geoidal_separation;
   
   /* Age in seconds since last update from differential reference station. */
   int dgps_age;
 
   /* DGPS station id - 4 bytes. */
   char dgps_id[4];
 } GgaData;
 
 typedef struct
 {
   GstSource source;
   Time time_utc;
 
   //RMS value of the standard deviation of the range inputs 
   //to the navigation process.
   float RMS_Deviation;
 
   //Standard deviation of semi-minor axis of error ellipse
   float MajorAxisDeviation;
   float MinorAxisDeviation;
 
   //Orientation of semi-major axis of error ellipse.
   float Orient;
 
   //Standart Deviation
   float LatDeviation;
   float LonDeviation;
   float AltDeviation;
 
 } GstData;
 /**************************************************************************************
  * CONST
  **************************************************************************************/
 
 Time    const INVALID_TIME = {-1, -1, -1, -1};
 Date    const INVALID_DATE = {-1, -1, -1};
 RmcData const INVALID_RMC  = {RmcSource::Unknown, INVALID_TIME, false, NAN, NAN, NAN, NAN, NAN, INVALID_DATE};
 GgaData const INVALID_GGA  = {GgaSource::Unknown, INVALID_TIME, NAN, NAN, FixQuality::Invalid, -1, NAN, NAN, NAN, -1, {0}};
 GstData const INVALID_GST  = {GstSource::Unknown, INVALID_TIME, NAN, NAN, NAN, NAN, NAN, NAN, NAN};
 
 /**************************************************************************************
  * FUNCTION DECLARATION
  **************************************************************************************/
 
 bool   isValid         (Date const & date);
 bool   isValid         (Time const & time);
 bool   isValid         (Date const & date, Time const & time);
 time_t toPosixTimestamp(Date const & date, Time const & time);
 
 /**************************************************************************************
  * NAMESPACE
  **************************************************************************************/
 
 } /* nmea */
 
 #endif /* ARDUINO_MTK3333_NMEA_TYPES_H_ */
 
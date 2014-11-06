/*
 * Library to log core temperature using the PAPI library.
 *
 * Anders Gidenstam  2014
 *
 */

const char* const PAPI_EVENTS[] = {
#ifdef SLEIPNER
  "coretemp:::hwmon0:temp2_input",
  "coretemp:::hwmon0:temp3_input",
  "coretemp:::hwmon0:temp4_input",
  "coretemp:::hwmon0:temp5_input",
#endif
#ifdef HLRSFE
  "coretemp:::hwmon0:temp0_input",
  "coretemp:::hwmon1:temp1_input",
  "coretemp:::hwmon1:temp2_input",
  "coretemp:::hwmon1:temp3_input",
  "coretemp:::hwmon1:temp4_input",
  "coretemp:::hwmon1:temp5_input",
  "coretemp:::hwmon2:temp1_input",
  "coretemp:::hwmon2:temp2_input",
  "coretemp:::hwmon2:temp3_input",
  "coretemp:::hwmon2:temp4_input",
  "coretemp:::hwmon2:temp5_input",
#endif
#ifdef HLRSEXCESS
  "coretemp:::hwmon0:temp0_input",
  "coretemp:::hwmon1:temp1_input",
  "coretemp:::hwmon1:temp2_input",
  "coretemp:::hwmon1:temp3_input",
  "coretemp:::hwmon1:temp4_input",
  "coretemp:::hwmon1:temp5_input",
  "coretemp:::hwmon1:temp6_input",
  "coretemp:::hwmon1:temp10_input",
  "coretemp:::hwmon1:temp11_input",
  "coretemp:::hwmon1:temp12_input",
  "coretemp:::hwmon1:temp13_input",
  "coretemp:::hwmon1:temp14_input",
  "coretemp:::hwmon2:temp1_input",
  "coretemp:::hwmon2:temp2_input",
  "coretemp:::hwmon2:temp3_input",
  "coretemp:::hwmon2:temp4_input",
  "coretemp:::hwmon2:temp5_input",
  "coretemp:::hwmon2:temp6_input",
  "coretemp:::hwmon2:temp10_input",
  "coretemp:::hwmon2:temp11_input",
  "coretemp:::hwmon2:temp12_input",
  "coretemp:::hwmon2:temp13_input",
  "coretemp:::hwmon2:temp14_input",
#endif
#ifdef CTHEXCESS
  "coretemp:::hwmon0:temp0_input",
  "coretemp:::hwmon1:temp1_input",
  "coretemp:::hwmon1:temp3_input",
  "coretemp:::hwmon1:temp4_input",
  "coretemp:::hwmon1:temp5_input",
  "coretemp:::hwmon1:temp6_input",
  "coretemp:::hwmon1:temp10_input",
  "coretemp:::hwmon1:temp11_input",
  "coretemp:::hwmon1:temp12_input",
  "coretemp:::hwmon1:temp13_input",
  "coretemp:::hwmon2:temp1_input",
  "coretemp:::hwmon2:temp3_input",
  "coretemp:::hwmon2:temp4_input",
  "coretemp:::hwmon2:temp5_input",
  "coretemp:::hwmon2:temp6_input",
  "coretemp:::hwmon2:temp10_input",
  "coretemp:::hwmon2:temp11_input",
  "coretemp:::hwmon2:temp12_input",
  "coretemp:::hwmon2:temp13_input",
#endif
  NULL
};

#include "papi-base.c"

/*
 * Library to log core temperature using the PAPI library.
 *
 * Copyright (C) 2014 Anders Gidenstam
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
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
  "coretemp:::hwmon0:temp1_input",
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

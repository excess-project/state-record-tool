/*
 * Library to log RAPL performance counters using the PAPI library.
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
#ifdef CTHEXCESS
  /*"rapl:::PACKAGE_ENERGY_CNT:PACKAGE0",
  "rapl:::PACKAGE_ENERGY_CNT:PACKAGE1",
  "rapl:::DRAM_ENERGY_CNT:PACKAGE0",
  "rapl:::DRAM_ENERGY_CNT:PACKAGE1",
  "rapl:::PP0_ENERGY_CNT:PACKAGE0",
  "rapl:::PP0_ENERGY_CNT:PACKAGE1",*/
  "rapl:::PACKAGE_ENERGY:PACKAGE0",
  "rapl:::PACKAGE_ENERGY:PACKAGE1",
  "rapl:::DRAM_ENERGY:PACKAGE0",
  "rapl:::DRAM_ENERGY:PACKAGE1",
  "rapl:::PP0_ENERGY:PACKAGE0",
  "rapl:::PP0_ENERGY:PACKAGE1",
#endif
#ifdef HLRSFE
  "rapl:::PACKAGE_ENERGY:PACKAGE0",
  "rapl:::PACKAGE_ENERGY:PACKAGE1",
  "rapl:::DRAM_ENERGY:PACKAGE0",
  "rapl:::DRAM_ENERGY:PACKAGE1",
  "rapl:::PP0_ENERGY:PACKAGE0",
  "rapl:::PP0_ENERGY:PACKAGE1",
#endif
#ifdef HLRSEXCESS
  "rapl:::PACKAGE_ENERGY:PACKAGE0",
  "rapl:::PACKAGE_ENERGY:PACKAGE1",
  "rapl:::DRAM_ENERGY:PACKAGE0",
  "rapl:::DRAM_ENERGY:PACKAGE1",
  "rapl:::PP0_ENERGY:PACKAGE0",
  "rapl:::PP0_ENERGY:PACKAGE1",
#endif
  NULL
};

#include "papi-base.c"

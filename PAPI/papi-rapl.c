/*
 * Library to log RAPL performance counters using the PAPI library.
 *
 * Anders Gidenstam  2014
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

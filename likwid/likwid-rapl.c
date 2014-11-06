/*
 * likwid-rapl.c
 *
 * Created on: 2014-09-24
 * Author: Anders Gidenstam
 * License: GPL v3 or later (As required due to the use of
 *                           the likwid access client.)
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* likwid includes */
#include <error.h>
#include <cpuid.h>
#include <numa.h>
#include <accessClient.h>
#include <msr.h>
#include <perfmon.h>
#include <power.h>

static void init(FILE* file);
static void write_sample(FILE* file);
static void shutdown(FILE* file);

static int sockets = 0;
static PowerData* pDataPkg;
static PowerData* pDataPP0;
static PowerData* pDataDram;
static int* cpuId;
static int has_pp0  = 0;
static int has_dram = 0;
static int msr_socket_fd = -1;

static void init(FILE* file)
{
  int i;
  if (cpuid_init() == EXIT_FAILURE) {
    printf("likwid-rapl.c: Unsupported processor!\n");
    exit(EXIT_FAILURE);
  }
  numa_init(); /* consider NUMA node as power unit for the moment */
  accessClient_setaccessmode(1);
  accessClient_init(&msr_socket_fd);
  msr_init(msr_socket_fd);
  timer_init();

  /* check for supported processors */
  if ((cpuid_info.model != SANDYBRIDGE) &&
      (cpuid_info.model != SANDYBRIDGE_EP)  &&
      (cpuid_info.model != IVYBRIDGE)  &&
      (cpuid_info.model != IVYBRIDGE_EP)  &&
      (cpuid_info.model != HASWELL)) {
    fprintf (stderr, "likwid-rapl.c: RAPL not supported on this processor!\n");
    exit(EXIT_FAILURE);
  }
  if ((cpuid_info.model == SANDYBRIDGE_EP) ||
      (cpuid_info.model == IVYBRIDGE_EP)) {
    has_dram = 1;
  }
  has_pp0 = 1;
  power_init(numa_info.nodes[0].processors[0]);

  sockets = cpuid_topology.numSockets;

  /* Allocate the static data arrays. */
  cpuId     = (int*)calloc(sockets, sizeof(int));
  pDataPkg  = (PowerData*)calloc(sockets, sizeof(PowerData));
  pDataDram = (PowerData*)calloc(sockets, sizeof(PowerData));
  pDataPP0  = (PowerData*)calloc(sockets, sizeof(PowerData));

  for (i = 0; i < sockets; i++) {
    cpuId[i] = numa_info.nodes[i].processors[0];
  }

  //printf("Power unit: %e J\n", power_info.energyUnit);

  /* Write rest of legend to the log file. */
  for (i = 0; i < sockets; i++) {
    if (!i) {
      fprintf(file, "PKG%i (J)", i);
    } else {
      fprintf(file, ", PKG%i (J)", i);
    }
  }
  if (has_dram) {
    for (i = 0; i < sockets; i++) {
      fprintf(file, ", DRAM%i (J)", i);
    }
  }
  if (has_pp0) {
    for (i = 0; i < sockets; i++) {
      fprintf(file, ", PP0%i (J)", i);
    }
  }
  fprintf(file, "\n");

  /* Start counting. */
  for (i = 0; i < sockets; i++) {
    power_start(&pDataPkg[i], cpuId[i], PKG);
    if (has_dram) {
      power_start(&pDataDram[i], cpuId[i], DRAM);
    }
    if (has_pp0) {
      power_start(&pDataPP0[i], cpuId[i], PP0);
    }
  }
  printf("likwid-rapl.c: initialized.\n");
}

static void write_sample(FILE* file)
{
  double val;
  int i;

  for (i = 0; i < sockets; i++) {
    power_stop(&pDataPkg[i], cpuId[i], PKG);
    val = power_printEnergy(&pDataPkg[i]);

    if (!i) {
      fprintf(file, "%e", val);
    } else {
      fprintf(file, ", %e", val);
    }
  }
  
  if (has_dram) {
    for (i = 0; i < sockets; i++) {
      power_stop(&pDataDram[i], cpuId[i], DRAM);
      val = power_printEnergy(&pDataDram[i]);

      fprintf(file, ", %e", val);
    }
  }
  if (has_pp0) {
    for (i = 0; i < sockets; i++) {
      power_stop(&pDataPP0[i], cpuId[i], PP0);
      val = power_printEnergy(&pDataPP0[i]);

      fprintf(file, ", %e", val);
    }
  }
  fprintf(file, "\n");
}

static void shutdown(FILE* file)
{
  write_sample(file);
  free(cpuId);
  free(pDataPkg);
  free(pDataDram);
  free(pDataPP0);
}

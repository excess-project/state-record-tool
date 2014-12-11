/*
 * Library to log performance counter data and core temperatures.
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

#include "read-pc.h"

#include <stdlib.h>
#include <pthread.h>
#include <time.h>

static void handle_error(char* msg);
static void* reader_main(void* arg);

/* Include the specific performance count reader. */
#ifdef PAPI_CORETEMP
#include "PAPI/papi-coretemp.c"
#endif
#ifdef PAPI_RAPL
#include "PAPI/papi-rapl.c"
#endif
#ifdef LIKWID_RAPL
#include "likwid/likwid-rapl.c"
#endif

volatile int finished = 0;
pthread_t reader_thread;
double interval_sec;

int pp_start(FILE* file, double frequency)
{
  int retval;
  int i;

  /* Write legend to the log file. */
  fprintf(file, "# timestamp, ");
  init(file);

  /* Start recording thread. */
  interval_sec = 1.0/frequency;
  pthread_create(&reader_thread, NULL, reader_main, file);
}

int pp_end()
{
  finished = 1;

  pthread_join(reader_thread, NULL);
}

static void handle_error(char* msg)
{
  fprintf(stderr, "read-pc.c: Failure with error '%s'.\n",
          msg);
  exit(1);
}

static void* reader_main(void* arg)
{
  FILE* file = (FILE*)arg;
  int i, retval;
  struct timespec delay;
  struct timespec now;
  delay.tv_sec = (time_t)interval_sec;
  delay.tv_nsec = (long)((interval_sec - (double)delay.tv_sec) * 1000000000);

  while (!finished) {
    clock_gettime(CLOCK_REALTIME, &now);

    fprintf(file, "%f, ", now.tv_sec + 1e-9*(double)now.tv_nsec);
    write_sample(file);

    nanosleep(&delay, NULL);
  }

  clock_gettime(CLOCK_REALTIME, &now);
  fprintf(file, "%f, ", now.tv_sec + 1e-9*(double)now.tv_nsec);
  shutdown(file);
}

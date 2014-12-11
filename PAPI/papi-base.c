/*
 * Library to log system state information using the PAPI library.
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

#include <stdlib.h>
#include <papi.h>

static void init(FILE* file);
static void write_sample(FILE* file);
static void shutdown(FILE* file);

static int EventSet = PAPI_NULL;

static void init(FILE* file)
{
  int retval;
  int i;

  /* Initialize the PAPI library. */
  retval = PAPI_library_init(PAPI_VER_CURRENT);

  if (retval != PAPI_VER_CURRENT && retval > 0) {
    fprintf(stderr, "papi-base.c: PAPI library version mismatch!\n");
    exit(1);
  }
  if (retval < 0) {
    fprintf(stderr, "papi-base.c: Initialization error!\n");
    exit(1);
  }

  /* Set up an EventSet. */
  retval = PAPI_create_eventset(&EventSet);
  if (retval != PAPI_OK) {
    handle_error(PAPI_strerror(retval));
  }

  for (i = 0; PAPI_EVENTS[i]; i++) {
    retval = PAPI_add_named_event(EventSet,
                                  (char*)PAPI_EVENTS[i]);
    if (retval != PAPI_OK) {
      fprintf(stderr, "papi-base.c: Failure to add PAPI event '%s'.\n",
              PAPI_EVENTS[i]);
      handle_error(PAPI_strerror(retval));
    }
  }

  /* Write rest of legend to the log file. */
  for (i = 0; PAPI_EVENTS[i]; i++) {
    if (PAPI_EVENTS[i+1]) {
      fprintf(file, "%s, ", PAPI_EVENTS[i]);
    } else {
      fprintf(file, "%s\n", PAPI_EVENTS[i]);
    }
  }

  /* Start counting. */
  retval =  PAPI_start(EventSet);
  if (retval != PAPI_OK) {
    handle_error(PAPI_strerror(retval));
  }

}

static void write_sample(FILE* file)
{
  long_long values[256];
  int i, retval;

  retval = PAPI_read(EventSet, values);
  if (retval != PAPI_OK) {
    handle_error(PAPI_strerror(retval));
  }

  for (i = 0; PAPI_EVENTS[i]; i++) {
    if (PAPI_EVENTS[i+1]) {
      fprintf(file, "%lld, ", values[i]);
    } else {
      fprintf(file, "%lld\n", values[i]);
    }
  }
}

static void shutdown(FILE* file)
{
  long_long values[256];
  int retval;
  retval = PAPI_stop(EventSet, values);
  if (retval != PAPI_OK) {
    handle_error(PAPI_strerror(retval));
  }
  write_sample(file);
}

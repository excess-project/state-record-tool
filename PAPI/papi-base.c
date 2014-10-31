/*
 * Library to log system state information using the PAPI library.
 *
 * Anders Gidenstam  2014
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

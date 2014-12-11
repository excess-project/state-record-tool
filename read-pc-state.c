/*
 * Linux command line utility to read system state at a fixed rate.
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "read-pc.h"

/* Internal functions. */
static void print_usage(int argc, char** argv);
static void process_arguments(int argc, char** argv);

/* Global state. Use with care. */
char *file_name = NULL;
FILE* file = NULL;
double sample_rate = 1.0;
int duration = 10;

int main(int argc, char** argv)
{
  process_arguments(argc, argv);
  printf("Starting state logging... ");

  if (file_name) {
    /* Open the data file */
    file = fopen(file_name, "w");
    if (file == NULL) {
      perror("fopen error: ");
    }
  } else {
    file = stdout;
  }

  pp_start(file, sample_rate);
  printf("done.\n");

  {
    struct timespec delay;
    delay.tv_sec = duration;
    delay.tv_nsec = 0;

    nanosleep(&delay, NULL);
  }

  printf("Ending state logging... ");
  pp_end();
  printf("done.\n");

  if (file) {
    fclose(file);
  }

  return 0;
}

static void print_usage(int argc, char** argv)
{
  printf("Usage: %s [OPTIONS]\n\n", argv[0]);
  printf("  -h                       Print this message and exit.\n");
  printf("  -o <file name>           Save the result in the named file.\n");
  printf("                           The default is stdout.\n");
  printf("  -s <sample rate in Hz>   Set the sample rate in Hz. The default is 1 Hz.\n");
  printf("  -d <duration>            Sample for <duration> seconds.\n");
  printf("                           The default is 10 seconds. \n");
}

static void process_arguments(int argc, char** argv)
{
  int i = 1;

  while (i < argc) {
    if (strcmp(argv[i], "-h") == 0) {
      print_usage(argc, argv);
      exit(0);
    } else if (strcmp(argv[i], "-o") == 0) {
      i++;
      if (i >= argc) {
        fprintf(stderr, "%s: No file name given to '-o'.\n", argv[0]);
        exit(-1);
      }
      file_name = argv[i];
    } else if (strcmp(argv[i], "-s") == 0) {
      float s;
      i++;
      if (i >= argc || 1 != sscanf(argv[i], "%f", &s) || s < 1) {
        fprintf(stderr, "%s: Bad sample frequency given to '-s'.\n", argv[0]);
        exit(-1);
      }
      sample_rate = s;
    } else if (strcmp(argv[i], "-d") == 0) {
      int d;
      i++;
      if (i >= argc || 1 != sscanf(argv[i], "%d", &d) || d < 1) {
        fprintf(stderr, "%s: Bad duration given to '-d'.\n", argv[0]);
        exit(-1);
      }
      duration = d;
    } else {
      fprintf(stderr, "%s: Unknown commandline argument '%s'.\n", argv[0], argv[i]);
      exit(-1);
    }
    i++;
  }
}

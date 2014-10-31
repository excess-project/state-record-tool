/*
 * Library to log performance counter data and core temperatures.
 *
 * Anders Gidenstam  2014
 *
 */
#ifndef _READ_PC_H
#define _READ_PC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

int pp_start(FILE* file, double frequency);

int pp_end();

#ifdef __cplusplus
}
#endif

#endif /* _READ_PC_H */

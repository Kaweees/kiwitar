#include <getopt.h>
#include <stdio.h>
#include "tar.h"

#define USAGE_STRING "Usage: %s  [ctxvS]f tarfile [ path [ ... ] ]\n" /* Program usage string */
#define SYSCALL_ERROR -1

/**
 * Prints the proper usage of the program and exits unsuccessfully.
 */
void usage(char* prog_name) {
  fprintf(stderr, USAGE_STRING, prog_name);
  exit(EXIT_FAILURE);
}

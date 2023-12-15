#include <getopt.h>
#include <stdio.h>
#include "tar.h"

/**
 * Prints the proper usage of the program and exits unsuccessfully.
 */
void usage() {
  fprintf(stderr, "Usage: mytar [ctxvS]f tarfile [ path [ ... ] ]\n");
  exit(EXIT_FAILURE);
}

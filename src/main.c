#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/kiwitar.h"
#include "../include/utils.h"

/**
 * @brief Program entry point
 *
 * @param argc - the number of command line arguments
 * @param argv - an array of command line arguments
 * @return int - the exit status
 */
int main(int argc, char* argv[]) {
  enum ProgramOptions opt = 0;
  int create = 0, list = 0, extract = 0, verbose = 0, strict = 0;
  char* archive_name = NULL;
  while ((opt = getopt(argc, argv, "ctxvSf:")) != OUT_OF_OPTIONS) {
    switch (opt) {
      case CREATE_ARCHIVE: create = 1; break;
      case LIST_CONTENTS: list = 1; break;
      case EXTRACT_CONTENTS: extract = 1; break;
      case VERBOSE_OUTPUT: verbose = 1; break;
      case SPECIFY_ARCHIVE_NAME: archive_name = optarg; break;
      case STRICT_FORMAT: strict = 1; break;
      default: usage(*argv);
    }
  } /* Ensure only one operation and the archive name are specified. */
  if ((create + list + extract) != 1 || archive_name == NULL) { usage(*argv); }

  if (create) { createArchive(archive_name, argc - optind, &argv[optind], verbose, strict); }
  // else if (list) {
  //   listArchive(archive_name, verbose, strict);
  // } else if (extract) {
  //   extractArchive(archive_name, verbose, strict);
  // }

  return EXIT_SUCCESS;
}

#include "tar.h"

#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define SYSCALL_ERROR -1

void createArchiveHelper(
    FILE *archive, char *curr_path, bool verbose, bool strict) {
  printf("Creating archive for %s\n", curr_path);
  USTARHeader header = {0};
  bool passing_strict = true;
  bool success_writing = true;
  // uint8_t checksum = 0;

  /* Get the stats of the file/directory */
  struct stat *statbuf = malloc(sizeof(struct stat));
  if (stat(curr_path, statbuf) == -1) {
    perror("Error getting file stats");
    exit(EXIT_FAILURE);
  }
  if (lstat(curr_path, statbuf) == SYSCALL_ERROR) {
    perror("Failed to get the file stats");
    exit(EXIT_FAILURE);
  }
  /* Store the name in a string */
  strncpy(header.name, curr_path, ARCHIVE_NAME_SIZE);

  snprintf(header.mode, ARCHIVE_MODE_SIZE, "%07o",
      (unsigned int)statbuf->st_mode & DEFAULT_PERMISSIONS);
  /* Store the user id in a string */

  if ((!strict || (strict && passing_strict)) && success_writing) {
    /* Write the file contents to the archive if strict mode enabled and the
     * file is conforming to the POSIX-specified USTAR archive format or if
     * strict mode is not enabled */
    if (fwrite(&header, 1, sizeof(USTARHeader), archive) !=
        sizeof(USTARHeader)) {
      perror("Error writing header to archive");
      fclose(archive);
      return;
    }
  }

  /* print out file permissions, the owner/group, the size, last modification
   * time and the filename*/
  if (verbose) {
    struct passwd *pwd = getpwuid(statbuf->st_uid);
    struct group *grp = getgrgid(statbuf->st_gid);
    char time_str[MTIME_WIDTH + 1] = {0};
    char owner_group[OWNER_GROUP_WIDTH + 1];
    snprintf(owner_group, OWNER_GROUP_WIDTH + 1, "%s/%s", pwd->pw_name,
        grp->gr_name);
    strftime(time_str, MTIME_WIDTH + 1, "%Y-%m-%d %H:%M",
        localtime(&statbuf->st_mtime));
    printf("%c%c%c%c%c%c%c%c%c%c ",
        (S_ISDIR(statbuf->st_mode))   ? 'd'
        : (S_ISLNK(statbuf->st_mode)) ? 'l'
                                      : '-',
        (statbuf->st_mode & S_IRUSR) ? 'r' : '-',
        (statbuf->st_mode & S_IWUSR) ? 'w' : '-',
        (statbuf->st_mode & S_IXUSR) ? 'x' : '-',
        (statbuf->st_mode & S_IRGRP) ? 'r' : '-',
        (statbuf->st_mode & S_IWGRP) ? 'w' : '-',
        (statbuf->st_mode & S_IXGRP) ? 'x' : '-',
        (statbuf->st_mode & S_IROTH) ? 'r' : '-',
        (statbuf->st_mode & S_IWOTH) ? 'w' : '-',
        (statbuf->st_mode & S_IXOTH) ? 'x' : '-');
    printf("%-*s", OWNER_GROUP_WIDTH, owner_group);
    printf(" %*lu", SIZE_WIDTH, (unsigned long)statbuf->st_size);
    printf(" %-*s", MTIME_WIDTH, time_str);
    printf(" %s\n", curr_path);
  }
}

/**
 * Creates a tar archive
 *
 * @param archive_name the name of the archive to create
 * @param file_count the number of files to archive
 * @param file_names an array of file names to archive
 * @param verbose a flag to indicate whether to give verbose output while
 creating the archive
 * @param strict a flag to indicate whether to be strict on files conforming
 to the POSIX-specified USTAR archive format
 */
void createArchive(char *archive_name, int file_count, char *file_names[],
    bool verbose, bool strict) {
  FILE *archive =
      fopen(archive_name, "wb"); /* Open the archive file for writing */
  if (archive == NULL) {
    perror("Error creating archive");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < file_count; i++) {
    createArchiveHelper(archive, file_names[i], verbose, strict);
  }

  /* Write the End of Archive marker which consists of two blocks of all zero
   * bytes */
  char zero_block[ARCHIVE_BLOCK_SIZE * 2] = {0};
  if (fwrite(zero_block, 1, ARCHIVE_BLOCK_SIZE * 2, archive) !=
      ARCHIVE_BLOCK_SIZE * 2) {
    perror("Error writing End of Archive marker");
    exit(EXIT_FAILURE);
  }
  fclose(archive);
}

/**
 * Lists the contents of a tar archive
 *
 * @param archive_name the name of the archive to list
 * @param verbose a flag to indicate whether to give verbose output while
 listing the archive
 * @param strict a flag to indicate whether to be strict on files conforming
 to the POSIX-specified USTAR archive format
 */
void listArchive(char *archive_name, int verbose, int strict) { return; }

/**
 * Extracts the contents of a tar archive
 *
 * @param archive_name the name of the archive to extract
 * @param verbose a flag to indicate whether to give verbose output while
  extracting the archive
 * @param strict a flag to indicate whether to be strict on files conforming
 to
  the POSIX-specified USTAR archive format
*/
void extractArchive(char *archive_name, int verbose, int strict) { return; }
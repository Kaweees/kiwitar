#ifndef TAR_H
#define TAR_H

#define PERMISSIONS_WIDTH 10
#define OWNER_GROUP_WIDTH 17
#define SIZE_WIDTH        8
#define MTIME_WIDTH       16

/* Begin typedef declarations */

/* Represents the options that can be passed to the program */
typedef enum TarOptions {
  CREATE_ARCHIVE = 'c',
  LIST_CONTENTS = 't',
  EXTRACT_CONTENTS = 'x',
  VERBOSE_OUTPUT = 'v',
  SPECIFY_ARCHIVE_NAME = 'f',
  STRICT_FORMAT = 'S',
  OUT_OF_OPTIONS = -1
} TarOptions;

/* Represents the type of a file in a tar archive */
typedef enum FileType {
  REGULAR_FILE = '0',
  REGULAR_FILE_ALTERNATE = '\0',
  SYMBOLIC_LINK = '2',
  DIRECTORY = '5'
} FileType;

/* Represents a header of the POSIX-specified USTAR archive format */
typedef struct USTARHeader {
  /* File name portion of the header */
  char name[ARCHIVE_NAME_SIZE];
  /* File modes portion of the header */
  char mode[ARCHIVE_MODE_SIZE];
  /* User id portion of the header */
  char uid[ARCHIVE_UID_SIZE];
  /* Group id portion of the header */
  char gid[ARCHIVE_GID_SIZE];
  /* File size portion of the header */
  char size[ARCHIVE_SIZE_SIZE];
  /* Modification time portion of the header */
  char mtime[ARCHIVE_MTIME_SIZE];
  /* Checksum portion of the header */
  char chksum[ARCHIVE_CHKSUM_SIZE];
  /* File type portion of the header */
  FileType typeflag;
  /* Link name portion of the header */
  char linkname[ARCHIVE_LINKNAME_SIZE];
  /* Magic number portion of the header */
  char magic[ARCHIVE_MAGIC_SIZE];
  /* Version portion of the header */
  char version[ARCHIVE_VERSION_SIZE];
  /* User name portion of the header */
  char uname[ARCHIVE_UNAME_SIZE];
  /* Group name portion of the header */
  char gname[ARCHIVE_GNAME_SIZE];
  /* Major device number portion of header */
  char devmajor[ARCHIVE_DEVMAJOR_SIZE];
  /* Minor device number portion of header */
  char devminor[ARCHIVE_DEVMINOR_SIZE];
  /* Prefix portion of the header */
  char prefix[ARCHIVE_PREFIX_SIZE];
} USTARHeader;

#endif /* TAR_H */

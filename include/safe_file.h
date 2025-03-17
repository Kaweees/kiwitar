#pragma once

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FILE_ERROR -1

/* Represents the contents of a file */
typedef struct FileContent {
    /* The length of the file contents in bytes */
    ssize_t file_size;
    /* The pointer to the file contents */
    unsigned char* file_contents;
} FileContent;

int safeOpen(char* filename, int flags, mode_t mode);
FileContent* safeRead(int fd);
void safeWrite(int fd, void* buf, size_t count);
void safeClose(int fd);
void freeFileContent(FileContent* file_contents);

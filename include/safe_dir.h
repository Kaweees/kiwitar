#pragma once

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "limits.h"

#ifndef PATH_MAX
#define PATH_MAX 2048 /* Maximum number of characters in a path name */
#endif

#define DIR_ERROR -1

/* Represents the contents of a directory */
typedef struct DirContent {
    /* The number of entries in the directory */
    ssize_t num_entries;
    /* The pointer to the directory entries */
    struct dirent** entries;
} DirContent;

DIR* safeOpenDir(const char* path);
DirContent* safeReadDir(DIR* dir);
void safeRewindDir(DIR* dir);
void safeCloseDir(DIR* dir);
void safeStat(char* path, struct stat* buf);
void safeLstat(const char* path, struct stat* buf);
void safeChdir(char* path);
void freeDirContent(DirContent* dir_contents);
char* safeGetCwd(char* buf, size_t size);

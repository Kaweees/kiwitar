#pragma once

#include <stdlib.h>
#include <unistd.h>

void* safeMalloc(size_t size);
void* safeRealloc(void* ptr, size_t size);
void* safeCalloc(size_t nmemb, size_t size);
void safeFree(void* ptr);

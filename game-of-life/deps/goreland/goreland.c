#include "goreland.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

void *memory(size_t size) {
  void *mem = malloc(size);
  if (mem == NULL) {
    logFatal("Can't allocate memory");
    return NULL;
  }

  return mem;
}

void logError(char *message) { printf(RED "[!!] %s" RESET, message); }
void logFatal(char *message) {
  logError(message);
  exit(1);
}

void logSuccess(char *message) { printf(GRN "[:)] %s" RESET, message); }

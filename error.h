#ifndef ERROR_H_
#define ERROR_H_

#include <stdio.h>

typedef enum { SUCCESS, FAILURE } result;

#define warn(msg) fprintf(stderr, "[%s:%d]: %s\n", __FILE__, __LINE__, msg)
#define goto_fail(msg) {warn(msg); goto fail;}

#define MEMORY_ERROR "Out of memory"

#endif

#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

// Elementwise copies memory from one location to another.
void copy( void * const dest, const void * const src, const size_t dest_sz,
           const size_t n );

#endif

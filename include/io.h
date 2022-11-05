#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_IO_BUFFER_SIZE 1024

char * get_n_char( char ** const buf, size_t * const restrict n,
                   FILE * const  stream );

char * get_delim_char( char ** const buf, const char * const restrict delim,
                       FILE *        stream );

#endif

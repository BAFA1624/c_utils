#ifndef IO_H
#define IO_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MAX_IO_BUFFER_SIZE
    #define MAX_IO_BUFFER_SIZE 1024
#endif

// Retrieves input from 'stream' until 'n' chars are received,
// or EOF is reached.
char * get_n_char( char ** const buf, size_t * const restrict n,
                   FILE * const  stream );

// Retrieves input from 'stream' until 'delim' is reached,
// 'n' chars are received, or EOF is reached.
char * get_delim_char( char ** const buf, size_t * const restrict n,
                       const char * const restrict delim, FILE * stream );

int valid_input( char ** const restrict response_buf, size_t * input_size,
                 const char * const valid_chars );
#endif

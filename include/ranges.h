#ifndef RANGES_H
#define RANGES_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h> // perror, remove after writing own error function
#include <stdlib.h>

typedef struct RANGE_T * range_t;
typedef range_t rrange_t;

typedef void * ( *range_access )( range_t, const size_t );
typedef void * ( *range_const_access )( const range_t, const size_t );


bool
is_forward_range( const range_t r );

size_t
range_size( const range_t r );

void *
front( const range_t r );
void *
back( const range_t r );


range_t
range_create( void * arr, const size_t size, const size_t element_size,
              const bool forward );


void
range_destroy( range_t r );


// Checked access to range
void *
at( range_t r, const size_t i );
// Unchecked access to underlying array
void *
access( range_t r, const size_t i );


// May not be necessary
// May alter underlying array
/*range_t
range_realloc( range_t r, const size_t new_element_size,
               const size_t n_elements );*/

#endif // RANGES_H

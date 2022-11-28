#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "ranges.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void ( *transform_func )( const void **, void ** );


typedef range_t tr_range_t;

tr_range_t get_tr_range( void * const arr, const size_t, const size_t );

void apply_transform( void *, const size_t, transform_func );

void *     transform_range( const range_t, transform_func, const size_t );
void *     transform_const_range( const const_range_t, transform_func,
                                  const size_t );
tr_range_t transform_arr( void * const, const size_t, const size_t,
                          transform_func, const size_t );
tr_range_t transform_tr_range( tr_range_t, transform_func, const size_t );

// clang-format off
#define transform( data, func, new_element_size )\
    _Generic( (data),\
            range_t: transform_range,\
            const_range_t: transform_const_range,\
            tr_range_t *: transform_tr_range,\
            void*: transform_arr )\
    ( ( data ), ( func ), ( new_element_size) )

// clang-format on

#endif

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "ranges.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct ARGS_
{
    const size_t  n;
    const void ** args;
};


typedef struct ARGS_ args;
typedef range_t      tr_range_t;
typedef rrange_t     trr_range_t;

typedef void ( *transform_func )( const void **, void ** );
typedef void ( *test_transform_func )( const void **, const args );


tr_range_t  get_tr_range( void * const arr, const size_t, const size_t );
trr_range_t get_trr_range( void * const arr, const size_t, const size_t );

void apply_transform( void **, const size_t, const transform_func, ... );

tr_range_t transform_range( const range_t, transform_func, const size_t );
tr_range_t transform_const_range( const const_range_t, const transform_func,
                                  const size_t );
tr_range_t transform_tr_range( tr_range_t, const transform_func, const size_t );

tr_range_t test_transform_range( const range_t, const test_transform_func,
                                 const args );
tr_range_t transform_arr( void * const, const size_t, const size_t,
                          const transform_func, const size_t );


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

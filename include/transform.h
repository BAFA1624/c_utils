#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "ranges.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void ( *transform_func )( const void **, void ** );

struct TRANSFORM_RANGE_T;
typedef struct TRANSFORM_RANGE_T tr_range_t;

struct TRANSFORM_RANGE_T
{
    const_range_t    range;
    size_t           n_transforms;
    size_t           capacity;
    transform_func * transforms;
};

tr_range_t get_tr_range( const void * const arr, const size_t, const size_t );
void       free_tr_range( tr_range_t * tr );

void apply_transform( void *, const size_t, transform_func );

void *     transform_range( const range_t, transform_func );
void *     transform_const_range( const const_range_t, transform_func );
void *     transform_arr( const void * const, const size_t, const size_t,
                          transform_func );
tr_range_t transform_tr_range( tr_range_t, transform_func );

// clang-format off
#define transform( data, func )\
    _Generic( (data),\
            range_t: transform_range,\
            const_range_t: transform_const_range,\
            tr_range_t *: transform_tr_range,\
            void*: transform_arr )\
    ( ( data ), ( func ) )

// clang-format on

#endif

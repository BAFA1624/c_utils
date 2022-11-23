#ifndef RANGES_H
#define RANGES_H

#include <stdlib.h>

typedef struct RANGE_S
{
    void * const begin;
    void * const end;
    const size_t element_size;
} range_t;

typedef struct CONST_RANGE_S
{
    const void * const begin;
    const void * const end;
    const size_t element_size;
} const_range_t;

range_t
get_range( void * const arr, const size_t size, const size_t element_size );

const_range_t
get_const_range_t( const void * const arr, const size_t size,
                   const size_t element_size );

#endif // RANGES_H

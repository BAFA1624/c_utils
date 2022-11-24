#ifndef RANGES_H
#define RANGES_H

#include <assert.h>
#include <stdlib.h>

typedef struct RANGE_T range_t;
typedef void * ( *range_access )( range_t, const size_t );
typedef void * ( *range_const_access )( const range_t, const size_t );
typedef struct CONST_RANGE_T const_range_t;
typedef void * ( *const_range_access )( const const_range_t, const size_t );

typedef struct RANGE_T
{
    void * const       begin;
    void * const       end;
    const void * const cbegin;
    const void * const cend;
    const size_t       element_size;
    range_access       at;
    range_const_access c_at;
} range_t;


struct CONST_RANGE_T
{
    const void * const cbegin;
    const void * const cend;
    const size_t       element_size;
    const_range_access at;
    const_range_access c_at;
};


range_t get_range( void * const arr, const size_t size,
                   const size_t element_size );

void * access_range( range_t r, const size_t i );

void * const_access_range( const range_t r, const size_t i );

const_range_t get_const_range( const void * const arr, const size_t size,
                               const size_t element_size );

void * access_const_range( const const_range_t r, const size_t i );

#endif // RANGES_H

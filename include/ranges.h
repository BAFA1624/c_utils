#ifndef RANGES_H
#define RANGES_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct RANGE_T       range_t;
typedef struct CONST_RANGE_T const_range_t;
typedef range_t              rrange_t;
typedef const_range_t        const_rrange_t;

typedef void * ( *range_access )( range_t, const size_t );
typedef void * ( *range_const_access )( const range_t, const size_t );
typedef void * ( *const_range_access )( const const_range_t, const size_t );

typedef struct RANGE_T
{
    void * const       begin;
    void * const       end;
    const void * const cbegin;
    const void * const cend;
    const size_t       element_size;
} range_t;


struct CONST_RANGE_T
{
    const void * const cbegin;
    const void * const cend;
    const size_t       element_size;
};

#define CHECK_FORWARD_ITER( range_ptr ) \
    ( intptr_t )( range_ptr->cbegin ) < ( intptr_t ) ( range_ptr->cend )

// Get size of range
#define RANGE_SIZE( range )                             \
    ( CHECK_FORWARD_ITER( ( &range ) ) ?                \
          ( size_t ) ( ( uintptr_t ) range.cend         \
                       - ( uintptr_t ) range.cbegin ) : \
          ( size_t ) ( ( uintptr_t ) range.cbegin       \
                       - ( uintptr_t ) range.cend ) )   \
        / range.element_size

// Retrieve front element in raw array
#define FRONT( range )                 \
    CHECK_FORWARD_ITER( ( &range ) ) ? \
        range.cbegin :                 \
        ( void * ) ( ( uintptr_t ) range.cend + range.element_size )

// Retrieve one past the end of the raw array
#define BACK( range )                             \
    CHECK_FORWARD_ITER( ( &range ) ) ?            \
        ( void * ) ( ( uintptr_t ) range.cend ) : \
        ( void * ) ( ( uintptr_t ) range.cbegin + range.element_size )

// Forward/Reverse iteration invariant increment/decrement
#define INCR( range, pos )                                              \
    CHECK_FORWARD_ITER( ( &range ) ) ?                                  \
        ( void * ) ( ( uintptr_t ) ( pos ) + ( range.element_size ) ) : \
        ( void * ) ( ( uintptr_t ) ( pos ) - ( range.element_size ) )

#define INCR_N( range, pos, n )                           \
    CHECK_FORWARD_ITER( ( &range ) ) ?                    \
        ( void * ) ( ( uintptr_t ) ( pos )                \
                     + ( n ) * ( range.element_size ) ) : \
        ( void * ) ( ( uintptr_t ) ( pos ) - ( n ) * ( range.element_size ) )

#define DECR( range, pos )                                              \
    CHECK_FORWARD_ITER( ( &range ) ) ?                                  \
        ( void * ) ( ( uintptr_t ) ( pos ) - ( range.element_size ) ) : \
        ( void * ) ( ( uintptr_t ) ( pos ) + ( range.element_size ) )

#define DECR_N( range, pos, n )                           \
    CHECK_FORWARD_ITER( ( &range ) ) ?                    \
        ( void * ) ( ( uintptr_t ) ( pos )                \
                     - ( n ) * ( range.element_size ) ) : \
        ( void * ) ( ( uintptr_t ) ( pos ) + ( n ) * ( range.element_size ) )



range_t get_range( void * const arr, const size_t size,
                   const size_t element_size );

const_range_t get_const_range( const void * const arr, const size_t size,
                               const size_t element_size );

rrange_t get_rrange( void * const arr, const size_t size,
                     const size_t element_size );

const_rrange_t get_const_rrange( const void * const arr, const size_t size,
                                 const size_t element_size );


void * at_range( range_t * r, const size_t i );

void * const_at_range( const range_t * r, const size_t i );

void * at_const_range( const const_range_t * r, const size_t i );

// clang-format off
#define at_ptr( range_ptr, idx )\
    _Generic( ( range_ptr ),\
            range_t * : at_range,\
            const range_t * : const_at_range,\
            const_range_t * : at_const_range )\
    ( ( range_ptr ), ( idx ) )

// clang-format on

#define at( range, idx ) at_ptr( &range, idx )


#endif // RANGES_H

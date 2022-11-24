#include "ranges.h"

#define CHECK_FORWARD_ITER( range ) \
    ( intptr_t )( range.cbegin ) < ( intptr_t ) ( range.cend )

// Forward/Reverse iteration invariant increment/decrement
#define INCR( range, pos )                                             \
    CHECK_FORWARD_ITER( ( range ) ) ?                                  \
        ( void * ) ( ( intptr_t ) ( pos ) + ( range.element_size ) ) : \
        ( void * ) ( ( intptr_t ) ( pos ) - ( range.element_size ) )

#define INCR_N( range, pos, n )                                                \
    CHECK_FORWARD_ITER( ( range ) ) ?                                          \
        ( void * ) ( ( intptr_t ) ( pos ) + ( n ) * ( range.element_size ) ) : \
        ( void * ) ( ( intptr_t ) ( pos ) - ( n ) * ( range.element_size ) )

#define DECR( range, pos )                                             \
    CHECK_FORWARD_ITER( ( range ) ) ?                                  \
        ( void * ) ( ( intptr_t ) ( pos ) - ( range.element_size ) ) : \
        ( void * ) ( ( intptr_t ) ( pos ) + ( range.element_size ) )

#define DECR_N( range, pos, n )                                                \
    CHECK_FORWARD_ITER( ( range ) ) ?                                          \
        ( void * ) ( ( intptr_t ) ( pos ) - ( n ) * ( range.element_size ) ) : \
        ( void * ) ( ( intptr_t ) ( pos ) + ( n ) * ( range.element_size ) )

range_t
get_range( void * const arr, const size_t size, const size_t element_size ) {
    const range_t range = {
        .begin = arr,
        .end = ( void * const ) ( ( uintptr_t ) arr + size * element_size ),
        .cbegin = ( const void * const ) arr,
        .cend = ( const void * const ) ( ( const uintptr_t ) arr
                                         + size * element_size ),
        .element_size = element_size,
        .at = access_range,
        .c_at = const_access_range
    };
    return range;
}

void *
access_range( range_t r, const size_t i ) {
    const uintptr_t left = CHECK_FORWARD_ITER( r ) ?
                               ( const uintptr_t ) r.cbegin :
                               ( const uintptr_t ) r.cend;
    const uintptr_t right = CHECK_FORWARD_ITER( r ) ?
                                ( const uintptr_t ) r.cend :
                                ( const uintptr_t ) r.cbegin;
    assert( left + i < right );

    return INCR_N( r, r.cbegin, i );
}

void *
const_access_range( const range_t r, const size_t i ) {
    const uintptr_t left = CHECK_FORWARD_ITER( r ) ?
                               ( const uintptr_t ) r.cbegin :
                               ( const uintptr_t ) r.cend;
    const uintptr_t right = CHECK_FORWARD_ITER( r ) ?
                                ( const uintptr_t ) r.cend :
                                ( const uintptr_t ) r.cbegin;
    assert( left + i < right );

    return INCR_N( r, r.cbegin, i );
}

const_range_t
get_const_range( const void * const arr, const size_t size,
                 const size_t element_size ) {
    const const_range_t range = {
        .cbegin = arr,
        .cend = ( const void * const ) ( ( const uintptr_t ) arr
                                         + size * element_size ),
        .element_size = element_size,
        .at = access_const_range,
        .c_at = access_const_range
    };
    return range;
}

void *
access_const_range( const const_range_t r, const size_t i ) {
    // Bounds check
    const uintptr_t left = CHECK_FORWARD_ITER( r ) ?
                               ( const uintptr_t ) r.cbegin :
                               ( const uintptr_t ) r.cend;
    const uintptr_t right = CHECK_FORWARD_ITER( r ) ?
                                ( const uintptr_t ) r.cend :
                                ( const uintptr_t ) r.cbegin;
    assert( left + i < right );

    return INCR_N( r, r.cbegin, i );
}


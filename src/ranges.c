#include "ranges.h"

#define CHECK_FORWARD_ITER( range_ptr ) \
    ( intptr_t )( range_ptr->cbegin ) < ( intptr_t ) ( range_ptr->cend )

// Forward/Reverse iteration invariant increment/decrement
#define INCR( range, pos )                                              \
    CHECK_FORWARD_ITER( ( &range ) ) ?                                  \
        ( void * ) ( ( uintptr_t ) ( pos ) + ( range.element_size ) ) : \
        ( void * ) ( ( uintptr_t ) ( pos ) - ( range.nelement_size ) )

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

range_t
get_range( void * const arr, const size_t size, const size_t element_size ) {
    const range_t range = {
        .begin = arr,
        .end = ( void * const ) ( ( uintptr_t ) arr + size * element_size ),
        .cbegin = ( const void * const ) arr,
        .cend = ( const void * const ) ( ( const uintptr_t ) arr
                                         + size * element_size ),
        .element_size = element_size,
    };
    return range;
}

const_range_t
get_const_range( const void * const arr, const size_t size,
                 const size_t element_size ) {
    const const_range_t range = {
        .cbegin = arr,
        .cend = ( const void * const ) ( ( const uintptr_t ) arr
                                         + size * element_size ),
        .element_size = element_size,
    };
    return range;
}

rrange_t
get_rrange( void * const arr, const size_t size, const size_t element_size ) {
    const rrange_t range = {
        .begin = ( void * const ) ( ( uintptr_t ) arr
                                    + ( size - 1 ) * element_size ),
        .end = ( void * const ) ( ( uintptr_t ) arr - element_size ),
        .cbegin = ( const void * const ) ( ( const uintptr_t ) arr
                                           + ( size - 1 ) * element_size ),
        .cend = ( const void * const ) ( ( uintptr_t ) arr - element_size ),
        .element_size = element_size,
    };
    return range;
}

const_rrange_t
get_const_rrange( const void * const arr, const size_t size,
                  const size_t element_size ) {
    const const_rrange_t range = {
        .cbegin = ( const void * const ) ( ( uintptr_t ) arr
                                           + ( size - 1 ) * element_size ),
        .cend = ( const void * const ) ( ( uintptr_t ) arr - element_size ),
        .element_size = element_size,
    };
    return range;
}


void *
at_range( range_t * r_ptr, const size_t i ) {
    const uintptr_t left = CHECK_FORWARD_ITER( r_ptr ) ?
                               ( const uintptr_t ) r_ptr->cbegin :
                               ( const uintptr_t ) r_ptr->cend;
    const uintptr_t right = CHECK_FORWARD_ITER( r_ptr ) ?
                                ( const uintptr_t ) r_ptr->cend :
                                ( const uintptr_t ) r_ptr->cbegin;
    assert( left + i < right );

    return INCR_N( ( *r_ptr ), ( *r_ptr ).cbegin, i );
}

void *
const_at_range( const range_t * r_ptr, const size_t i ) {
    const uintptr_t left = CHECK_FORWARD_ITER( r_ptr ) ?
                               ( const uintptr_t ) r_ptr->cbegin :
                               ( const uintptr_t ) r_ptr->cend;
    const uintptr_t right = CHECK_FORWARD_ITER( r_ptr ) ?
                                ( const uintptr_t ) r_ptr->cend :
                                ( const uintptr_t ) r_ptr->cbegin;
    assert( left + i < right );

    return INCR_N( ( *r_ptr ), r_ptr->cbegin, i );
}

void *
at_const_range( const const_range_t * r_ptr, const size_t i ) {
    // Bounds check
    const uintptr_t left = CHECK_FORWARD_ITER( r_ptr ) ?
                               ( const uintptr_t ) r_ptr->cbegin :
                               ( const uintptr_t ) r_ptr->cend;
    const uintptr_t right = CHECK_FORWARD_ITER( r_ptr ) ?
                                ( const uintptr_t ) r_ptr->cend :
                                ( const uintptr_t ) r_ptr->cbegin;
    assert( left + i < right );

    return INCR_N( ( *r_ptr ), r_ptr->cbegin, i );
}


#include "ranges.h"

struct RANGE_T
{
    void * begin;
    void * end;
    size_t element_size;
};


bool
is_forward_range( const range_t r ) {
    return ( uintptr_t ) r->begin < ( uintptr_t ) r->end;
}

size_t
range_size( const range_t r ) {
    return ( size_t ) ( is_forward_range( r ) ?
                            ( uintptr_t ) r->end - ( uintptr_t ) r->begin :
                            ( uintptr_t ) r->begin - ( uintptr_t ) r->end );
}

void *
front( const range_t r ) {
    return is_forward_range( r ) ?
               r->begin :
               ( void * ) ( ( uintptr_t ) r->end + r->element_size );
}
void *
back( const range_t r ) {
    return is_forward_range( r ) ?
               r->end :
               ( void * ) ( ( uintptr_t ) r->begin + r->element_size );
}

void *
incr( const range_t r, const void * const ptr ) {
    return ( void * ) ( is_forward_range( r ) ?
                            ( uintptr_t ) ptr + r->element_size :
                            ( uintptr_t ) ptr - r->element_size );
}
void *
decr( const range_t r, const void * const ptr ) {
    return ( void * ) ( is_forward_range( r ) ?
                            ( uintptr_t ) ptr - r->element_size :
                            ( uintptr_t ) ptr + r->element_size );
}

void *
incr_n( const range_t r, const void * const ptr, const size_t n ) {
    return ( void * ) ( is_forward_range( r ) ?
                            ( uintptr_t ) ptr + n * r->element_size :
                            ( uintptr_t ) ptr - n * r->element_size );
}
void *
decr_n( const range_t r, const void * const ptr, const size_t n ) {
    return ( void * ) ( is_forward_range( r ) ?
                            ( uintptr_t ) ptr - n * r->element_size :
                            ( uintptr_t ) ptr + n * r->element_size );
}

range_t
range_create( void * arr, const size_t size, const size_t element_size,
              const bool forward ) {
    range_t r = ( range_t ) malloc( sizeof( struct RANGE_T ) );
    if ( !r ) {
        perror( "malloc" );
        exit( -1 );
    }

    r->begin =
        forward ?
            arr :
            ( void * ) ( ( uintptr_t ) arr + ( size - 1 ) * element_size );
    r->end = ( void * ) ( forward ? ( uintptr_t ) arr + size * element_size :
                                    ( uintptr_t ) arr - element_size );
    r->element_size = element_size;

    return r;
}

void
range_destroy( range_t r ) {
    free( r );
}

void *
at( range_t r, const size_t i ) {
    const size_t n = range_size( r );
    return incr_n( r, front( r ), i % ( n + 1 ) );
}
void *
access( range_t r, const size_t i ) {
    return incr_n( r, front( r ), i );
}

range_t
range_realloc( range_t r, const size_t new_element_size,
               const size_t n_elements ) {
    const bool forward = is_forward_range( r );

    if ( new_element_size != r->element_size ) {}

    return r;
}


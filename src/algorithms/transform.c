#include "transform.h"

typedef void *       T;
typedef const void * CT;

struct ARGS_
{
    size_t   n;
    size_t * argument_sizes;
    T *      arguments;
};

args
args_create( const size_t * args_sizes, const size_t n, ... ) {
    args a = ( args ) malloc( sizeof( struct ARGS_ ) );
    if ( !a ) {
        perror( "malloc" );
        exit( EXIT_FAILURE );
    }
    a->argument_sizes = ( size_t * ) malloc( n * sizeof( size_t ) );
    if ( !a->argument_sizes ) {
        free( a );
        perror( "malloc" );
        exit( EXIT_FAILURE );
    }

    size_t required_capacity = 0;
    for ( size_t i = 0; i < n; ++i ) {
        required_capacity += args_sizes[i];
        a->argument_sizes[i] = args_sizes[i];
    }

    a->arguments = malloc( required_capacity );
    if ( !a->arguments ) {
        free( a->argument_sizes );
        free( a );
        perror( "malloc" );
        exit( EXIT_FAILURE );
    }

    va_list ap;
    va_start( ap, n );

    for ( size_t i = 0; i < n; ++i ) {
        size_t sz = 0;
        T *    arg1 = args_at( a, i, &sz );
        T      arg2 = va_arg( ap, T );
        memcpy( arg1, arg2, sz );
    }

    va_end( ap );

    return a;
}

void
args_destroy( args a ) {
    if ( !a->arguments ) {
        free( a->arguments );
    }
    if ( !a->argument_sizes ) {
        free( a->argument_sizes );
    }
    if ( !a ) {
        free( a );
    }
}

T *
args_at( args a, const size_t i, size_t * sz ) {
    *sz = a->argument_sizes[i];

    uintptr_t pos = ( uintptr_t ) a->arguments;
    for ( size_t j = 0; j < i; ++j ) { pos += a->argument_sizes[j]; }

    return ( T * ) pos;
}

bool
args_verify( const args a, size_t n, ... ) {
    int result = 0;

    va_list ap;
    va_start( ap, n );

    for ( size_t i = 0; i < n; ++i ) {
        size_t sz = 0;
        T      arg1 = args_at( a, i, &sz );
        T      arg2 = va_arg( ap, T );
        result += memcmp( arg1, arg2, sz );
    }

    va_end( ap );

    return !( bool ) result;
}

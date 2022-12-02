#include "transform.h"

typedef void * T;

struct ARGS_
{
    size_t n;
    size_t * args_sizes;
    T * args;
};

args
args_create( const size_t n, const size_t * args_sizes, T * args ) {
    args a = ( args ) malloc( sizeof( struct ARGS_ ) );
    if ( !a ) {
        perror( "malloc" );
        exit( EXIT_FAILURE );
    }

    size_t required_capacity = 0;
    for ( size_t i = 0; i < n; ++i ) { required_capacity += args_sizes[i]; }

    a->args = malloc( required_capacity );
    if ( !a->args ) {
        perror( "malloc" );
        exit( EXIT_FAILURE );
    }

    for ( size_t i = 0; i < required_capacity; ++i ) {}


    return a;
}
void
args_destroy( args a ) {
    free( a->args );
    free( a->args_sizes );
    free( a );
}

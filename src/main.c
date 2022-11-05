#include "io.h"

#include <assert.h>

int
main( int argc, char * argv[] ) {
    assert( argc > 1 );

    size_t n = atoi( argv[1] );

    char * buf = ( char * ) malloc( n );

    get_n_char( &buf, &n, stdin );
    puts( buf );

    free( buf );

    return 0;
}

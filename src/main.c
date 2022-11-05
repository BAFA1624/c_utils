#include "io.h"

#include <assert.h>

int
main( int argc, char * argv[] ) {
    printf( "Writing tmp file.\n" );
    size_t n;
    if ( argc > 1 )
        n = atoi( argv[1] );
    n = MAX_IO_BUFFER_SIZE;
    FILE * fp = fopen( "tmp.txt", "w" );
    char   c[n];
    size_t i = 0;
    for ( ; i < n - 1; ++i ) { c[i] = 'c'; }
    c[n - 1] = '\0';
    fputs( c, fp );
    fclose( fp );
    printf( "Complete.\n" );

    printf( "Testing get_n_char.\n" );
    fp = fopen( "tmp.txt", "r" );
    // char * buf = ( char * ) malloc( n );
    char * buf = get_n_char( NULL, &n, fp );
    free( buf );
    fclose( fp );
    printf( "Complete.\n" );

    printf( "Removing tmp file.\n" );
    remove( "tmp.txt" );
    printf( "Complete.\n" );

    return 0;
}

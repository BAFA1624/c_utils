#include "io.h"

#include <assert.h>

int
main( int argc, char * argv[] ) {
    assert( argc == 3 );

    printf( "Writing tmp file.\n" );
    // const size_t pos = atoi( argv[1] );
    const char delim = argv[2][0];

    size_t n = MAX_IO_BUFFER_SIZE;
    FILE * fp = fopen( "tmp.txt", "w" );
    char   c[n];
    size_t i = 0;
    for ( ; i < n - 1; ++i ) {
        // if ( i != pos )
        c[i] = 'c';
        // else
        //     c[i] = delim;
    }
    c[n - 1] = '\0';
    fputs( c, fp );
    fclose( fp );
    printf( "Complete.\n" );

    printf( "Testing get_n_char.\n" );
    fp = fopen( "tmp.txt", "r" );
    char * buf = ( char * ) malloc( n );
    get_delim_char( &buf, &n, &delim, fp );
    printf( "Found delim, %c, after %ld chars.\n", delim, n );
    printf( "Buf: |%s|\n", buf );

    free( buf );
    fclose( fp );
    printf( "Complete.\n" );

    printf( "Removing tmp file.\n" );
    remove( "tmp.txt" );
    printf( "Complete.\n" );

    return 0;
}

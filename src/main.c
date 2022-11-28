#include "algorithm.h"
#include "common_math.h"
#include "io.h"
#include "ranges.h"

#include <assert.h>

void
print_cf( const complex_f c ) {
    printf( "%f + %fi\n", crealf( c ), cimagf( c ) );
}
void
print_clf( const complex_lf c ) {
    printf( "%f + %fi\n", crealf( c ), cimagf( c ) );
}
void
print_cllf( const complex_llf c ) {
    printf( "%f + %fi\n", crealf( c ), cimagf( c ) );
}

void
square( const void ** f, void ** dst ) {
    // *dst is mem location of storage
    float * destination = ( float * ) ( *dst );
    *destination = *( float * ) ( *f ) * *( float * ) ( *f );
}

void
print( const void ** f, void ** dst ) {
    char * buf = ( char * ) malloc( 10 );
    snprintf( buf, 10, "%g\n", *( float * ) ( *f ) );
    *( char ** ) ( *dst ) = ( void * ) buf;
}

int
main() {
    size_t n = 5;

    float * test_f = linspace_f( -5.5, 5.5, n, true );

    for ( size_t i = 0; i < n; ++i ) { printf( "%f\n", test_f[i] ); }


    rrange_t range = get_rrange( ( void * ) test_f, n, sizeof( test_f[0] ) );

    putchar( '\n' );

    for ( size_t i = 0; i < n; ++i ) {
        printf( "%f\n", *( float * ) at( range, i ) );
    }

    putchar( '\n' );

    char ** transformed_range = transform( range, print, sizeof( char * ) );

    for ( size_t i = 0; i < n; ++i ) {
        printf( "%s", ( char * ) transformed_range[i] );
    }

    putchar( '\n' );

    tr_range_t tr = transform_arr( ( void * ) test_f, n, sizeof( float ),
                                   square, sizeof( float ) );

    for ( size_t i = 0; i < n; ++i ) {
        printf( "%f\n", *( float * ) at( tr, i ) );
    }

    free( test_f );
    free( transformed_range );

    return 0;
}


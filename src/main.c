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


    rrange_t range =
        range_create( ( void * ) test_f, n, sizeof( test_f[0] ), false );

    putchar( '\n' );

    for ( size_t i = 0; i < n; ++i ) {
        printf( "%f\n", *( float * ) at( range, i ) );
    }

    putchar( '\n' );

    float    a1 = M_PI;
    uint64_t a2 = 121251258699;
    char     a3[] = "Hello world";

    printf( "a1: %f, size  = %ld\n", a1, sizeof( a1 ) );
    printf( "a2: %llu, size = %ld\n", a2, sizeof( a2 ) );
    printf( "a3: %s, size  = %ld\n", a3, strlen( a3 ) );

    size_t sizes[] = { sizeof( a1 ), sizeof( a2 ), sizeof( a3 ) };
    args   a =
        args_create( sizes, 3, ( void * ) &a1, ( void * ) &a2, ( void * ) &a3 );

    printf( "args_verify: %s\n", args_verify( a, 3, ( void * ) &a1,
                                              ( void * ) &a2, ( void * ) &a3 ) ?
                                     "true" :
                                     "false" );

    args_destroy( a );
    range_destroy( range );
    free( test_f );

    return 0;
}


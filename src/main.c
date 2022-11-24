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

int
main() {
    size_t n = 5;

    float * test_f = linspace_f( -5.5, 5.5, n, true );

    for ( size_t i = 0; i < n; ++i ) { printf( "%f\n", test_f[i] ); }

    printf( "test_f[0] = %p, test_f[%ld] = %p\n", ( void * ) test_f, n,
            ( void * ) ( test_f + n ) );

    range_t range = get_range( ( void * ) test_f, n, sizeof( test_f[0] ) );

    printf( "begin = %p, end = %p\n", range.begin, range.end );

    for ( size_t i = 0; i < n; ++i ) {
        printf( "%f\n", *( float * ) access_range( range, i ) );
    }

    free( test_f );

    return 0;
}


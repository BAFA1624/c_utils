#include "algorithm.h"
#include "io.h"

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
    size_t n = 60;

    complex_f a = 5.5 + I * -4.5;
    complex_f b = -4.5 + I * 5.5;

    printf( "a: " );
    print_cf( a );
    printf( "b: " );
    print_cf( b );

    complex_f * test_cf = linspace_cf( a, b, n );

    puts( "complex_f:" );
    for ( size_t i = 0; i < n; ++i ) { print_cf( test_cf[i] ); }
    puts( "" );

    free( test_cf );

    return 0;
}


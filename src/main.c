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

    float * test_cf = linspace_f( -5.5, 5.5, n, true );

    puts( "complex_f:" );
    for ( size_t i = 0; i < n; ++i ) { printf( "%f\n", test_cf[i] ); }
    puts( "" );

    free( test_cf );

    return 0;
}


#include "algorithm.h"
#include "io.h"

#include <assert.h>

int
main() {
    size_t n = 60;

    float * test_f  = linspace( ( float ) -5.5, ( float ) 4.5, n );
    double * test_d = linspace( ( double ) 5.5, ( double ) -4.5, n );
    long double * test_ld =
        linspace( ( long double ) -5.5, ( long double ) 4.5, n );

    puts( "Float linspace:" );
    for ( size_t i = 0; i < n; ++i ) { printf( "%f  ", test_f[i] ); }
    puts( "\n\nDouble linspace:" );
    for ( size_t i = 0; i < n; ++i ) { printf( "%lf  ", test_d[i] ); }
    puts( "\n\nLong double linspace:" );
    for ( size_t i = 0; i < n; ++i ) { printf( "%Lf  ", test_ld[i] ); }
    puts( "\n" );

    free( test_f );
    free( test_d );
    free( test_ld );

    return 0;
}


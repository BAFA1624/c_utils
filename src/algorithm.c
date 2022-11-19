#include "algorithm.h"

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

float *
linspace_f( float start, const float end, const size_t n ) {
    float * const arr = ( float * ) malloc( n * sizeof( float ) );
    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const float delta = ( end - start ) / n;
    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}

double *
linspace_lf( double start, const double end, const size_t n ) {
    double * const arr = ( double * ) malloc( n * sizeof( double ) );
    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const double delta = ( end - start ) / n;
    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}

long double *
linspace_llf( long double start, const long double end, const size_t n ) {
    long double * arr = ( long double * ) malloc( n * sizeof( long double ) );
    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const long double delta = ( end - start ) / n;
    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}

complex_f *
linspace_cf( complex_f start, const complex_f end, const size_t n ) {
    complex_f * const arr = ( complex_f * ) malloc( n * sizeof( complex_f ) );
    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const complex_f delta = ( crealf( end ) - crealf( start )
                              + I * ( cimagf( end ) - cimagf( start ) ) )
                            / n;

    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}

complex_lf *
linspace_clf( complex_lf start, const complex_lf end, const size_t n ) {
    complex_lf * const arr =
        ( complex_lf * ) malloc( n * sizeof( complex_lf ) );
    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const complex_lf delta = ( creal( end ) - creal( start )
                               + I * ( cimag( end ) - cimag( start ) ) )
                             / n;

    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}

complex_llf *
linspace_cllf( complex_llf start, const complex_llf end, const size_t n ) {
    complex_llf * const arr =
        ( complex_llf * ) malloc( n * sizeof( complex_llf ) );

    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const complex_llf delta = ( creall( end ) - creall( start )
                                + I * ( cimagl( end ) - cimagl( start ) ) )
                              / n;

    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}


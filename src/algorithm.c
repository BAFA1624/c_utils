#include "algorithm.h"

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


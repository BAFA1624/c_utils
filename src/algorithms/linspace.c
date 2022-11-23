#include "linspace.h"

float *
linspace_f( float start, const float end, const size_t n,
            const bool endpoint ) {
    float * const arr = ( float * ) malloc( n * sizeof( float ) );
    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const float delta = ( end - start ) / ( endpoint ? n - 1 : n );
    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}

double *
linspace_lf( double start, const double end, const size_t n,
             const bool endpoint ) {
    if ( endpoint ) {
        return linspace_lf( start, end, n + 1, false );
    }

    double * const arr = ( double * ) malloc( n * sizeof( double ) );
    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const double delta = ( end - start ) / ( endpoint ? n - 1 : n );
    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}

long double *
linspace_llf( long double start, const long double end, const size_t n,
              const bool endpoint ) {
    long double * arr = ( long double * ) malloc( n * sizeof( long double ) );
    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const long double delta = ( end - start ) / ( endpoint ? n - 1 : n );
    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}

complex_f *
linspace_cf( complex_f start, const complex_f end, const size_t n,
             const bool endpoint ) {
    complex_f * const arr = ( complex_f * ) malloc( n * sizeof( complex_f ) );
    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }
    const complex_f delta = ( end - start ) / ( endpoint ? n - 1 : n );

    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}

complex_lf *
linspace_clf( complex_lf start, const complex_lf end, const size_t n,
              const bool endpoint ) {
    if ( endpoint ) {
        return linspace_clf( start, end, n + 1, false );
    }

    complex_lf * const arr =
        ( complex_lf * ) malloc( n * sizeof( complex_lf ) );
    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const complex_lf delta = ( end - start ) / ( endpoint ? n - 1 : n );

    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}

complex_llf *
linspace_cllf( complex_llf start, const complex_llf end, const size_t n,
               const bool endpoint ) {
    if ( endpoint ) {
        return linspace_cllf( start, end, n + 1, false );
    }

    complex_llf * const arr =
        ( complex_llf * ) malloc( n * sizeof( complex_llf ) );

    if ( !arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const complex_llf delta = ( end - start ) / ( endpoint ? n - 1 : n );

    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }

    return arr;
}


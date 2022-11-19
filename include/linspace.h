#ifndef LINSPACE_H
#define LINSPACE_H

#include "utility_macros.h"

#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

float *
linspace_f( float start, const float end, const size_t n );
double *
linspace_lf( double start, const double end, const size_t n );
long double *
linspace_llf( long double start, const long double end, const size_t n );
complex_f *
linspace_cf( complex_f start, const complex_f end, const size_t n );
complex_lf *
linspace_clf( complex_lf start, const complex_lf end, const size_t n );
complex_llf *
linspace_cllf( complex_llf start, const complex_llf end, const size_t n );

// clang-format off

#define linspace( start, end, n )\
    _Generic( ( start ),\
            float: linspace_f,\
            double: linspace_lf,\
            long double: linspace_llf,\
            complex_f: linspace_cf,\
            complex_lf: linspace_clf,\
            complex_llf: linspace_cllf)( ( start ), ( end ), ( n ) )

// clang-format on

#endif

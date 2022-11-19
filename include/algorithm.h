#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "utility_macros.h"

#include <complex.h> // _Complex
#include <stdint.h>  // intN_t, uintN_t
#include <stdlib.h>  // malloc

// TODO: REMOVE perror CALLS AFTER FINISHING OWN ERROR HANDLING LIB
#include <stdio.h> // perror, fprintf

// Defines

// Typedefs
typedef _Complex float complex_f;
typedef _Complex double complex_lf;
typedef _Complex long double complex_llf;

// Signed integer variants

// Unsigned integer variants

// Floating point variants
float *
linspace_f( float start, const float end, const size_t n );
double *
linspace_lf( double start, const double end, const size_t n );
long double *
linspace_llf( long double start, const long double end, const size_t n );

// Complex number variants
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

#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#include <math.h>
#include <stdlib.h>

typedef struct POLYNOMIAL_F
{
    size_t  n_coeffs;
    float * coeffs;
    float * powers;
} poly_f;

typedef struct POLYNOMIAL_LF
{
    size_t   n_coeffs;
    double * coeffs;
    double * powers;
} poly_lf;

typedef struct POLYNOMIAL_LLF
{
    size_t        n_coeffs;
    long double * coeffs;
    long double * powers;
} poly_llf;

float eval_poly_f( const poly_f * p, const float x );

double eval_poly_lf( const poly_lf * p, const double x );

long double eval_poly_llf( const poly_llf * p, const long double x );

// clang-format off

#define eval_poly(poly, x)\
    _Generic( (x),\
            float: eval_poly_f,\
            double: eval_poly_lf,\
            long double: eval_poly_llf )\
        ( ( poly ), ( x ) )

// clang-format on

#endif

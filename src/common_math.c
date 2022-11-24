#include "common_math.h"

float
eval_poly_f( const poly_f * p, const float x ) {
    float y = 0;
    for ( size_t i = 0; i < p->n_coeffs; ++i ) {
        y += p->coeffs[i] * powf( x, p->powers[i] );
    }
    return y;
}

double
eval_poly_lf( const poly_lf * p, const double x ) {
    double y = 0;
    for ( size_t i = 0; i < p->n_coeffs; ++i ) {
        y += p->coeffs[i] * pow( x, p->powers[i] );
    }
    return y;
}

long double
eval_poly_llf( const poly_llf * p, const long double x ) {
    long double y = 0;
    for ( size_t i = 0; i < p->n_coeffs; ++i ) {
        y += p->coeffs[i] * powl( x, p->powers[i] );
    }
    return y;
}


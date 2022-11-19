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
typedef _Complex float       complex_f;
typedef _Complex double      complex_lf;
typedef _Complex long double complex_llf;

// Signed integer variants
int8_t *  linspace_i8( int8_t start, const int8_t end, const size_t n );
int16_t * linspace_i16( int16_t start, const int16_t end, const size_t n );
int64_t * linspace_i32( int32_t start, const int32_t end, const size_t n );
int32_t * linspace_i64( int64_t start, const int64_t end, const size_t n );

// Unsigned integer variants
uint8_t *  linspace_u8( uint8_t start, const uint8_t end, const size_t n );
uint16_t * linspace_u16( uint16_t start, const uint16_t end, const size_t n );
uint32_t * linspace_u32( uint32_t start, const uint32_t end, const size_t n );
uint64_t * linspace_u64( uint64_t start, const uint64_t end, const size_t n );

// Floating point variants
float *       linspace_f( float start, const float end, const size_t n );
double *      linspace_lf( double start, const double end, const size_t n );
long double * linspace_llf( long double start, const long double end,
                            const size_t n );

// Complex number variants
complex_f * linspace_cf( complex_f start, const complex_f end, const size_t n );
complex_lf *  linspace_clf( complex_lf start, const complex_lf end,
                            const size_t n );
complex_llf * linspace_cllf( complex_llf start, const complex_llf end,
                             const size_t n );

// clang-format off

#define linspace( start, end, n )\
    _Generic( ( start ),\
            int8_t: linspace_i8,\
            int16_t: linspace_i16,\
            int32_t: linspace_i32,\
            int64_t: linspace_i64,\
            uint8_t: linspace_u8,\
            uint16_t: linspace_u16,\
            uint32_t: linspace_u32,\
            uint64_t: linspace_u64,\
            float: linspace_f,\
            double: linspace_lf,\
            long double: linspace_llf,\
            complex_f: linspace_cf,\
            complex_lf: linspace_clf,\
            complex_llf: linspace_cllf)( ( start ), ( end ), ( n ) )

// clang-format on

#endif

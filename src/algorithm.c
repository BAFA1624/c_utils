#include "algorithm.h"

#ifdef SAFE_MATH
    #include <inttypes.h>

    #define DECL_SAFE_ADD( type, suffix ) \
        static type safe_add_##suffix( const type l, const type r )

    #define OVR_FLW_ERR( type, fmt, l, r )                                     \
        fprintf( stderr,                                                       \
                 "Overflow error encountered: " fmt " + " fmt " (%s) - %s:%d", \
                 l, r, #type, __FILE__, __LINE__ )

    #define UDR_FLW_ERR( type, fmt, l, r )                     \
        fprintf( stderr,                                       \
                 "Underflow error encountered: " fmt " + " fmt \
                 " (%s) - %s:%d.",                             \
                 l, r, #type, __FILE__, __LINE__ )

DECL_SAFE_ADD( int8_t, i8 ) {
    // Overflow
    if ( l > 0 && r > INT8_MAX - l ) {
        OVR_FLW_ERR( int8_t, "%PRIi8", l, r );
        exit( -1 );
    }
    // Underflow
    else if ( l < 0 && r < INT8_MIN ) {
        UDR_FLW_ERR( int8_t, "%PRIi8", l, r );
        exit( -1 );
    }
    else {
        return l + r;
    }
}
DECL_SAFE_ADD( int16_t, i16 )
DECL_SAFE_ADD( int32_t, i32 );
DECL_SAFE_ADD( int64_t, i64 );

DECL_SAFE_ADD( uint8_t, u8 );
DECL_SAFE_ADD( uint16_t, u16 );
DECL_SAFE_ADD( uint32_t, u32 );
DECL_SAFE_ADD( uint64_t, u64 );

DECL_SAFE_ADD( float, f );
DECL_SAFE_ADD( double, lf );
DECL_SAFE_ADD( long double, llf );

DECL_SAFE_ADD( complex_f, cf );
DECL_SAFE_ADD( complex_lf, clf );
DECL_SAFE_ADD( complex_llf, cllf );

#endif

int8_t *
linspace_i8( int8_t start, const int8_t end, const size_t n ) {
    int8_t * arr = ( int8_t * ) malloc( n * sizeof( int8_t ) );
    if ( !arr ) {
        // TODO: USE OWN ERROR HANDLING LIBRARY
        perror( "malloc" );
        exit( -1 );
    }
    const int8_t delta = ;
    for ( size_t i = 0; i < n; ++i ) {
        arr[i] = start;
        start += delta;
    }
}


#include "ranges.h"

range_t
get_range( void * const arr, const size_t size, const size_t element_size ) {
    const range_t range = {
        .begin = arr,
        .end = ( void * const ) ( ( char * const ) arr + size * element_size ),
        .element_size = element_size,
    };
    return range;
}

const_range_t
get_const_range( const void * const arr, const size_t size,
                 const size_t element_size ) {
    const const_range_t range = {
        .begin        = arr,
        .end          = ( const void * const ) ( ( const char * const ) arr
                                        + size * element_size ),
        .element_size = element_size,
    };
    return range;
}


#include "memory.h"

void
copy( void * const restrict dest, const void * const restrict src,
      const size_t dest_sz, const size_t n ) {
    if ( dest == NULL || src == NULL || dest_sz == 0 || n == 0 )
        return;

    // All forward copying normally.
    // Therefore, doesn't matter if dest is before src & overlaps.
    // If src is before dest & overlaps, vals required for later copying
    // will be overwritten before copying. Backwards copy for that case.
    if ( ( uintptr_t ) src <= ( uintptr_t ) dest
         && ( uintptr_t ) src + dest_sz >= ( uintptr_t ) dest ) {
        char * d_ptr = ( char * ) ( ( uintptr_t ) dest + dest_sz - 1 );
        char * s_ptr = ( char * ) ( ( uintptr_t ) src
                                    + ( n <= dest_sz ? n : dest_sz ) - 1 );

        while ( ( uintptr_t ) d_ptr >= ( uintptr_t ) dest
                && ( uintptr_t ) d_ptr >= ( uintptr_t ) d_ptr - n ) {
            *( d_ptr-- ) = *( s_ptr-- );
        }
    }
    else {
        char * d_ptr = ( char * ) dest;
        char * s_ptr = ( char * ) src;

        while (
            ( size_t ) ( ( uintptr_t ) d_ptr - ( uintptr_t ) dest ) < dest_sz
            && ( size_t ) ( ( uintptr_t ) d_ptr - ( uintptr_t ) dest ) < n ) {
            *( d_ptr++ ) = *( s_ptr++ );
        }
    }
}

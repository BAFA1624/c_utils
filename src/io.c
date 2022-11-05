#include "io.h"

static const size_t max_buffer_alloc = MAX_IO_BUFFER_SIZE;

size_t
_min_( const size_t * const lhs, const size_t * const rhs ) {
    return ( ( *lhs <= *rhs ) ? *lhs : *rhs );
}

char *
get_n_char( char ** const buf, size_t * const restrict n,
            FILE * const  stream ) {
    // If *buf == NULL, allocate memory.
    char * tmp;
    if ( !buf ) {
        tmp = ( char * ) malloc( _min_( n, &max_buffer_alloc ) );
        if ( !( tmp ) ) {
            printf( "Failed to allocate memory for buffer.\n" );
            exit( -1 );
        }
    }
    else {
        tmp = *buf;
    }

    // Begin reading n - 1 chars into buffer.

    if ( !buf ) {
        tmp[_min_( n, &max_buffer_alloc ) - 1] = '\0';
    }
    else {
        tmp[*n - 1] = '\0';
    }

    printf( "%ld\n", ( ( !buf ) ? _min_( n, &max_buffer_alloc ) : *n ) - 1 );

    size_t pos = 0;
    while ( feof( stream ) == 0
            && pos < ( ( !buf ) ? _min_( n, &max_buffer_alloc ) : *n ) - 1 ) {
        tmp[pos++] = getchar();
    }

    *n = pos;

    return tmp;
}

/*char *
get_delim_char( char ** const buf, const char * const restrict delim,
                FILE * const  stream ) {
    char * tmp;
    if ( !buf ) {
        tmp = ( char * ) malloc();
    }
    else {
        tmp = *buf;
    }
}*/


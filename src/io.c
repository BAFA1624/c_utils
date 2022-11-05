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
    size_t allocated_memory = 0;
    if ( !buf ) {
        allocated_memory = _min_( n, &max_buffer_alloc );
        tmp = ( char * ) malloc( allocated_memory );
        if ( !( tmp ) ) {
            perror( "malloc" );
            exit( EXIT_FAILURE );
        }
    }
    else {
        allocated_memory = *n;
        tmp = *buf;
    }

    // Begin reading n - 1 chars into buffer.
    tmp[allocated_memory - 1] = '\0';

    size_t pos = 0;
    while ( !feof( stream ) && !ferror( stream )
            && pos < allocated_memory - 1 ) {
        // printf( "%ld: Retrieving char.\n", pos );
        tmp[pos++] = getc( stream );
    }

    // Check if EOF or error indicators are set
    if ( !!feof( stream ) ) {
        pos--;
    }
    if ( !!ferror( stream ) ) {
        perror( "getc" );
    }
    clearerr( stream );

    // Return number of chars read in.
    *n = pos;

    // pos + 1 = size of buffer required to store read-in data.
    if ( pos + 1 < allocated_memory ) {
        tmp = ( char * ) realloc( ( void * ) tmp, pos + 1 );
        tmp[pos] = '\0';
    }

    return tmp;
}

/*char *
get_delim_char( char ** const buf, const char * const restrict delim,
                FILE * const  stream ) {
    char * tmp;
    if ( !buf ) {
        tmp = ( char * ) malloc( max_buffer_alloc );
    }
    else {
        tmp = *buf;
    }
}*/

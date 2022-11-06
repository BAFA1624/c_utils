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

    // Return number of chars read in.
    *n = pos;

    // pos + 1 = size of buffer required to store read-in data.
    if ( pos + 1 < allocated_memory ) {
        tmp = ( char * ) realloc( ( void * ) tmp, pos + 1 );
        if ( !tmp ) {
            perror( "realloc" );
            exit( EXIT_FAILURE );
        }
        tmp[pos] = '\0';
    }

    // Check if EOF or error indicators are set
    if ( !!feof( stream ) ) {
        pos--;
    }
    if ( !!ferror( stream ) ) {
        perror( "getc" );
    }
    clearerr( stream );

    return tmp;
}

char *
get_delim_char( char ** const buf, size_t * const restrict n,
                const char * const restrict delim, FILE * const stream ) {
    char * tmp;
    size_t allocated_memory;
    if ( !buf ) {
        allocated_memory = _min_( n, &max_buffer_alloc );
        tmp = ( char * ) malloc( allocated_memory );
    }
    else {
        tmp = *buf;
        allocated_memory = *n;
    }

    size_t pos = 0;
    while ( pos < allocated_memory - 1 && !feof( stream )
            && !ferror( stream ) ) {
        tmp[pos] = getc( stream );
        if ( tmp[pos] == *delim ) {
            break;
        }
        pos++;
    }

    *n = pos;

    if ( pos + 1 < allocated_memory ) {
        tmp = ( char * ) realloc( tmp, pos + 1 );
        if ( !tmp ) {
            perror( "realloc" );
            exit( EXIT_FAILURE );
        }
    }
    tmp[pos] = '\0';

    // Check if EOF or error indicators are set
    if ( !!feof( stream ) ) {
        pos--;
    }
    if ( !!ferror( stream ) ) {
        perror( "getc" );
    }
    clearerr( stream );

    return tmp;
}

// Returns 0 for invalid input.
// TODO: implement string functions for this.
int
valid_input( char ** const restrict response_buf, size_t input_buffer_size,
             const char * const valid_chars ) {
    // Get input
    char delim = '\n';
    get_delim_char( response_buf, &input_buffer_size, &delim, stdin );

    for ( char * c_input = response_buf[0]; *c_input != '\0'; c_input++ ) {
        for ( const char * c_valid = valid_chars; *c_valid != '\0';
              c_valid++ ) {
            if ( *c_input == *c_valid ) {
                return 1;
            }
        }
    }
    return 0;
}


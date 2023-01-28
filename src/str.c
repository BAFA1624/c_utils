#include "str.h"

size_t
len_cstr( const char * restrict s ) {
    const uintptr_t start = ( uintptr_t ) s;
    while ( *s != '\0' ) s++;
    return ( size_t ) ( ( uintptr_t ) s - start );
}

int
comp_cstr( const char * const lhs, const char * const rhs ) {
    const char *lptr, *rptr;

    for ( lptr = lhs; *lptr != '\0'; lptr++ ) {
        for ( rptr = rhs; *rptr != '\0'; rptr++ ) {
            if ( *lptr == *rptr )
                return 0;
        }
    }

    return 1;
}

size_t
count_cstr( const char * const buf, const size_t buf_sz,
            const char * const target, const size_t target_sz ) {
    if ( buf == NULL || target == NULL )
        return 0;
    if ( buf_sz == 0 || target_sz == 0 || target_sz > buf_sz )
        return 0;

    const char *l = buf, *r = l;
    size_t      n = 0;

    while ( *l != '\0' ) {
    search:
        if ( *l == target[0] ) {
            size_t pos = 0;
            while ( pos < target_sz ) {
                if ( *r != target[pos++] ) {
                    l = r;
                    goto search;
                }
                r++;
            }
            r--;
            l = r;
            n++;
        }
        l++;
        r++;
    }

    return n;
}

size_t
find_first_cstr( const char * const buf, const size_t buf_sz,
                 const char * const target, const size_t target_sz ) {
    if ( buf == NULL || target == NULL )
        return buf_sz;
    if ( buf_sz == 0 || target_sz == 0 || target_sz > buf_sz )
        return buf_sz;

    size_t pos = 0;
    while ( buf[pos] != '\0' ) {
    search:
        if ( buf[pos] == target[0] ) {
            size_t search_pos = 1;
            while ( search_pos < target_sz ) {
                if ( buf[pos + search_pos] != target[search_pos] )
                    goto search;
                search_pos++;
            }
            return pos;
        }
        pos++;
    }

    return buf_sz;
}

size_t *
find_pos_cstr( const char * const buf, const size_t buf_sz,
               const char * const target, const size_t target_sz, size_t * n ) {
    if ( buf == NULL || target == NULL ) {
        *n = 0;
        return NULL;
    }
    if ( buf_sz == 0 || target_sz == 0 || target_sz > buf_sz ) {
        *n = 0;
        return NULL;
    }

    // Result storage
    size_t   result_sz = 0;
    size_t   result_cap = 10;
    size_t * result = malloc( result_cap * sizeof( size_t ) );
    if ( !result ) {
        perror( "malloc" );
        exit( EXIT_FAILURE );
    }

    // Check through buffer to find all occurences of target.
    const char * buf_ptr = buf;
    while ( ( size_t ) ( ( uintptr_t ) buf_ptr - ( uintptr_t ) buf )
            != buf_sz ) {
    search:
        if ( *buf_ptr == target[0] ) {
            size_t forward_check = 1;
            while ( forward_check < target_sz ) {
                if ( buf_ptr[forward_check] != target[forward_check] )
                    goto search; // target not found.
                forward_check++;
            }

            // Target found!
            // If not enough capacity, realloc.
            if ( result_sz == result_cap ) {
                result_cap *= ( size_t ) 2;
                result = ( size_t * ) realloc( ( void * ) result,
                                               result_cap * sizeof( size_t ) );
                if ( !result ) {
                    perror( "realloc" );
                    exit( EXIT_FAILURE );
                }
            }

            // Save position.
            result[result_sz++] =
                ( size_t ) ( ( uintptr_t ) buf_ptr - ( uintptr_t ) buf );
            buf_ptr = ( char * ) ( ( uintptr_t ) buf_ptr + target_sz - 1 );
        }

        buf_ptr++;
    }

    if ( result_sz != result_cap ) {
        result = ( size_t * ) realloc( ( void * ) result,
                                       result_sz * sizeof( size_t ) );
        if ( !result ) {
            perror( "realloc" );
            exit( EXIT_FAILURE );
        }
    }

    *n = result_sz;
    return result;
}

char **
split_cstr( const char * const buf, const size_t buf_sz,
            const char * const target, const size_t target_sz, size_t * n ) {
    if ( buf == NULL || target == NULL ) {
        *n = 0;
        return NULL;
    }
    if ( buf_sz == 0 || target_sz == 0 || target_sz > buf_sz ) {
        *n = 0;
        return NULL;
    }

    size_t * positions = find_pos_cstr( buf, buf_sz, target, target_sz, n );
    if ( !positions ) {
        *n = 0;
        return NULL;
    }

    char ** result = ( char ** ) malloc( ( *n + 1 ) * sizeof( char * ) );
    if ( !result ) {
        perror( "malloc" );
        exit( EXIT_FAILURE );
    }

    if ( *n == 0 ) {
        free( positions );
        return NULL;
    }

    result[0] = ( char * ) malloc( positions[0] );
    if ( !result[0] ) {
        perror( "malloc" );
        exit( EXIT_FAILURE );
    }
    memcpy( ( void * ) result[0], buf, positions[0] - 1 );

    for ( size_t i = 1; i < *n + 1; ++i ) {
        size_t l = 0, r = 0;
        if ( i == 0 ) {
            l = 0;
            r = positions[0];
        }

        l = positions[i];
        r = positions[i + 1];

        result[i + 1] = ( char * ) malloc( r - l );
        if ( !result[i] ) {
            perror( "malloc" );
            exit( EXIT_FAILURE );
        }

        memcpy( result[i + 1] );
    }

    free( positions );

    return result;
}


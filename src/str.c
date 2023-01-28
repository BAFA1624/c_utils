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

    // Get positions of delimiters in buf.
    size_t * positions = find_pos_cstr( buf, buf_sz, target, target_sz, n );
    if ( !positions ) {
        *n = 0;
        return NULL;
    }

    // find_pos_cstr sets *n to number of delimiters.
    // Therefore, number of substrings = *n + 1;
    char ** result = ( char ** ) malloc( ( *n + 1 ) * sizeof( char * ) );
    if ( !result ) {
        perror( "malloc" );
        exit( EXIT_FAILURE );
    }

    if ( *n == 0 ) {
        free( positions );
        return NULL;
    }

    // Counter for substrings w/ sz = 0, therefore need to skip.
    // result_count keeps track of which result index to store into.
    size_t result_count = 0;
    // Handle first substring manually.
    // Sizeof first substring = index of first delimiter + '\0'.
    if ( positions[0] != 0 ) {
        result[result_count] = ( char * ) malloc( positions[0] + 1 );
        if ( !result[result_count] ) {
            perror( "malloc" );
            exit( EXIT_FAILURE );
        }
        copy( ( void * ) result[result_count], buf, positions[0] + 1,
              positions[0] );
        result[result_count][positions[0]] = '\0';
        result_count++;
    }

    // Handle remaining substrings.
    size_t l = 0, r = 0;
    for ( size_t i = 0; i < *n - 1; ++i ) {
        // Represent start & finish of each substring.
        l = positions[i] + target_sz;
        r = positions[i + 1];
        if ( r - l == 0 )
            continue;

        // Length is r - l + '\0'.
        result[result_count] = ( char * ) malloc( r - l + 1 );
        if ( !result[result_count] ) {
            perror( "malloc" );
            exit( EXIT_FAILURE );
        }
        copy( ( void * ) result[result_count],
              ( void * ) ( ( uintptr_t ) buf + l ), r - l + 1, r - l );
        result[result_count][r - l] = '\0';
        result_count++;
    }

    // Handle final substring.
    if ( positions[*n - 1] != buf_sz - target_sz ) {
        result[result_count] =
            ( char * ) malloc( buf_sz - positions[*n - 1] + target_sz + 1 );
        if ( !result[result_count] ) {
            perror( "malloc" );
            exit( EXIT_FAILURE );
        }

        copy( ( void * ) result[result_count],
              ( void * ) ( ( uintptr_t ) buf + positions[*n - 1] + target_sz ),
              buf_sz - positions[*n - 1] + target_sz + 1,
              buf_sz - positions[*n - 1] + target_sz );

        result[result_count][buf_sz - positions[*n - 1] + target_sz] = '\0';

        result_count++;
    }

    // Remove space allocated for any sz zero strings.
    *n = result_count;
    result = ( char ** ) realloc( ( void * ) result,
                                  result_count * sizeof( char * ) );
    if ( !result ) {
        perror( "realloc" );
        exit( EXIT_FAILURE );
    }

    free( positions );

    return result;
}

char *
replace_cstr( char * buf, const size_t buf_sz, const char * const target,
              const size_t target_sz, const char * const replacement,
              const size_t replacement_sz, size_t * n ) {
    if ( buf == NULL || target == NULL )
        return 0;
    if ( buf_sz == 0 || target_sz == 0 )
        return 0;

    char ** substrings = split_cstr( buf, buf_sz, target, target_sz, n );
    if ( *n == 0 ) {
        free( substrings );
        return buf;
    }

    const size_t final_sz = ( size_t ) ( ( long long ) buf_sz
                                         - ( ( long long ) target_sz
                                             - ( long long ) replacement_sz ) );

    char * result = ( char * ) malloc( final_sz );
    if ( !result ) {
        perror( "malloc" );
        exit( EXIT_FAILURE );
    }

    if ( target_sz >= replacement_sz ) {}
    else {}

    for ( size_t i = 0; i < *n; ++i ) free( substrings[i] );
    free( substrings );

    return result;
}


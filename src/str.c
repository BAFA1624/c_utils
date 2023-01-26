#include "str.h"

#include <stdio.h>

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
    if ( buf_sz == 0 || target_sz == 0 )
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

/*char **
split_cstr( const char * const buf, const size_t sz, const char * delim ) {
    const char *l = buf, *r = buf + sz - 1;

    const size_t delim_len = len_cstr( delim );

    // Count no. times delim appears in buf.
    size_t n = 0;
    do {
    } while ( !l );

    return NULL;
}*/


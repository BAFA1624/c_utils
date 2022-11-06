#include "str.h"

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


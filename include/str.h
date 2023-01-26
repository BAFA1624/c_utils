#ifndef STR_H
#define STR_H

#include <stdlib.h>

size_t len_cstr( const char * const restrict s );

// Returns a count of the target string found in the provided buffer.
size_t count_cstr( const char * const buf, const size_t buf_sz,
                   const char * const target, const size_t target_sz );

// Returns the index positions of the target string found in the provided
// buffer.
size_t * find_pos_cstr( const char * const buf, const size_t buf_sz,
                        const char * const target, size_t * n );

size_t find_first_cstr( const char * const buf, const size_t buf_sz,
                        const char * const target, const size_t target_sz );

size_t replace_cstr( char * const s, const char * const target,
                     const char * const replacement );

int comp_cstr( const char * const lhs, const char * const rhs );

char ** split_cstr( const char * buf, const size_t sz, const char * delim );

#endif

#ifndef STR_H
#define STR_H

#include <stdlib.h>

// Implemented.
// Returns length of a cstring, not including the null char.
size_t len_cstr( const char * const restrict s );

// Implemented
// Returns a count of the target string found in the provided buffer.
size_t count_cstr( const char * const buf, const size_t buf_sz,
                   const char * const target, const size_t target_sz );

// Implemented.
// Returns the index positions of the target string found in the provided
// buffer.
size_t * find_pos_cstr( const char * const buf, const size_t buf_sz,
                        const char * const target, const size_t target_sz,
                        size_t * n );

// Implemented.
// Returns the index of the first occurrence of target in the buffer.
// Returns the index of one-past-the-end if target not found.
size_t find_first_cstr( const char * const buf, const size_t buf_sz,
                        const char * const target, const size_t target_sz );

// TODO
// Returns the number of occurrences of target replaced.
size_t replace_cstr( char * const buf, const char * const target,
                     const char * const replacement );

// Implemented.
// Returns 1 if two cstrings are equal, 0 if not.
int comp_cstr( const char * const lhs, const char * const rhs );

// TODO
// Returns array substrings of buf after being split using delimiter "delim"
// Sets value of "n" to size of resulting array.
char ** split_cstr( const char * const buf, const size_t buf_sz,
                    const char * target, const size_t target_sz, size_t * n );

#endif

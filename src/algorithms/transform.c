#include "transform.h"

tr_range_t
get_tr_range( void * const arr, const size_t n_elements,
              const size_t element_size ) {
    tr_range_t tr = get_range( arr, n_elements, element_size );
    return tr;
}

void *
transform_range( const range_t r, const transform_func f,
                 const size_t new_element_size ) {
    const size_t n = RANGE_SIZE( r );
    void *       transformed_arr = malloc( new_element_size * n );
    if ( !transformed_arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const void * rl_ptr = FRONT( r );
    const void * rr_ptr = BACK( r );
    void *       t_ptr = transformed_arr;

    while ( rl_ptr != rr_ptr ) {
        f( &rl_ptr, &t_ptr );
        rl_ptr = ( void * ) ( ( uintptr_t ) rl_ptr + r.element_size );
        t_ptr = ( void * ) ( ( uintptr_t ) t_ptr + new_element_size );
    }

    return transformed_arr;
}

void *
transform_const_range( const const_range_t r, const transform_func f,
                       const size_t new_element_size ) {
    const size_t n = RANGE_SIZE( r );
    void *       transformed_arr = malloc( new_element_size * n );
    if ( !transformed_arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const void * rl_ptr = FRONT( r );
    const void * rr_ptr = BACK( r );
    void *       t_ptr = transformed_arr;

    while ( rl_ptr != rr_ptr ) {
        f( &rl_ptr, &t_ptr );
        rl_ptr = ( void * ) ( ( uintptr_t ) rl_ptr + r.element_size );
        t_ptr = ( void * ) ( ( uintptr_t ) t_ptr + new_element_size );
    }

    return transformed_arr;
}

tr_range_t
transform_arr( void * const arr, const size_t n, const size_t element_size,
               const transform_func f, const size_t new_element_size ) {
    tr_range_t range = get_tr_range( arr, n, element_size );

    return transform_tr_range( range, f, new_element_size );
}

tr_range_t
transform_tr_range( tr_range_t tr, const transform_func f,
                    const size_t new_element_size ) {
    void * new_arr = malloc( new_element_size * RANGE_SIZE( tr ) );

    const void * rl_ptr = FRONT( tr );
    const void * rr_ptr = BACK( tr );
    void *       t_ptr = new_arr;

    while ( rl_ptr != rr_ptr ) {
        f( &rl_ptr, &t_ptr );
        rl_ptr = ( void * ) ( ( uintptr_t ) rl_ptr + tr.element_size );
        t_ptr = ( void * ) ( ( uintptr_t ) t_ptr + new_element_size );
    }

    return get_tr_range( new_arr, RANGE_SIZE( tr ), new_element_size );
    /*
     * AIM:
     *  - In place transform function.
     * ISSUES:
     *  - Initial & final types may have different sizes. Can't do
     *    a normal realloc as cbein & cend are declared
     *    const void * const and therefore can't be changed.
     * PROCESS:
     *  - If initial size != final size, use specialized realloc.
     *    to change base array size.
     *  - Create temporary array to account for any element overlap.
     *  - Apply function over array, saving results into temporary
     *    array when necessary, then into original when overlap is
     *    accounted for.
     */
}

/*tr_range_t
test_transform_range( const range_t r, const test_transform_func f,
                      const args ) {}*/


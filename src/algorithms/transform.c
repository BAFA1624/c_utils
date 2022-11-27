#include "transform.h"

tr_range_t
get_tr_range( const void * const arr, const size_t n_elements,
              const size_t element_size ) {
    const_range_t range = get_const_range( arr, n_elements, element_size );
    tr_range_t    tr = {
           .range = range,
           .n_transforms = 0,
           .capacity = 10,
           .transforms =
            ( transform_func * ) malloc( sizeof( transform_func ) * 10 ),
    };
    return tr;
}

void
free_tr_range( tr_range_t * tr ) {
    free( tr->transforms );
    tr->capacity = 0;
    tr->n_transforms = 0;
}

void *
transform_range( const range_t r, transform_func f ) {
    const size_t n = RANGE_SIZE( r );
    void *       transformed_arr = malloc( r.element_size * n );
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
        t_ptr = ( void * ) ( ( uintptr_t ) t_ptr + r.element_size );
    }

    return transformed_arr;
}

void *
transform_const_range( const const_range_t r, transform_func f ) {
    printf( "transform_const_range\n" );

    const size_t n = RANGE_SIZE( r );
    void *       transformed_arr = malloc( r.element_size * n );
    if ( !transformed_arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const void * r_ptr = r.cbegin;
    void *       t_ptr = transformed_arr;

    while ( r_ptr != r.cend ) {
        f( &r_ptr, &t_ptr );
        INCR( r, r_ptr );
        INCR( r, t_ptr );
    }

    return transformed_arr;
}

void *
transform_arr( const void * const arr, const size_t n,
               const size_t element_size, transform_func f ) {
    void * transformed_arr = malloc( n * element_size );
    if ( !transformed_arr ) {
        perror( "malloc" );
        exit( -1 );
    }

    const_range_t range = get_const_range( arr, n, element_size );

    return transform_const_range( range, f );
}

tr_range_t
transform_tr_range( tr_range_t tr, transform_func f ) {
    if ( tr.n_transforms == tr.capacity ) {
        tr.transforms = ( transform_func * ) realloc(
            ( void * ) tr.transforms,
            2 * ( tr.capacity * sizeof( transform_func ) ) );
        tr.capacity = 2 * tr.capacity;
    }

    tr.transforms[tr.n_transforms] = f;
    tr.n_transforms++;

    return tr;
}


#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "ranges.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct ARGS_ * args;


args args_create( const size_t * args_sizes, const size_t n, ... );
void args_destroy( args a );

void ** args_at( args a, const size_t i, size_t * sz );

// range_t transform( const range_t r );

bool args_verify( const args a, size_t n, ... );

#endif

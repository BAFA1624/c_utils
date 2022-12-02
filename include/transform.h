#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "ranges.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct ARGS_ * args;


args
args_create( const size_t n, const size_t * args_sizes, T * args );
void
args_destroy( args a );

#endif
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "ranges.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct ARGS_
{
    const size_t n;
    const void ** args;
};


typedef struct ARGS_ args;

#endif

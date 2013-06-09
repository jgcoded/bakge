#ifndef BAKGE_BAKGE_H
#define BAKGE_BAKGE_H

/* Include standard library dependencies */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* GCC-only attributes */
#ifdef __GNUC__
/* Send compiler warning if function return result is not used */
#define BGE_WUNUSED __attribute__((warn_unused_result))
/* Mark a variable as possibly unused in its function  */
#define BGE_UNUSED __attribute__((unused))
/* Factory functions are static class methods that return allocated memory  */
#define BGE_FACTORY static BGE_WUNUSED
#else /* Define them anyways to avoid compilation errors  */
#define BGE_WUNUSED
#define BGE_UNUSED
#endif /* __GNUC__  */


#include "../lib/glfw-2.7.9/include/GL/glfw.h"


/* Include Bakge */
#include <bakge/core/Type.h>
#include <bakge/core/Window.h>

#endif /* BAKGE_BAKGE_H */


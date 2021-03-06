/* *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Paul Holden et al. (See AUTHORS)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * */

#ifndef BAKGE_CORE_TYPE_H
#define BAKGE_CORE_TYPE_H

#include <bakge/Bakge.h>

namespace bakge
{

#define BGE_FAILURE 1
#define BGE_SUCCESS 0
typedef int Result;

typedef unsigned char Byte;
typedef double Seconds;

#ifdef _WIN32
typedef unsigned long long Microseconds;
#else
typedef uint64_t Microseconds;
#endif

/* *
 * GLFW uses doubles for its mouse/scroll motion measurements.
 * Better to just deal with doubles than with casting to integral types
 * */
typedef double DeviceMotion;
typedef double DeviceCoord;

} /* bakge */

#endif /* BAKGE_CORE_TYPE_H */

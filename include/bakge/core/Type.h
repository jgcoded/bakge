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

/*!
 * @file Type.h
 * @brief Bakge type definitions and relevant defined symbols.
 */

#ifndef BAKGE_CORE_TYPE_H
#define BAKGE_CORE_TYPE_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @cond HIDDEN_SYMBOLS
 */
#ifdef _WIN32
typedef UINT64 uint64;
typedef INT64 int64;
typedef UINT32 uint32;
typedef INT32 int32;
#else
typedef uint64_t uint64;
typedef int64_t int64;
typedef uint32_t uint32;
typedef int32_t int32;
#endif /* _WIN32 */
/*! @endcond
 */

/*! @brief Compare with a Result value to determine failure.
 */
#define BGE_FAILURE 1

/*! @brief Compare with a Result value to determine success.
 */
#define BGE_SUCCESS 0

/*! @brief Returned from many Bakge functions to describe operation results.
 *
 * Compare with BGE_FAILURE or BGE_SUCCESS to determine if the method succeeded
 * or failed due to arbitrary errors.
 */
typedef int Result;

#define BGE_SCALAR_EPSILON 0.000001f

#define BGE_RAD_PER_DEG 0.0174532925f

#define BGE_DEG_PER_RAD 57.2957795f

typedef float Scalar;

typedef Scalar Degrees;

typedef Scalar Radians;

/*! @brief An 8-bit type definition. Is not necessarily a printable character.
 */
typedef unsigned char Byte;

/*! @brief Seconds are described as double-precision floating point numbers
 */
typedef double Seconds;

/*! @brief An unsigned 64-bit integral type.
 *
 * A Microsecond is 1 millionth (1 E -6) of a second. The largest duration
 * that can be stored is around 600,000 years, as compared to around 1 minute
 * with a 32 bit unsigned integer.
 */
typedef uint64 Microseconds;

/*! @brief Used to describe mouse/joystick motion or positions.
 */
typedef Scalar Motion;

/*! @brief Used to describe a mouse or screen position
 */
typedef Scalar Coord;

} /* bakge */

#endif /* BAKGE_CORE_TYPE_H */

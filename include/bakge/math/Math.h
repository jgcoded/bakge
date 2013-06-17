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

#ifndef BAKGE_MATH_MATH_H
#define BAKGE_MATH_MATH_H

#include <bakge/Bakge.h>

namespace bakge
{
namespace math
{

#define SCALAR_EPSILON 0.000001
#define RAD_PER_DEG 0.0174532925f
#define DEG_PER_RAD 57.2957795f
typedef float Scalar;
typedef Scalar Degrees;
typedef Scalar Radians;


inline Radians ToRadians(Degrees BGE_NCP Deg)
{
    return (Deg * RAD_PER_DEG);
}


inline Degrees ToDegrees(Radians BGE_NCP Rad)
{
    return (Rad * DEG_PER_RAD);
}

} /* math */
} /* bakge */

#endif /* BAKGE_MATH_MATH_H */

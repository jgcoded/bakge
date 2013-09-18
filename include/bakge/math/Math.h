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
 * @file Math.h
 * @brief Math utility API declarations.
 */

#ifndef BAKGE_MATH_MATH_H
#define BAKGE_MATH_MATH_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Convert a degree value to radians.
 *
 * Convert a degree value to radians.
 *
 * @param[in] Deg Angle value in degrees.
 *
 * @return Angle value in radians.
 */
BGE_INL Radians ToRadians(Degrees BGE_NCP Deg)
{
    return (Deg * BGE_RAD_PER_DEG);
}


/*! @brief Convert a radians value to degrees.
 *
 * Convert a radians value to degrees.
 *
 * @param[in] Rad Angle value in radians.
 *
 * @return Angle value in degrees.
 */
BGE_INL Degrees ToDegrees(Radians BGE_NCP Rad)
{
    return (Rad * BGE_DEG_PER_RAD);
}


/*! @brief Compare the value of two floating-point values.
 *
 * Compare the value of two floating-point values. If the absolute value
 * of the difference of the two values is less than an arbitrary constant,
 * they are considered equal.
 *
 * @param[in] Left A value to compare.
 * @param[in] Right Other value to compare.
 *
 * @return true if the difference between the two values is less than an
 * arbitrary epsilon.
 */
BGE_INL bool ScalarCompare(Scalar BGE_NCP Left, Scalar BGE_NCP Right)
{
    return abs(Right - Left) < BGE_SCALAR_EPSILON;
}


/*! @brief Get the max of two arbitrary variables of arbitrary type.
 *
 * Get the max of two arbitrary variables of arbitrary type. The type T for
 * the template must implement the greater than operator (>).
 *
 * @param[in] A First value to compare.
 * @param[in] B Second value to compare.
 *
 * @return A copy of the greater of the two variables.
 */
template<class T>
BGE_INL T BGE_NCP Max(T BGE_NCP A, T BGE_NCP B)
{
    return (A > B) ? (A) : (B);
}

} /* bakge */

#endif /* BAKGE_MATH_MATH_H */

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

#ifndef BAKGE_MATH_VECTOR4_H
#define BAKGE_MATH_VECTOR4_H

#include <bakge/Bakge.h>

namespace bakge
{
namespace math
{

/* *
 * Vectors are used to represent arbitrary points, or directions (and
 * their magnitudes). The homogeneous fourth coordinate, identified as the w
 * coordinate, distinguishes points from 3D vectors. If w is 0, the Vector4
 * represents a vector with a direction and length, or magnitude. If w is a 1,
 * the Vector4 represents a point in 3D space. This is used to enforce common
 * logic -- a point plus a point is meaningless. A point plus a vector is
 * another point, and a vector plus a vector is another vector. Many operations
 * check this homogeneous coordinate before proceeding, such as scalar
 * multiplication. Dividing a point by a constant is meaningless. Dividing a
 * vector by a constant reduces its magnitude (length).
 * */
class Vector4
{

public:

    Vector4();
    Vector4(Scalar X, Scalar Y, Scalar Z, Scalar W);
    Vector4(Vector4 BGE_NCP Other);
    ~Vector4();

    /* *
     * No real need for them to be friends, just a way to not have to
     * declare them elsewhere
     * */
    friend Vector4 Point(Scalar X, Scalar Y, Scalar Z);
    friend Vector4 Vector(Scalar X, Scalar Y, Scalar Z);
    friend Vector4 UnitVector(Scalar X, Scalar Y, Scalar Z);

    Scalar& operator[](int BGE_NCP At);
    Scalar BGE_NCP operator[](int BGE_NCP At) const;

    Vector4 BGE_NCP operator=(Vector4 BGE_NCP Other);

    Vector4 BGE_NCP operator+=(Vector4 BGE_NCP Other);
    Vector4 BGE_NCP operator-=(Vector4 BGE_NCP Other);

    Vector4 BGE_NCP operator*=(Scalar BGE_NCP Value);
    Vector4 BGE_NCP operator/=(Scalar BGE_NCP Value);

    Vector4 BGE_NCP Normalize();
    Vector4 Normalized() const;

    Scalar LengthSquared() const;
    Scalar Length() const;

    friend Vector4 operator+(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right);
    friend Vector4 operator-(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right);

    friend Vector4 operator*(Vector4 BGE_NCP Left, Scalar BGE_NCP Right);
    friend Vector4 operator/(Vector4 BGE_NCP Left, Scalar BGE_NCP Right);

    friend Scalar Dot(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right);
    friend Vector4 Cross(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right);


private:

    Scalar Val[4];

}; /* Vector4 */

} /* math */
} /* bakge */

#endif /* BAKGE_MATH_VECTOR4_H */


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

/*! @brief 4-component vector for representing 3D vectors or points.
 *
 * Commonly used for representing points or directions in 3D Cartesian space.
 * The homogeneous fourth coordinate is often called the w-coordinate.
 */
class BGE_API Vector4
{
    union
    {
        struct
        {
            Scalar Val[4];
        };

        struct
        {
            Scalar V0, V1, V2, V3;
        };
    };


public:

    static const Vector4 Origin;
    static const Vector4 ZeroVector;

    Vector4();
    Vector4(Scalar X, Scalar Y, Scalar Z, Scalar W);
    Vector4(Vector4 BGE_NCP Other);
    ~Vector4();

    Vector4 operator-() const;

    Scalar& operator[](int At);
    Scalar BGE_NCP operator[](int At) const;

    Vector4 BGE_NCP operator=(Vector4 BGE_NCP Other);
    bool operator==(Vector4 BGE_NCP Other) const;

    Vector4 BGE_NCP operator+=(Vector4 BGE_NCP Other);
    Vector4 BGE_NCP operator-=(Vector4 BGE_NCP Other);
    Vector4 BGE_NCP operator*=(Scalar Value);
    Vector4 BGE_NCP operator/=(Scalar Value);

    Vector4 operator+(Vector4 BGE_NCP Other) const;
    Vector4 operator-(Vector4 BGE_NCP Other) const;
    Vector4 operator*(Scalar Value) const;
    Vector4 operator/(Scalar Value) const;

    Vector4 BGE_NCP Normalize();
    Vector4 Normalized() const;

    Scalar LengthSquared() const;
    Scalar Length() const;

}; /* Vector4 */

BGE_FUNC Scalar Dot(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right);
BGE_FUNC Vector4 Cross(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right);
BGE_FUNC Vector4 Point(Scalar X, Scalar Y, Scalar Z);
BGE_FUNC Vector4 Vector(Scalar X, Scalar Y, Scalar Z);
BGE_FUNC Vector4 UnitVector(Scalar X, Scalar Y, Scalar Z);

} /* bakge */

#endif /* BAKGE_MATH_VECTOR4_H */

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

#include <bakge/Bakge.h>

namespace bakge
{
namespace math
{

Vector4::Vector4()
{
}


Vector4::Vector4(Scalar X, Scalar Y, Scalar Z, Scalar W)
{
    Val[0] = X;
    Val[1] = Y;
    Val[2] = Z;
    Val[3] = W;
}


Vector4::Vector4(Vector4 BGE_NCP Other)
{
}


Vector4::~Vector4()
{
}


Vector4 Point(Scalar X, Scalar Y, Scalar Z)
{
    return Vector4(X, Y, Z, 1);
}


Vector4 Vector(Scalar X, Scalar Y, Scalar Z)
{
    return Vector4(X, Y, Z, 0);
}


Vector4 UnitVector(Scalar X, Scalar Y, Scalar Z)
{
    Scalar Len = sqrt(X * X + Y * Y + Z * Z);
    return Vector4(X / Len, Y / Len, Z / Len, 0);
}


Scalar& Vector4::operator[](int BGE_NCP At)
{
    return *Val;
}


Scalar BGE_NCP Vector4::operator[](int BGE_NCP At) const
{
    return *Val;
}


Vector4 BGE_NCP Vector4::operator=(Vector4 BGE_NCP Other)
{
    return *this; /* Allow cascading assignment */
}


Vector4 BGE_NCP Vector4::operator+=(Vector4 BGE_NCP Other)
{
    return *this;
}


Vector4 BGE_NCP Vector4::operator-=(Vector4 BGE_NCP Other)
{
    return *this;
}


Vector4 BGE_NCP Vector4::operator*=(Scalar BGE_NCP Other)
{
    return *this;
}


Vector4 BGE_NCP Vector4::operator/=(Scalar BGE_NCP Value)
{
    return *this;
}


Vector4 BGE_NCP Vector4::Normalize()
{
    return *this;
}


Vector4 Vector4::Normalized() const
{
    return Vector4(*this);
}


Scalar Vector4::LengthSquared() const
{
    return Scalar(Val[0] * Val[0] + Val[1] * Val[1] + Val[2] * Val[2]);
}


Scalar Vector4::Length() const
{
    return sqrt(LengthSquared());
}


Vector4 operator+(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    return Vector4();
}


Vector4 operator-(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    return Vector4();
}


Vector4 operator*(Vector4 BGE_NCP Left, Scalar BGE_NCP Right)
{
    return Vector4();
}


Vector4 operator/(Vector4 BGE_NCP Left, Scalar BGE_NCP Right)
{
    return Vector4();
}


Scalar Dot(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    return 0;
}


Vector4 Cross(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    return Vector4();
}

} /* math */
} /* bakge */


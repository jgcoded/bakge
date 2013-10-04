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

const Vector4 Vector4::Origin;
const Vector4 Vector4::ZeroVector(0, 0, 0, 0);

Vector4::Vector4()
{
    Val[0] = 0;
    Val[1] = 0;
    Val[2] = 0;
    Val[3] = 1.0;
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
    Val[0] = Other[0];
    Val[1] = Other[1];
    Val[2] = Other[2];
    Val[3] = Other[3];
}


Vector4::~Vector4()
{
}


Vector4 Vector4::operator-() const
{
    return Vector4(-Val[0], -Val[1], -Val[2], -Val[3]);
}


Vector4 Vector4::Point(Scalar X, Scalar Y, Scalar Z)
{
    return Vector4(X, Y, Z, 1.0);
}


Vector4 Vector4::Vector(Scalar X, Scalar Y, Scalar Z)
{
    return Vector4(X, Y, Z, 0);
}


Vector4 Vector4::UnitVector(Scalar X, Scalar Y, Scalar Z)
{
    Scalar Len = sqrt(X * X + Y * Y + Z * Z);

    return Vector4(X / Len, Y / Len, Z / Len, 0);
}


Scalar& Vector4::operator[](int At)
{
    return Val[At];
}


Scalar BGE_NCP Vector4::operator[](int At) const
{
    return Val[At];
}


Vector4 BGE_NCP Vector4::operator=(Vector4 BGE_NCP Other)
{
    Val[0] = Other[0];
    Val[1] = Other[1];
    Val[2] = Other[2];
    Val[3] = Other[3];

    return *this;
}


Vector4 BGE_NCP Vector4::operator+=(Vector4 BGE_NCP Other)
{
    Val[0] += Other[0];
    Val[1] += Other[1];
    Val[2] += Other[2];
    Val[3] += Other[3];

    return *this;
}


Vector4 BGE_NCP Vector4::operator-=(Vector4 BGE_NCP Other)
{
    Val[0] -= Other[0];
    Val[1] -= Other[1];
    Val[2] -= Other[2];
    Val[3] -= Other[3];

    return *this;
}


Vector4 BGE_NCP Vector4::operator*=(Scalar Value)
{
    Val[0] *= Value;
    Val[1] *= Value;
    Val[2] *= Value;
    Val[3] *= Value;

    return *this;
}


Vector4 BGE_NCP Vector4::operator/=(Scalar Value)
{
    Val[0] /= Value;
    Val[1] /= Value;
    Val[2] /= Value;
    Val[3] /= Value;

    return *this;
}

bool Vector4::operator==(Vector4 BGE_NCP Other) const
{
    return ScalarCompare(Val[0], Other.Val[0])
        && ScalarCompare(Val[1], Other.Val[1])
        && ScalarCompare(Val[2], Other.Val[2])
        && ScalarCompare(Val[3], Other.Val[3]);
}


Vector4 BGE_NCP Vector4::Normalize()
{
    Scalar Len = Length();

    Val[0] /= Len;
    Val[1] /= Len;
    Val[2] /= Len;
    Val[3] /= Len;

    return *this;
}


Vector4 Vector4::Normalized() const
{
    Scalar Len = Length();

    return Vector4(Val[0] / Len, Val[1] / Len, Val[2] / Len, Val[3] / Len);
}


Scalar Vector4::LengthSquared() const
{
    return Scalar(Val[0] * Val[0] + Val[1] * Val[1] + Val[2] * Val[2]
                                                + Val[3] * Val[3]);
}


Scalar Vector4::Length() const
{
    return sqrtf(LengthSquared());
}


Scalar Vector4::Dot(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    return Left[0] * Right[0] + Left[1] * Right[1] + Left[2] * Right[2]
                                                    + Left[3] * Right[3];
}


Vector4 Vector4::Cross(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    return Vector4(
        Left[1] * Right[2] - Left[2] * Right[1],
        Left[2] * Right[0] - Left[0] * Right[2],
        Left[0] * Right[1] - Left[1] * Right[0],
        0
    );
}


Vector4 Vector4::operator+(Vector4 BGE_NCP Other) const
{
    return Vector4(Val[0] + Other[0], Val[1] + Other[1], Val[2] + Other[2],
                                                        Val[3] + Other[3]);
}


Vector4 Vector4::operator-(Vector4 BGE_NCP Other) const
{
    return Vector4(Val[0] - Other[0], Val[1] - Other[1], Val[2] - Other[2],
                                                        Val[3] - Other[3]);
}


Vector4 Vector4::operator*(Scalar Value) const
{
    return Vector4(Val[0] * Value, Val[1] * Value, Val[2] * Value,
                                                    Val[3] * Value);
}


Vector4 Vector4::operator/(Scalar Value) const
{
    return Vector4(Val[0] / Value, Val[1] / Value, Val[2] / Value,
                                                    Val[3] / Value);
}

} /* bakge */

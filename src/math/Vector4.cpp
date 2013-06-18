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


Vector4::Vector4(Scalar X, Scalar Y, Scalar Z, int W)
{
    Val[0] = X;
    Val[1] = Y;
    Val[2] = Z;
    this->W = W;
}


Vector4::Vector4(Vector4 BGE_NCP Other)
{
    Val[0] = Other[0];
    Val[1] = Other[1];
    Val[2] = Other[2];
    this->W = Other.W;
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
    return Val[At];
}


Scalar BGE_NCP Vector4::operator[](int BGE_NCP At) const
{
    return Val[At];
}


Vector4 BGE_NCP Vector4::operator=(Vector4 BGE_NCP Other)
{
    Val[0] = Other[0];
    Val[1] = Other[1];
    Val[2] = Other[2];
    W = Other.W;

    /* Allow cascading assignment */
    return *this;
}


Vector4 BGE_NCP Vector4::operator+=(Vector4 BGE_NCP Other)
{
    /* A point plus a point is meaningless */
    BGE_ASSERT_EX(Other.W, "Point addition is invalid")

    Val[0] += Other[0];
    Val[1] += Other[1];
    Val[2] += Other[2];

    return *this;
}


Vector4 BGE_NCP Vector4::operator-=(Vector4 BGE_NCP Other)
{
    /* A point plus a point is meaningless */
    BGE_ASSERT_EX(Other.W, "Point subtraction is invalid")

    Val[0] -= Other[0];
    Val[1] -= Other[1];
    Val[2] -= Other[2];

    return *this;
}


Vector4 BGE_NCP Vector4::operator*=(Scalar BGE_NCP Value)
{
    /* Scalar multiplication is only relevant to vectors */
    BGE_ASSERT_EX(!W, "Not a vector");

    Val[0] *= Value;
    Val[1] *= Value;
    Val[2] *= Value;

    return *this;
}


Vector4 BGE_NCP Vector4::operator/=(Scalar BGE_NCP Value)
{
    /* Scalar division is only relevant to vectors */
    BGE_ASSERT_EX(!W, "Not a vector");
    BGE_ASSERT_EX(!ScalarCompare(Value, 0), "Division by 0")

    Val[0] /= Value;
    Val[1] /= Value;
    Val[2] /= Value;

    return *this;
}

bool Vector4::operator==(Vector4 BGE_NCP Other)
{
    return ScalarCompare(Val[0], Other.Val[0])
        && ScalarCompare(Val[1], Other.Val[1])
        && ScalarCompare(Val[2], Other.Val[2])
        && W == Other.W;
}


Vector4 BGE_NCP Vector4::Normalize()
{
    BGE_ASSERT_EX(!W, "Not a vector");

    return *this /= Length();
}


Vector4 Vector4::Normalized() const
{
    Scalar Len;

    BGE_ASSERT_EX(!W, "Not a vector");

    Len = Length();
    return Vector4(Val[0] / Len, Val[1] / Len, Val[2] / Len, 0);
}


Scalar Vector4::LengthSquared() const
{
    BGE_ASSERT_EX(!W, "Not a vector");

    return Scalar(Val[0] * Val[0] + Val[1] * Val[1] + Val[2] * Val[2]);
}


Scalar Vector4::Length() const
{
    BGE_ASSERT_EX(!W, "Not a vector");

    return sqrt(LengthSquared());
}


Scalar Dot(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    BGE_ASSERT_EX(!Left.W, "Not a vector")
    BGE_ASSERT_EX(!Right.W, "Not a vector")

    return Left[0] * Right[0] + Left[1] * Right[1] + Left[2] * Right[2];
}


Vector4 Cross(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    BGE_ASSERT_EX(!Left.W, "Not a vector")
    BGE_ASSERT_EX(!Right.W, "Not a vector")

    return Vector4(
        Left[1] * Right[2] - Left[2] * Right[1],
        Left[2] * Right[0] - Left[0] * Right[2],
        Left[0] * Right[1] - Left[1] * Right[0],
        0
    );
}

} /* math */
} /* bakge */


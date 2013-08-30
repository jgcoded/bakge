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

Vector3::Vector3()
{
    Val[0] = 0;
    Val[1] = 0;
    Val[2] = 1.0;
}


Vector3::Vector3(Vector3 BGE_NCP Other)
{
    *this = Other;
}


Vector3::Vector3(Scalar X, Scalar Y, Scalar Z)
{
    Val[0] = X;
    Val[1] = Y;
    Val[2] = Z;
}


Vector3::~Vector3()
{
}


Scalar& Vector3::operator[](int BGE_NCP At)
{
    return Val[At];
}


Scalar BGE_NCP Vector3::operator[](int BGE_NCP At) const
{
    return Val[At];
}


Vector3 BGE_NCP Vector3::operator=(Vector3 BGE_NCP Other)
{
    Val[0] = Other[0];
    Val[1] = Other[1];
    Val[2] = Other[2];

    return *this;
}


bool Vector3::operator==(Vector3 BGE_NCP Other) const
{
    return ScalarCompare(Val[0], Other.Val[0])
        && ScalarCompare(Val[1], Other.Val[1])
        && ScalarCompare(Val[2], Other.Val[2]);
}


Vector3 BGE_NCP Vector3::operator+=(Vector3 BGE_NCP Other)
{
    Val[0] += Other[0];
    Val[1] += Other[1];

    return *this;
}


Vector3 BGE_NCP Vector3::operator-=(Vector3 BGE_NCP Other)
{
    Val[0] -= Other[0];
    Val[1] -= Other[1];

    return *this;
}


Vector3 BGE_NCP Vector3::operator*=(Scalar BGE_NCP Value)
{
    Val[0] /= Value;
    Val[1] /= Value;

    return *this;
}


Vector3 BGE_NCP Vector3::operator/=(Scalar BGE_NCP Value)
{
    if(ScalarCompare(Value, 0)){
        return *this;
    }

    Val[0] /= Value;
    Val[1] /= Value;

    return *this;
}


Vector3 Vector3::operator+(Vector3 BGE_NCP Other) const
{
    return Vector3(Val[0] + Other[0], Val[1] + Other[1], Val[2]);
}


Vector3 Vector3::operator-(Vector3 BGE_NCP Other) const
{
    return Vector3(Val[0] - Other[0], Val[1] - Other[1], Val[2]);
}


Vector3 Vector3::operator*(Scalar BGE_NCP Value) const
{
    return Vector3(Val[0] * Value, Val[1] * Value, Val[2]);
}


Vector3 Vector3::operator/(Scalar BGE_NCP Value) const
{
    if(ScalarCompare(Value, 0)){
        return *this;
    }

    return Vector3(Val[0] / Value, Val[1] / Value, Val[2]);
}


Vector3 Vector3::Normalized() const
{
    Scalar Len = Length();

    return Vector3(Val[0] / Len, Val[1] / Len, Val[2]);
}


Scalar Vector3::Length() const
{
    return sqrt(LengthSquared());
}


Scalar Vector3::LengthSquared() const
{
    return Scalar(Val[0] * Val[0] + Val[1] * Val[1]);
}


static Scalar Dot(Vector3 BGE_NCP Left, Vector3 BGE_NCP Right)
{
    return Left[0] * Right[0] + Left[1] * Right[1];
}


static Vector3 UnitVector(Scalar BGE_NCP X, Scalar  BGE_NCP Y, Scalar BGE_NCP Z)
{
    Scalar Len = sqrt(X * X + Y * Y);

    return Vector3(X / Len, Y / Len, Z);
}

} /* bakge */

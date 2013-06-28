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

Vector2::Vector2()
{
    Val[0] = 0;
    Val[1] = 0;
    Val[2] = 1.0;
}


Vector2::Vector2(Scalar X, Scalar Y, Scalar Z)
{
    Val[0] = X;
    Val[1] = Y;
    Val[2] = Z;
}


Vector2::~Vector2()
{
}


Scalar& Vector2::operator[](int BGE_NCP At)
{
    return Val[At];
}


Scalar BGE_NCP Vector2::operator[](int BGE_NCP At) const
{
    return Val[At];
}


Vector2 BGE_NCP Vector2::operator=(Vector2 BGE_NCP Other)
{
    Val[0] = Other[0];
    Val[1] = Other[1];
    Val[2] = Other[2];

    /* Cascading assignment */
    return *this;
}


Vector2 BGE_NCP Vector2::operator+=(Vector2 BGE_NCP Other)
{
    Val[0] += Other[0];
    Val[1] += Other[1];

    return *this;
}


Vector2 BGE_NCP Vector2::operator-=(Vector2 BGE_NCP Other)
{
    Val[0] -= Other[0];
    Val[1] -= Other[1];

    return *this;
}


Vector2 BGE_NCP Vector2::operator*=(Vector2 BGE_NCP Other)
{
    Val[0] *= Other[0];
    Val[1] *= Other[1];

    return *this;
}


Vector2 BGE_NCP Vector2::operator/=(Vector2 BGE_NCP Other)
{
    Val[0] /= Other[0];
    Val[1] /= Other[1];

    return *this;
}


Vector2 BGE_NCP Vector2::operator/=(Scalar Value)
{

    if(ScalarCompare(Value, 0)){
        printf("Division by 0. Cancelling operation\n");
        return *this;
    }

    Val[0] /= Value;
    Val[1] /= Value;

    return *this;
}


bool BGE_NCP Vector2::operator==(Vector2 BGE_NCP Other)
{

    return Val[0] == Other[0] &&
           Val[1] == Other[1] &&
           Val[2] == Other[2];
}


Vector2 Vector2::Normalized() const
{
    Scalar Len = Length();
    return Vector2(Val[0] / Len, Val[1] / Len, Val[2]);
}


Scalar Vector2::Length() const
{

    return sqrt(LengthSquared());
}


Scalar Vector2::LengthSquared() const
{

    return Scalar(Val[0] * Val[0] + Val[1] * Val[1]);
}


static Vector2 Normalize(Vector2 BGE_NCP Other)
{
    Scalar Len = Other.Length();
    return Vector2(Other[0] / Len, Other[1] / Len, Other[2]);
}


static Scalar Dot(Vector2 BGE_NCP Left, Vector2 BGE_NCP Right)
{

    return Left[0] * Right[0] + Left[1] * Right[2];
}

} /* math */
} /* bakge */
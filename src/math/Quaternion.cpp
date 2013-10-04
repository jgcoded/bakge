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

Quaternion::Quaternion()
{
    Val[0] = 0.0f;
    Val[1] = 0.0f;
    Val[2] = 0.0f;
    Val[3] = 1.0f;
}


Quaternion::Quaternion(Vector4 BGE_NCP V, Scalar R)
{
    Val[0] = V[0];
    Val[1] = V[1];
    Val[2] = V[2];
    Val[3] = R;
}


Quaternion::Quaternion(Vector4 BGE_NCP Components)
{
    Val[0] = Components[0];
    Val[1] = Components[1];
    Val[2] = Components[2];
    Val[3] = Components[3];
}


Quaternion::Quaternion(Scalar X, Scalar Y, Scalar Z, Scalar W)
{
    Val[0] = X;
    Val[1] = Y;
    Val[2] = Z;
    Val[3] = W;
}


Quaternion::Quaternion(Quaternion BGE_NCP Other)
{
    Val[0] = Other.Val[0];
    Val[1] = Other.Val[1];
    Val[2] = Other.Val[2];
    Val[3] = Other.Val[3];
}


Quaternion::~Quaternion()
{
}


Quaternion BGE_NCP Quaternion::operator=(Quaternion BGE_NCP Other)
{
    Q0 = Other.Q0;
    Q1 = Other.Q1;
    Q2 = Other.Q2;
    Q3 = Other.Q3;

    return *this;
}


Matrix Quaternion::ToMatrix() const
{
    return Matrix(
        1 - (2 * Val[1] * Val[1]) - (2 * Val[2] * Val[2]),
        (2 * Val[0] * Val[1]) + (2 * Val[2] * Val[3]),
        (2 * Val[0] * Val[2]) - (2 * Val[1] * Val[3]),
        0,
        (2 * Val[0] * Val[1]) - (2 * Val[2] * Val[3]),
        1 - (2 * Val[0] * Val[0]) - (2 * Val[2] * Val[2]),
        (2 * Val[1] * Val[2]) + (2 * Val[3] * Val[0]),
        0,
        (2 * Val[0] * Val[2]) + (2 * Val[1] * Val[3]),
        (2 * Val[1] * Val[2]) - (2 * Val[0] * Val[3]),
        1 - (2 * Val[0] * Val[0]) - (2 * Val[1] * Val[1]),
        0,
        0, 0, 0, 1
    );
}


Radians Quaternion::GetAngle() const
{
    return acosf(Val[3]) * 2.0f;
}


Vector4 Quaternion::GetAxis() const
{
    Scalar Inv = 1.0f / sinf(acosf(Val[3]));

    return Vector4(Val[0] * Inv, Val[1] * Inv, Val[2] * Inv, 0);
}


Quaternion Quaternion::FromEulerAngles(Radians X, Radians Y, Radians Z)
{
    Scalar SinX = sinf(X / 2.0f);
    Scalar SinY = sinf(Y / 2.0f);
    Scalar SinZ = sinf(Z / 2.0f);
    Scalar CosX = cosf(X / 2.0f);
    Scalar CosY = cosf(Y / 2.0f);
    Scalar CosZ = cosf(Z / 2.0f);

    return Quaternion(
        Vector4(
            SinX * CosY * CosZ - CosX * SinY * SinZ,
            CosX * SinY * CosZ + SinX * CosY * SinZ,
            CosX * CosY * SinZ - SinX * SinY * CosZ,
            0
        ),
        CosX  * CosY * CosZ + SinX * SinY * SinZ
    );
}


Quaternion Quaternion::FromAxisAndAngle(Vector4 BGE_NCP Axis, Radians Angle)
{
    return Quaternion(Axis * sinf(Angle / 2.0f), cosf(Angle / 2.0f));
}

Quaternion BGE_NCP Quaternion::operator+=(Quaternion BGE_NCP Other)
{
    Val[0] += Other.Val[0];
    Val[1] += Other.Val[1];
    Val[2] += Other.Val[2];
    Val[3] += Other.Val[3];

    return *this;
}


Quaternion BGE_NCP Quaternion::operator-=(Quaternion BGE_NCP Other)
{
    Val[0] -= Other.Val[0];
    Val[1] -= Other.Val[1];
    Val[2] -= Other.Val[2];
    Val[3] -= Other.Val[3];

    return *this;
}


Quaternion BGE_NCP Quaternion::operator*=(Quaternion BGE_NCP Other)
{
    Vector4 Temp(Val[0], Val[1], Val[2], Val[3]);
    Val[3] *= Other.Val[3];
    Val[3] -= Val[0] * Other.Val[0];
    Val[3] -= Val[1] * Other.Val[1];
    Val[3] -= Val[2] * Other.Val[2];
    Val[0] *= Other.Val[3];
    Val[1] *= Other.Val[3];
    Val[2] *= Other.Val[3];
    Val[0] += Other.Val[0] * Temp[3];
    Val[1] += Other.Val[1] * Temp[3];
    Val[2] += Other.Val[2] * Temp[3];
    Val[0] += Temp[1] * Other.Val[2] - Temp[2] * Other.Val[1];
    Val[1] += Temp[2] * Other.Val[0] - Temp[0] * Other.Val[2];
    Val[2] += Temp[0] * Other.Val[1] - Temp[1] * Other.Val[0];

    return *this;
}


Quaternion BGE_NCP Quaternion::operator/=(Quaternion BGE_NCP Other)
{
    *this *= Other.Inverted();

    return *this;
}


Quaternion BGE_NCP Quaternion::operator*=(Scalar BGE_NCP Value)
{
    Val[0] *= Value;
    Val[1] *= Value;
    Val[2] *= Value;
    Val[3] *= Value;

    return *this;
}


Quaternion BGE_NCP Quaternion::operator/=(Scalar BGE_NCP Value)
{
    Val[0] /= Value;
    Val[1] /= Value;
    Val[2] /= Value;
    Val[3] /= Value;

    return *this;
}


Quaternion Quaternion::operator+(Quaternion BGE_NCP Other) const
{
    return Quaternion(Val[0] + Other.Val[0], Val[1] + Other.Val[1],
                        Val[2] + Other.Val[2], Val[3] + Other.Val[3]);
}


Quaternion Quaternion::operator-(Quaternion BGE_NCP Other) const
{
    return Quaternion(Val[0] - Other.Val[0], Val[1] - Other.Val[1],
                        Val[2] - Other.Val[2], Val[3] - Other.Val[3]);
}


Quaternion Quaternion::operator*(Quaternion BGE_NCP Other) const
{
    Vector4 Us(Val[0], Val[1], Val[2], 0);
    Vector4 Them(Other.Val[0], Other.Val[1], Other.Val[2], 0);

    return Quaternion(
        Vector4(
            Val[0] * Other.Val[3] + Other.Val[0] * Val[3]
             + Val[1] * Other.Val[2] - Val[2] * Other.Val[1],
            Val[1] * Other.Val[3] + Other.Val[1] * Val[3]
             + Val[2] * Other.Val[0] - Val[0] * Other.Val[2],
            Val[2] * Other.Val[3] + Other.Val[2] * Val[3]
             + Val[0] * Other.Val[1] - Val[1] * Other.Val[0],
            0
        ),
        Val[3] * Other.Val[3] - Vector4::Dot(Us, Them)
    );
}


Quaternion Quaternion::operator/(Quaternion BGE_NCP Other) const
{
    return *this * Other.Inverted();
}


Quaternion Quaternion::operator*(Scalar BGE_NCP Value) const
{
    return Quaternion(Val[0] * Value, Val[1] * Value,
                        Val[2] * Value, Val[3] * Value);
}


Quaternion Quaternion::operator/(Scalar BGE_NCP Value) const
{
    return Quaternion(Val[0] / Value, Val[1] / Value,
                        Val[2] / Value, Val[3] / Value);
}


Quaternion Quaternion::operator-() const
{
    return Quaternion(-Val[0], -Val[1], -Val[2], -Val[3]);
}


Quaternion BGE_NCP Quaternion::Invert()
{
    operator-();
    Normalize();

    return *this;
}


Quaternion Quaternion::Inverted() const
{
    return operator-() / Length();
}


Quaternion BGE_NCP Quaternion::Normalize()
{
    Scalar Len = Length();

    /* Don't divide by 0 */
    if(ScalarCompare(Len, 0))
        return *this;

    Val[0] /= Len;
    Val[1] /= Len;
    Val[2] /= Len;
    Val[3] /= Len;

    return *this;
}


Quaternion Quaternion::Normalized() const
{
    return Quaternion(*this).Normalize();
}


Scalar Quaternion::Length() const
{
    return sqrt(LengthSq());
}


Scalar Quaternion::LengthSq() const
{
    Vector4 Us(Val[0], Val[1], Val[2], 0);

    return Scalar(Val[3] * Val[3] + pow(Us.Length(), 2));
}

} /* bakge */

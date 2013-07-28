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
}


Quaternion::Quaternion(Vector4 BGE_NCP Vec, Scalar BGE_NCP Real)
{
    Axis = Vec;
    Angle = Real;
}


Quaternion::Quaternion(Quaternion BGE_NCP Other)
{
    Axis = Other.Axis;
    Angle = Other.Angle;
}


Quaternion::~Quaternion()
{
}


Matrix Quaternion::ToMatrix() const
{
    return Matrix(
        1 - 2 * (Axis[1] * Axis[1] + Axis[2] * Axis[2]),
        2 * (Axis[0] * Axis[1] + Angle * Axis[2]),
        2 * (Axis[0] * Axis[2] - Angle * Axis[1]),
        0,
        2 * (Axis[0] * Axis[1] - Angle * Axis[2]),
        1 - 2 * (Axis[0] * Axis[0] + Axis[2] * Axis[2]),
        2 * (Axis[1] * Axis[2] + Angle * Axis[0]),
        0,
        2 * (Axis[0] * Axis[2] + Angle * Axis[1]),
        2 * (Axis[1] * Axis[2] - Angle * Axis[0]),
        1 - 2 * (Axis[0] * Axis[0] + Axis[1] * Axis[1]),
        0,
        0, 0, 0, 1
    );
}


Scalar Quaternion::GetAngle() const
{
    return acos(Angle) * 2.0f;
}


Vector4 Quaternion::GetAxis() const
{
    Scalar Inv = 1.0f / sin(GetAngle() / 2.0f);
    return Vector4(Axis[0] * Inv, Axis[1] * Inv, Axis[2] * Inv, 0);
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


Quaternion BGE_NCP Quaternion::operator+=(Quaternion BGE_NCP Other)
{
    Axis += Other.Axis;
    Angle += Other.Angle;
    return *this;
}


Quaternion BGE_NCP Quaternion::operator-=(Quaternion BGE_NCP Other)
{
    Axis -= Other.Axis;
    Angle -= Other.Angle;
    return *this;
}


Quaternion BGE_NCP Quaternion::operator*=(Quaternion BGE_NCP Other)
{
    Vector4 Temp = Axis;
    Angle *= Other.Angle;
    Angle -= Axis[0] * Other.Axis[0];
    Angle -= Axis[1] * Other.Axis[1];
    Angle -= Axis[2] * Other.Axis[2];
    Axis *= Other.Angle;
    Axis[0] += Other.Axis[0] * Angle;
    Axis[1] += Other.Axis[1] * Angle;
    Axis[2] += Other.Axis[2] * Angle;
    Axis[0] += Temp[1] * Other.Axis[2] - Temp[2] * Other.Axis[1];
    Axis[1] += Temp[2] * Other.Axis[0] - Temp[0] * Other.Axis[2];
    Axis[2] += Temp[0] * Other.Axis[1] - Temp[1] * Other.Axis[0];
    return *this;
}


Quaternion BGE_NCP Quaternion::operator/=(Quaternion BGE_NCP Other)
{
    *this = Other.Inverted();
    return *this;
}


Quaternion BGE_NCP Quaternion::operator*=(Scalar BGE_NCP Value)
{
    Axis *= Value;
    Angle *= Value;
    return *this;
}


Quaternion BGE_NCP Quaternion::operator/=(Scalar BGE_NCP Value)
{
    Axis /= Value;
    Angle /= Value;
    return *this;
}


Quaternion Quaternion::operator+(Quaternion BGE_NCP Other) const
{
    return Quaternion(Axis + Other.Axis, Angle + Other.Angle);
}


Quaternion Quaternion::operator-(Quaternion BGE_NCP Other) const
{
    return Quaternion(Axis - Other.Axis, Angle - Other.Angle);
}


Quaternion Quaternion::operator*(Quaternion BGE_NCP Other) const
{
    return Quaternion(
        Vector4(
            Axis[0] * Other.Angle + Other.Axis[0] * Angle
             + Axis[1] * Other.Axis[2] - Axis[2] * Other.Axis[1],
            Axis[1] * Other.Angle + Other.Axis[1] * Angle
             + Axis[2] * Other.Axis[0] - Axis[0] * Other.Axis[2],
            Axis[2] * Other.Angle + Other.Axis[2] * Angle
             + Axis[0] * Other.Axis[1] - Axis[1] * Other.Axis[0],
            0
        ),
        Angle * Other.Angle - Dot(Axis, Other.Axis)
    );
}


Quaternion Quaternion::operator/(Quaternion BGE_NCP Other) const
{
    return *this * Other.Inverted();
}


Quaternion Quaternion::operator*(Scalar BGE_NCP Value) const
{
    return Quaternion(Axis * Value, Angle * Value);
}


Quaternion Quaternion::operator/(Scalar BGE_NCP Value) const
{
    return Quaternion(Axis / Value, Angle / Value);
}


Quaternion Quaternion::operator-() const
{
    return Quaternion(-Axis, -Angle);
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

    Angle /= Len;
    Axis /= Len;

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
    return Scalar(Angle * Angle + pow(Axis.Length(), 2));
}

} /* bakge */

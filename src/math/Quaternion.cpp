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
    /* Default to axis <0, 1, 0>, angle 0 radians */
    Real = 1.0f;
}


Quaternion::Quaternion(Vector4 BGE_NCP V, Scalar BGE_NCP R)
{
    X = V[0];
    Y = V[1];
    Z = V[2];
    W = R;
}


Quaternion::Quaternion(Scalar X, Scalar Y, Scalar Z, Scalar W)
{
    this->X = X;
    this->Y = Y;
    this->Z = Z;
    this->W = W;
}


Quaternion::Quaternion(Quaternion BGE_NCP Other)
{
    X = Other.X;
    Y = Other.Y;
    Z = Other.Z;
    W = Other.W;
}


Quaternion::~Quaternion()
{
}


Matrix Quaternion::ToMatrix() const
{
    return Matrix(
        1 - (2 * Y * Y) - (2 * Z * Z),
        (2 * X * Y) + (2 * Z * W),
        (2 * X * Z) - (2 * Y * W),
        0,
        (2 * X * Y) - (2 * Z * W),
        1 - (2 * X * X) - (2 * Z * Z),
        (2 * Vec[1] * Vec[2]) + (2 * Real * Vec[0]),
        0,
        (2 * X * Z) + (2 * Y * W),
        (2 * Y * Z) - (2 * X * W),
        1 - (2 * X * X) - (2 * Y * Y),
        0,
        0, 0, 0, 1
    );
}


Scalar Quaternion::GetAngle() const
{
    return acosf(Real) * 2.0f;
}


Vector4 Quaternion::GetAxis() const
{
    Scalar Inv = 1.0f / sinf(acosf(Real));

    return Vector4(Vec[0] * Inv, Vec[1] * Inv, Vec[2] * Inv, 0);
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


Quaternion Quaternion::FromAxisAndAngle(Vector4 BGE_NCP Axis, Scalar Angle)
{
    return Quaternion(Axis * sinf(Angle / 2.0f), cosf(Angle / 2.0f));
}

Quaternion BGE_NCP Quaternion::operator+=(Quaternion BGE_NCP Other)
{
    /* Vector addition/subtraction affects homogeneous coord also */
    X += Other.X;
    Y += Other.Y;
    Z += Other.Z;
    W += Other.W;

    return *this;
}


Quaternion BGE_NCP Quaternion::operator-=(Quaternion BGE_NCP Other)
{
    /* Vector addition/subtraction affects homogeneous coord also */
    X -= Other.X;
    Y -= Other.Y;
    Z -= Other.Z;
    W -= Other.W;

    return *this;
}


Quaternion BGE_NCP Quaternion::operator*=(Quaternion BGE_NCP Other)
{
    Vector4 Temp(X, Y, Z, W);
    Real *= Other.Real;
    Real -= Vec[0] * Other.Vec[0];
    Real -= Vec[1] * Other.Vec[1];
    Real -= Vec[2] * Other.Vec[2];
    X *= Other.W;
    Y *= Other.W;
    Z *= Other.W;
    Vec[0] += Other.Vec[0] * Real;
    Vec[1] += Other.Vec[1] * Real;
    Vec[2] += Other.Vec[2] * Real;
    Vec[0] += Temp[1] * Other.Vec[2] - Temp[2] * Other.Vec[1];
    Vec[1] += Temp[2] * Other.Vec[0] - Temp[0] * Other.Vec[2];
    Vec[2] += Temp[0] * Other.Vec[1] - Temp[1] * Other.Vec[0];

    return *this;
}


Quaternion BGE_NCP Quaternion::operator/=(Quaternion BGE_NCP Other)
{
    *this = Other.Inverted();

    return *this;
}


Quaternion BGE_NCP Quaternion::operator*=(Scalar BGE_NCP Value)
{
    X *= Value;
    Y *= Value;
    Z *= Value;
    W *= Value;

    return *this;
}


Quaternion BGE_NCP Quaternion::operator/=(Scalar BGE_NCP Value)
{
    X /= Value;
    Y /= Value;
    Z /= Value;
    W /= Value;

    return *this;
}


Quaternion Quaternion::operator+(Quaternion BGE_NCP Other) const
{
    return Quaternion(X + Other.X, Y + Other.Y, Z + Other.Z, W + Other.W);
}


Quaternion Quaternion::operator-(Quaternion BGE_NCP Other) const
{
    return Quaternion(X - Other.X, Y - Other.Y, Z - Other.Z, W - Other.W);
}


Quaternion Quaternion::operator*(Quaternion BGE_NCP Other) const
{
    Vector4 Us(X, Y, Z, W);
    Vector4 Them(Other.X, Other.Y, Other.Z, Other.W);

    return Quaternion(
        Vector4(
            Vec[0] * Other.Real + Other.Vec[0] * Real
             + Vec[1] * Other.Vec[2] - Vec[2] * Other.Vec[1],
            Vec[1] * Other.Real + Other.Vec[1] * Real
             + Vec[2] * Other.Vec[0] - Vec[0] * Other.Vec[2],
            Vec[2] * Other.Real + Other.Vec[2] * Real
             + Vec[0] * Other.Vec[1] - Vec[1] * Other.Vec[0],
            0
        ),
        Real * Other.Real - Dot(Us, Them)
    );
}


Quaternion Quaternion::operator/(Quaternion BGE_NCP Other) const
{
    return *this * Other.Inverted();
}


Quaternion Quaternion::operator*(Scalar BGE_NCP Value) const
{
    return Quaternion(X * Value, Y * Value, Z * Value, W * Value);
}


Quaternion Quaternion::operator/(Scalar BGE_NCP Value) const
{
    return Quaternion(X / Value, Y / Value, Z / Value, W / Value);
}


Quaternion Quaternion::operator-() const
{
    return Quaternion(-X, -Y, -Z, -W);
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

    X /= Len;
    Y /= Len;
    Z /= Len;
    W /= Len;

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
    Vector4 Us(X, Y, Z, W);
    return Scalar(Real * Real + pow(Us.Length(), 2));
}

} /* bakge */

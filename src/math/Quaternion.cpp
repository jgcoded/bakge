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
    return Quaternion();
}


Quaternion Quaternion::operator-(Quaternion BGE_NCP Other) const
{
    return Quaternion();
}


Quaternion Quaternion::operator*(Quaternion BGE_NCP Other) const
{
    return Quaternion();
}


Quaternion Quaternion::operator/(Quaternion BGE_NCP Other) const
{
    return Quaternion();
}


Quaternion Quaternion::operator*(Scalar BGE_NCP Value) const
{
    return Quaternion();
}


Quaternion Quaternion::operator/(Scalar BGE_NCP Value) const
{
    return Quaternion();
}


Quaternion BGE_NCP Quaternion::Invert()
{
    return *this;
}


Quaternion Quaternion::Inverted() const
{
    return Quaternion();
}


Quaternion BGE_NCP Quaternion::Normalize()
{
    return *this;
}


Quaternion Quaternion::Normalized() const
{
    return Quaternion();
}

} /* bakge */

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
    return *this;
}


Quaternion BGE_NCP Quaternion::operator-=(Quaternion BGE_NCP Other)
{
    return *this;
}


Quaternion BGE_NCP Quaternion::operator*=(Quaternion BGE_NCP Other)
{
    return *this;
}


Quaternion BGE_NCP Quaternion::operator/=(Quaternion BGE_NCP Other)
{
    return *this;
}


Quaternion BGE_NCP Quaternion::operator*=(Scalar BGE_NCP Value)
{
    return *this;
}


Quaternion BGE_NCP Quaternion::operator/=(Scalar BGE_NCP Value)
{
    return *this;
}


Quaternion BGE_NCP Quaternion::operator+(Quaternion BGE_NCP Other) const
{
    return *this;
}


Quaternion BGE_NCP Quaternion::operator-(Quaternion BGE_NCP Other) const
{
    return *this;
}


Quaternion BGE_NCP Quaternion::operator*(Quaternion BGE_NCP Other) const
{
    return *this;
}


Quaternion BGE_NCP Quaternion::operator/(Quaternion BGE_NCP Other) const
{
    return *this;
}


Quaternion BGE_NCP Quaternion::operator*(Scalar BGE_NCP Value) const
{
    return *this;
}


Quaternion BGE_NCP Quaternion::operator/(Scalar BGE_NCP Value) const
{
    return *this;
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

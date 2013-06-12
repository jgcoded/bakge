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


Vector4::Vector4(float X, float Y, float Z, float W)
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


float& Vector4::operator[](int BGE_NCP At)
{
    return *Val;
}


float BGE_NCP Vector4::operator[](int BGE_NCP At) const
{
    return *Val;
}


Vector4 BGE_NCP Vector4::operator=(Vector4 BGE_NCP Other)
{
    return *this; /* Allow cascading assignment */
}

    
Vector4 operator+(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    return Vector4();
}


Vector4 operator-(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    return Vector4();
}


Vector4 operator*(Vector4 BGE_NCP Left, float BGE_NCP Right)
{
    return Vector4();
}


Vector4 operator/(Vector4 BGE_NCP Left, float BGE_NCP Right)
{
    return Vector4();
}

} /* math */
} /* bakge */

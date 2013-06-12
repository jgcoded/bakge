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

#ifndef BAKGE_MATH_VECTOR4_H
#define BAKGE_MATH_VECTOR4_H

#include <bakge/Bakge.h>

namespace bakge
{
namespace math
{

class Vector4
{

public:

    Vector4();
    Vector4(float X, float Y, float Z, float W);
    Vector4(Vector4 BGE_NCP Other);
    ~Vector4();

    float& operator[](int BGE_NCP At);
    float BGE_NCP operator[](int BGE_NCP At) const;
    
    Vector4 BGE_NCP operator=(Vector4 BGE_NCP Other);
    
    friend Vector4 operator+(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right);
    friend Vector4 operator-(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right);
    
    friend Vector4 operator*(Vector4 BGE_NCP Left, float BGE_NCP Right);
    friend Vector4 operator/(Vector4 BGE_NCP Left, float BGE_NCP Right);


private:

    float Val[4];

}; /* Vector4 */

} /* math */
} /* bakge */

#endif /* BAKGE_MATH_VECTOR4_H */

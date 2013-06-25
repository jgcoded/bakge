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

#ifndef BAKGE_MATH_VECTOR3_H
#define BAKGE_MATH_VECTOR3_H

#include <bakge/Bakge.h>

namespace bakge
{
namespace math
{

/* *
 * Vectors are used to represent arbitrary points, or directions (and
 * their magnitudes).
 * */
class Vector3
{

public:

    Vector3();
    Vector3(Scalar X, Scalar Y, Scalar Z);
    Vector3(Vector3 BGE_NCP Other);
    ~Vector3();

    Scalar& operator[](int BGE_NCP At);
    Scalar BGE_NCP operator[](int BGE_NCP At) const;
    
    Vector3 BGE_NCP operator=(Vector3 BGE_NCP Other);

    Vector3 BGE_NCP operator+=(Vector3 BGE_NCP Other);
    Vector3 BGE_NCP operator-=(Vector3 BGE_NCP Other);
    
    Vector3 BGE_NCP operator*=(Vector3 BGE_NCP Other);
    Vector3 BGE_NCP operator/=(Vector3 BGE_NCP Other);
    Vector3 BGE_NCP operator/=(Scalar Value);
    
    Vector3 operator+(Vector3 BGE_NCP Other);
    Vector3 operator-(Vector3 Other);
    Vector3 operator*(Vector3 BGE_NCP Other);
    Vector3 operator/(Vector3 BGE_NCP Other);
    Vector3 operator/(Scalar Value);

    bool BGE_NCP operator==(Vector3 BGE_NCP Other);

    Vector3 Normalized() const;

    Scalar LengthSquared() const;
    Scalar Length() const;

    static const Vector3 UpVector; /* Where do I define this? */

    static Vector3 Normalize(Vector3 Other);
    static Scalar Dot(Vector3 BGE_NCP Left, Vector3 BGE_NCP Right);
    static Vector3 Cross(Vector3 BGE_NCP Left, Vector3 BGE_NCP Right);
    static Vector3 UnitVector(Scalar X, Scalar Y, Scalar Z);
    static Vector3 Hermite(Vector3 BGE_NCP Left, Vector3 BGE_NCP tangentLeft, Vector3 BGE_NCP Right, Vector3 BGE_NCP tangentRight, Scalar amount);

private:

    Scalar Val[3];


}; /* Vector3 */

Vector3 operator+(Vector3 BGE_NCP Left, Vector3 BGE_NCP Right);
Vector3 operator-(Vector3 BGE_NCP Left, Vector3 BGE_NCP Right);
Vector3 operator-(Vector3 BGE_NCP This);
Vector3 operator*(Vector3 BGE_NCP Left, Vector3 BGE_NCP Right);
Vector3 operator/(Vector3 BGE_NCP Left, Vector3 BGE_NCP Right);

} /* math */
} /* bakge */

#endif
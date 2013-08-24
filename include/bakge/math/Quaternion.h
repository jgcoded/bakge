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

#ifndef BAKGE_MATH_QUATERNION_H
#define BAKGE_MATH_QUATERNION_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Quaternions are used to describe rotations in 3D Cartesian space
 *
 * Quaternions describe rotations in space using an axis <i, j, k> and
 * a rotation theta around that axis. Quaternions are composed of 4 parts,
 * one real (or scalar) part and 3 imaginary (or vector) parts.
 *
 * Quaternions are the preferred method of describing rotations in space.
 * Using quaternions protects you from gimbal lock -- an issue that may arise
 * from using Euler angles to describe rotations. It is also quite easy
 * to extract a rotation matrix from a quaternion, which can then be used
 * by OpenGL or elsewhere to perform rotation transformations.
 *
 * Quaternions are almost like numbers. They can be used together in all sorts
 * of operations such as multiplication, division, scalar multiplication and
 * division, normalization and more. The catch is that quaternion-quaternion
 * multiplication is non-commutative.
 *
 * Multiplying a quaternion by another rotates the first by the second. This
 * is useful for compounding rotations upon each other without building
 * rotation matrices and multiplying them instead.
 */
class BGE_API Quaternion
{
    Vector4 Val;


public:

    Quaternion();
    Quaternion(Vector4 BGE_NCP Vec, Scalar BGE_NCP Real);
    Quaternion(Quaternion BGE_NCP Other);
    Quaternion(Vector4 BGE_NCP Components);
    Quaternion(Scalar X, Scalar Y, Scalar Z, Scalar W);
    ~Quaternion();

    Matrix ToMatrix() const;

    Scalar GetAngle() const;
    Vector4 GetAxis() const;

    static Quaternion FromEulerAngles(Radians X, Radians Y, Radians Z);
    static Quaternion FromAxisAndAngle(Vector4 BGE_NCP Axis, Scalar Angle);

    Quaternion BGE_NCP operator+=(Quaternion BGE_NCP Other);
    Quaternion BGE_NCP operator-=(Quaternion BGE_NCP Other);
    Quaternion BGE_NCP operator*=(Quaternion BGE_NCP Other);
    Quaternion BGE_NCP operator/=(Quaternion BGE_NCP Other);
    Quaternion BGE_NCP operator*=(Scalar BGE_NCP Value);
    Quaternion BGE_NCP operator/=(Scalar BGE_NCP Value);

    Quaternion operator+(Quaternion BGE_NCP Other) const;
    Quaternion operator-(Quaternion BGE_NCP Other) const;
    Quaternion operator*(Quaternion BGE_NCP Other) const;
    Quaternion operator/(Quaternion BGE_NCP Other) const;
    Quaternion operator*(Scalar BGE_NCP Value) const;
    Quaternion operator/(Scalar BGE_NCP Value) const;
    Quaternion operator-() const;

    Quaternion BGE_NCP Invert();
    Quaternion Inverted() const;

    Quaternion BGE_NCP Normalize();
    Quaternion Normalized() const;

    Scalar Length() const;
    Scalar LengthSq() const;

}; /* Quaternion */

} /* bakge */

#endif /* BAKGE_MATH_QUATERNION_H */

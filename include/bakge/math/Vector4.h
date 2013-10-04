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

/*!
 * @file Vector4.h
 * @brief Vector4 class declaration.
 */

#ifndef BAKGE_MATH_VECTOR4_H
#define BAKGE_MATH_VECTOR4_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief 4-component vector for representing 3D vectors or points.
 *
 * Commonly used for representing points or directions in 3D Cartesian space.
 * The homogeneous fourth coordinate is often called the w-coordinate.
 */
class BGE_API Vector4
{
    union
    {
        struct
        {
            Scalar Val[4];
        };

        struct
        {
            Scalar V0, V1, V2, V3;
        };
    };


public:

    static const Vector4 Origin;
    static const Vector4 ZeroVector;

    /*! @brief Default Vector4 constructor.
     *
     * Default Vector4 constructor.
     */
    Vector4();

    /*! @brief Component-wise Vector4 constructor.
     *
     * Component-wise Vector4 constructor.
     */
    Vector4(Scalar X, Scalar Y, Scalar Z, Scalar W);

    /*! @brief Vector4 copy constructor.
     *
     * Vector4 copy constructor.
     */
    Vector4(Vector4 BGE_NCP Other);

    /*! @brief Vector4 destructor.
     *
     * Vector4 destructor.
     */
    ~Vector4();

    /*! @brief Binary negation operator.
     *
     * Binary negation operator. Get the opposite of a vector.
     *
     * @return Opposite of the Vector4 direction.
     *
     * @warning Do not negate a point.
     */
    Vector4 operator-() const;

    /*! @brief Mutable indexing operator.
     *
     * Mutable indexing operator. Get the value of a Vector4's component.
     *
     * @return reference to the component at the given index.
     */
    Scalar& operator[](int At);

    /*! @brief Read-only indexing operator.
     *
     * Read-only indexing operator. Get the value of a Vector4's component.
     *
     * @return constref to the component at the given index.
     */
    Scalar BGE_NCP operator[](int At) const;

    /*! @brief Assignment operator.
     *
     * Assignment operator.
     *
     * @param[in] Other Vector4 to copy.
     *
     * @return constref to the Vector4 after assignment.
     */
    Vector4 BGE_NCP operator=(Vector4 BGE_NCP Other);

    /*! @brief Equality operator.
     *
     * Check if two Vector4 objects have components differing by less than
     * a constant epsilon value.
     *
     * @param[in] Other Vector4 with which to compare.
     *
     * @return true if the Vector4 objects are roughly equal.
     */
    bool operator==(Vector4 BGE_NCP Other) const;

    /*! @brief Compound add-assign operator.
     *
     * Compound add-assign operator.
     *
     * @param[in] Other Vector4 to add.
     *
     * @return constref to the Vector4 after addition.
     *
     * @warning Do not sum two points.
     */
    Vector4 BGE_NCP operator+=(Vector4 BGE_NCP Other);

    /*! @brief Compound subtract-assign operator.
     *
     * Compound subtract-assign operator.
     *
     * @param[in] Other Vector4 to subtract.
     *
     * @return constref to the Vector4 after subtraction.
     *
     * @warning Do not subtract a point from a vector.
     */
    Vector4 BGE_NCP operator-=(Vector4 BGE_NCP Other);

    /*! @brief Compound multiply-assign operator.
     *
     * Compound multiply-assign operator.
     *
     * @param[in] Other Scalar to multiply by.
     *
     * @return constref to the Vector4 after multiplication.
     */
    Vector4 BGE_NCP operator*=(Scalar Value);

    /*! @brief Compound divide-assign operator.
     *
     * Compound divide-assign operator.
     *
     * @param[in] Other Scalar to divide by.
     *
     * @return constref to the Vector4 after division.
     */
    Vector4 BGE_NCP operator/=(Scalar Value);

    /*! @brief Add two vectors together.
     *
     * Add two vectors together.
     *
     * @param[in] Other Vector4 to add with.
     *
     * @return Sum of two Vector4 objects, component-wise.
     *
     * @warning Do not sum 2 points.
     */
    Vector4 operator+(Vector4 BGE_NCP Other) const;

    /*! @brief Subtract two vectors.
     *
     * Subtract two vectors.
     *
     * @param[in] Other Vector4 to subtract with.
     *
     * @return Difference of two Vector4 objects, component-wise.
     *
     * @warning Do not subtract a point from a vector.
     */
    Vector4 operator-(Vector4 BGE_NCP Other) const;

    /*! @brief Vector4 multiplied by a scalar.
     *
     * Vector4 multiplied by a scalar.
     *
     * @param[in] Value Scalar to multiply by.
     *
     * @return Value of the Vector4 multiplied by a given value.
     *
     * @warning Do not multiply a point by a scalar.
     */
    Vector4 operator*(Scalar Value) const;

    /*! @brief Vector4 divided by a scalar.
     *
     * Vector4 divided by a scalar.
     *
     * @param[in] Value Scalar to divide by.
     *
     * @return Value of the Vector4 divided by a given value.
     *
     * @warning Do not divide a point by a scalar.
     */
    Vector4 operator/(Scalar Value) const;

    /*! @brief Normalize a vector.
     *
     * Normalize a vector.
     *
     * @warning Do not normalize a point.
     */
    Vector4 BGE_NCP Normalize();

    /*! @brief Get a normalized copy of the Vector4.
     *
     * Get a normalized copy of the Vector4.
     *
     * @warning Do not normalize a point.
     */
    Vector4 Normalized() const;

    /*! @brief Get the length of a vector, squared.
     *
     * Get the length of a vector, squared.
     *
     * @return Length squared of the vector.
     *
     * @warning Do not get the length of a point.
     */
    Scalar LengthSquared() const;

    /*! @brief Get the length of a vector.
     *
     * Get the length of a vector.
     *
     * @return Length of the vector.
     *
     * @warning Do not get the length of a point.
     */
    Scalar Length() const;

    /*! @brief Dot product of two vectors.
     *
     * Dot product of two vectors.
     *
     * @return Dot product of two vectors.
     *
     * @warning Do not use points to compute a dot product.
     */
    static Scalar Dot(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right);

    /*! @brief Cross product of two vectors.
     *
     * Cross product of two vectors.
     *
     * @return Vector perpendicular to two given vectors.
     *
     * @warning Safe to use on points, as the homogeneous coordinate is ignored.
     */
    static Vector4 Cross(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right);

    /*! @brief Get a point in 3D Cartesian space.
     *
     * Get a point in 3D Cartesian space.
     *
     * @param[in] X X coordinate of the point.
     * @param[in] Y Y coordinate of the point.
     * @param[in] Z Z coordinate of the point.
     *
     * @return Vector4 representing a point in 3D Cartesian space.
     */
    static Vector4 Point(Scalar X, Scalar Y, Scalar Z);

    /*! @brief Get a vector in 3D Cartesian space.
     *
     * Get a vector in 3D Cartesian space.
     *
     * @param[in] X X component of the vector.
     * @param[in] Y Y component of the vector.
     * @param[in] Z Z component of the vector.
     *
     * @return Vector4 representing a vector in 3D Cartesian space.
     */
    static Vector4 Vector(Scalar X, Scalar Y, Scalar Z);

    /*! @brief Get a unit vector (length of 1) in 3D Cartesian space.
     *
     * Get a unit vector (length of 1) in 3D Cartesian space.
     *
     * @param[in] X X component of the vector.
     * @param[in] Y Y component of the vector.
     * @param[in] Z Z component of the vector.
     *
     * @return Vector4 representing unit vector in 3D Cartesian space.
     */
    static Vector4 UnitVector(Scalar X, Scalar Y, Scalar Z);

}; // Vector4

} /* bakge */

#endif /* BAKGE_MATH_VECTOR4_H */

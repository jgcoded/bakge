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
 * @file Vector3.h
 * @brief Vector3 class declaration.
 */

#ifndef BAKGE_MATH_VECTOR3_H
#define BAKGE_MATH_VECTOR3_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief 3-component 2D vector/point class.
 *
 * This class assumes the vector or point it represents exists in 2D Cartesian
 * space. As such, there is no cross product. Using a Vector3 to represent
 * points or vectors in 3D space works just fine though.
 */
class BGE_API Vector3
{
    Scalar Val[3];


public:

    /*! @brief Default Vector3 constructor.
     *
     * Default Vector3 constructor.
     */
    Vector3();

    /*! @brief Component-wise Vector3 constructor.
     *
     * Component-wise Vector3 constructor.
     */
    Vector3(Scalar X, Scalar Y, Scalar Z);

    /*! @brief Vector3 copy constructor.
     *
     * Vector3 copy constructor.
     */
    Vector3(Vector3 BGE_NCP Other);

    /*! @brief Vector3 destructor.
     *
     * Vector3 destructor.
     */
    ~Vector3();

    /*! @brief Negation operator.
     *
     * Get the negative of a vector.
     *
     * @return Opposite of the vector.
     *
     * @warning Do not use on points.
     */
    Vector3 operator-() const;

    /*! @brief Mutable index operator.
     *
     * Mutable index operator.
     *
     * @return Reference to component at given index.
     */
    Scalar& operator[](int At);

    /*! @brief Immutable index operator.
     *
     * Immutable index operator.
     *
     * @return constref to component at given index.
     */
    Scalar BGE_NCP operator[](int At) const;

    /*! @brief Assignment operator.
     *
     * Assignment operator.
     *
     * @param[in] Other Vector3 to copy.
     *
     * @return constref to Vector3 after assignment.
     */
    Vector3 BGE_NCP operator=(Vector3 BGE_NCP Other);

    /*! @brief Equality operator.
     *
     * Check if two Vector3 objects have components differing by less than
     * a constant epsilon value.
     *
     * @param[in] Other Vector3 with which to compare.
     *
     * @return true if the Vector3 objects are roughly equal.
     */
    bool operator==(Vector3 BGE_NCP Other) const;

    /*! @brief Compound add-assign operator.
     *
     * Compound add-assign operator.
     *
     * @param[in] Other Vector3 to add.
     *
     * @return constref to the Vector3 after addition.
     *
     * @warning Do not sum two points.
     */
    Vector3 BGE_NCP operator+=(Vector3 BGE_NCP Other);

    /*! @brief Compound subtract-assign operator.
     *
     * Compound subtract-assign operator.
     *
     * @param[in] Other Vector3 to subtract.
     *
     * @return constref to the Vector3 after subtraction.
     *
     * @warning Do not subtract a point from a vector.
     */
    Vector3 BGE_NCP operator-=(Vector3 BGE_NCP Other);

    /*! @brief Compound multiply-assign operator.
     *
     * Compound multiply-assign operator.
     *
     * @param[in] Value Scalar to multiply by.
     *
     * @return constref to the Vector3 after multiplication.
     */
    Vector3 BGE_NCP operator*=(Scalar Value);

    /*! @brief Compound divide-assign operator.
     *
     * Compound divide-assign operator.
     *
     * @param[in] Value Scalar to divide by.
     *
     * @return constref to the Vector3 after division.
     */
    Vector3 BGE_NCP operator/=(Scalar Value);

    /*! @brief Add two vectors together.
     *
     * Add two vectors together.
     *
     * @param[in] Other Vector3 to add with.
     *
     * @return Sum of two Vector3 objects, component-wise.
     *
     * @warning Do not sum 2 points.
     */
    Vector3 operator+(Vector3 BGE_NCP Other) const;

    /*! @brief Subtract two vectors.
     *
     * Subtract two vectors.
     *
     * @param[in] Other Vector3 to subtract with.
     *
     * @return Difference of two Vector3 objects, component-wise.
     *
     * @warning Do not subtract a point from a vector.
     */
    Vector3 operator-(Vector3 BGE_NCP Other) const;

    /*! @brief Vector3 multiplied by a scalar.
     *
     * Vector3 multiplied by a scalar.
     *
     * @param[in] Value Scalar to multiply by.
     *
     * @return Value of the Vector3 multiplied by a given value.
     *
     * @warning Do not multiply a point by a scalar.
     */
    Vector3 operator*(Scalar Value) const;

    /*! @brief Vector3 divided by a scalar.
     *
     * Vector3 divided by a scalar.
     *
     * @param[in] Value Scalar to divide by.
     *
     * @return Value of the Vector3 divided by a given value.
     *
     * @warning Do not divide a point by a scalar.
     */
    Vector3 operator/(Scalar Value) const;

    /*! @brief Normalize a vector.
     *
     * Normalize a vector.
     *
     * @warning Do not normalize a point.
     */
    Vector3 BGE_NCP Normalize();

    /*! @brief Get a normalized copy of the Vector3.
     *
     * Get a normalized copy of the Vector3.
     *
     * @warning Do not normalize a point.
     */
    Vector3 Normalized() const;

    /*! @brief Get the length of a vector, squared.
     *
     * Get the length of a vector, squared.
     *
     * @return Length squared of the vector.
     *
     * @warning Do not get the length of a point.
     */
    Scalar Length() const;

    /*! @brief Get the length of a vector.
     *
     * Get the length of a vector.
     *
     * @return Length of the vector.
     *
     * @warning Do not get the length of a point.
     */
    Scalar LengthSquared() const;

    /*! @brief Dot product of two vectors.
     *
     * Dot product of two vectors.
     *
     * @return Dot product of two vectors.
     *
     * @warning Do not use points to compute a dot product.
     */
    static Scalar Dot(Vector3 BGE_NCP Left, Vector3 BGE_NCP Right);

    /*! @brief Get a unit vector (length of 1) in 2D Cartesian space.
     *
     * Get a unit vector (length of 1) in 2D Cartesian space.
     *
     * @param[in] X X component of the vector.
     * @param[in] Y Y component of the vector.
     * @param[in] Z Z component of the vector.
     *
     * @return Vector3 representing unit vector in 2D Cartesian space.
     */
    static Vector3 UnitVector(Scalar X, Scalar Y, Scalar Z);

}; /* Vector3 */

} /* bakge */

#endif /* BAKGE_MATH_VECTOR3_H */

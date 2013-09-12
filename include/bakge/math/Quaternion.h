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
 * @file Quaternion.h
 * @brief Quaternion class declaration.
 */

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

    /*! @brief Default Quaternion constructor.
     *
     * Sets scalar component to 1.0, describing a rotation of 0 radians about
     * the <0, 1, 0> axis.
     */
    Quaternion();

    /*! @brief Scalar-and-vector constructor.
     *
     * Not to be confused with an axis-and-angle constructor. Simply
     * copies the vector and scalar components.
     *
     * @param[in] Vec Vector part of the quaternion.
     * @param[in] Real Scalar part of the quaternion.
     */
    Quaternion(Vector4 BGE_NCP Vec, Scalar BGE_NCP Real);

    /*! @bief Quaternion copy constructor.
     *
     * Copy data from the other quaternion.
     *
     * @param[in] Other Quaternion to copy data from.
     */
    Quaternion(Quaternion BGE_NCP Other);

    /*! @brief Components constructor.
     *
     * Copy data from vector directly to quaternion. The first three fields
     * in the vector are the vector part and the last field is the scalar
     * part.
     *
     * @param[in] Components First three fields are the vector component. The
     * last field is the scalar component.
     */
    Quaternion(Vector4 BGE_NCP Components);

    /*! @brief Component-wise constructor.
     *
     * Copy data into quaternion. X, Y and Z are the vector part and W is the
     * scalar part.
     *
     * @param[in] X X component of the quaternion's vector part.
     * @param[in] Y Y component of the quaternion's vector part.
     * @param[in] Z Z component of the quaternion's vector part.
     * @param[in] W Real part of the quaternion.
     */
    Quaternion(Scalar X, Scalar Y, Scalar Z, Scalar W);

    /*! @brief Quaternion destructor.
     *
     * Quaternion destructor.
     */
    ~Quaternion();

    /*! @brief Return a rotation Matrix described by the Quaternion.
     *
     * This function constructs a Matrix from the quaternion's rotation
     * in space.
     *
     * @return Rotation matrix representing the Quaternion's rotation in
     * 3D Cartesian space.
     */
    Matrix ToMatrix() const;

    /*! @brief Extract the angle about the quaternion's arbitrary axis
     *
     * Quaternions describe rotations about an arbitrary axis in space.
     * This method extracts that rotation, described in radians.
     *
     * @return Scalar representing rotation in radians.
     */
    Radians GetAngle() const;

    /*! @brief Extract the axis from the quaternion's rotation.
     *
     * Quaternions describe rotations about an arbitrary axis in space.
     * This method extracts that axis, described as a vector.
     *
     * @return Vector describing the axis about which the quaternion's rotation
     * is oriented. Not guaranteed to be a unit vector.
     */
    Vector4 GetAxis() const;

    /*! @brief Construct a quaternion from radians about the three major axes.
     *
     * Quaternions can be constructed from Euler angles. This method creates
     * a quaternion from which you can extract axis and angle data from
     * Euler angle data.
     *
     * @param[in] X Radian angle about the X axis.
     * @param[in] Y Radian angle about the Y axis.
     * @param[in] Z Radian angle about the Z axis.
     *
     * @return Quaternion describing rotation about the three major axes.
     */
    static Quaternion FromEulerAngles(Radians X, Radians Y, Radians Z);

    /*! @brief Construct a quaternion from an axis and an angle.
     *
     * Construct a quaternion from an axis and an angle.
     *
     * @param[in] Axis Axis about which the rotation is described.
     * @param[in] Angle Radian angle about Axis.
     *
     * @return Quaternion describing rotation about an arbitrary axis.
     */
    static Quaternion FromAxisAndAngle(Vector4 BGE_NCP Axis, Radians Angle);

    /*! @brief Component-wise addition compound assignment.
     *
     * Component-wise addition compound assignment.
     *
     * @param[in] Other Quaternion to add with component-wise.
     *
     * @return Left operand after component-wise addition with right operand.
     */
    Quaternion BGE_NCP operator+=(Quaternion BGE_NCP Other);

    /*! @brief Component-wise subtraction compound assignment.
     *
     * Component-wise subtraction compound assignment.
     *
     * @param[in] Other Quaternion to subtract by component-wise.
     *
     * @return Left operand after component-wise subtraction with right operand.
     */
    Quaternion BGE_NCP operator-=(Quaternion BGE_NCP Other);

    /*! @brief Quaternion-quaternion compound rotation.
     *
     * Rotates left operand by the rotation described by the right operand.
     *
     * @param[in] Other Quaternion describing rotation to be compounded into
     * left operand.
     *
     * @return Left operand after compounded rotation by right operand.
     */
    Quaternion BGE_NCP operator*=(Quaternion BGE_NCP Other);

    /*! @brief Quaternion-quaternion compound rotation.
     *
     * Rotates left operand by rotation described by the inverse of the right
     * operand.
     *
     * @param[in] Other Quaternion describing inverse rotation to be compounded
     * into left operand.
     *
     * @return Left operand after compounded inverse rotation by right operand.
     */
    Quaternion BGE_NCP operator/=(Quaternion BGE_NCP Other);

    /*! @brief Component-wise multiplication compound assignment.
     *
     * Component-wise multiplication compound assignment.
     *
     * @param[in] Value Scalar to multiply quaternion's components by.
     *
     * @return Left operand after component-wise compounded scalar
     * multiplication.
     */
    Quaternion BGE_NCP operator*=(Scalar BGE_NCP Value);

    /*! @brief Component-wise division compound assignment.
     *
     * Component-wise division compound assignment.
     *
     * @param[in] Value Scalar to divide quaternion's components by.
     *
     * @return Left operand after component-wise compounded scalar
     * division.
     */
    Quaternion BGE_NCP operator/=(Scalar BGE_NCP Value);

    /*! @brief Component-wise quaternion addition.
     *
     * Component-wise quaternion addition.
     *
     * @param[in] Other Quaternion to add with component-wise.
     *
     * @return Quaternion representing component-wise sum of left and right
     * operands.
     */
    Quaternion operator+(Quaternion BGE_NCP Other) const;

    /*! @brief Component-wise quaternion subtraction.
     *
     * Component-wise quaternion subtraction.
     *
     * @param[in] Other Quaternion to subtract by component-wise.
     *
     * @return Quaternion representing component-wise difference of left and
     * right operands.
     */
    Quaternion operator-(Quaternion BGE_NCP Other) const;

    /*! @brief Quaternion-quaternion rotation.
     *
     * Quaternion-quaternion rotation.
     *
     * @param[in] Other Quaternion describing rotation to be compounded
     * onto left operand.
     *
     * @return Quaternion representing compounded rotations of the left and
     * right operands.
     */
    Quaternion operator*(Quaternion BGE_NCP Other) const;

    /*! @brief Quaternion-quaternion inverse rotation.
     *
     * Quaternion-quaternion inverse rotation.
     *
     * @param[in] Other Quaternion describing inverse rotation to be compounded
     * onto left operand.
     *
     * @return Quaternion representing the compound of the left operand's
     * rotation and the right operand's inverse rotation.
     */
    Quaternion operator/(Quaternion BGE_NCP Other) const;

    /*! @brief Component-wise scalar multiplication.
     *
     * Component-wise scalar multiplication.
     *
     * @param[in] Value Scalar by which to multiply left operand's components.
     *
     * @return Quaternion representing components of the left operand
     * multiplied by the right operand.
     */
    Quaternion operator*(Scalar BGE_NCP Value) const;

    /*! @brief Component-wise scalar division.
     *
     * Component-wise scalar division.
     *
     * @param[in] Value Scalar by which to divide left operand's components.
     *
     * @return Quaternion representing components of the left operand
     * divided by the right operand.
     */
    Quaternion operator/(Scalar BGE_NCP Value) const;

    /*! @brief Binary negation operator (inverse).
     *
     * Negates the vector and scalar parts of the quaternion. The inverse of
     * a quaternion is the normalized negation of its components.
     *
     * @return Quaternion with negative components of the operand.
     */
    Quaternion operator-() const;

    /*! @brief Invert the quaternion.
     *
     * Invert the quaternion. Negates the components and normalizes.
     *
     * @return The quaternion after being inverted.
     */
    Quaternion BGE_NCP Invert();

    /*! @brief Get an inverted copy of the quaternion.
     *
     * Get an inverted copy of the quaternion.
     *
     * @return Copy of the quaternion, inverted.
     */
    Quaternion Inverted() const;

    /*! @brief Normalize the quaternion.
     *
     * Normalize the quaternion by dividing it by its length.
     *
     * @return The quaternion after being normalized.
     *
     * @see Quaternion::Length
     */
    Quaternion BGE_NCP Normalize();

    /*! @brief Get a normalized copy of the quaternion.
     *
     * Get a normalized copy of the quaternion.
     *
     * @return Copy of the quaternion, normalized.
     */
    Quaternion Normalized() const;

    /*! @brief Get the length of the quaternion.
     *
     * The length of a quaternion is the square root of the sum of the length
     * of the vector part and the square of the real part.
     *
     * @return Scalar representing length of the quaternion.
     *
     * @see Quaternion::LengthSq
     */
    Scalar Length() const;

    /*! @brief Get the length of the quaternion, squared.
     *
     * Use LengthSq when you need to compare the length of two Quaternions, as
     * the square root operation becomes a needless and relatively
     * time-consuming operation.
     *
     * @return The square of the length of the quaternion.
     *
     * @see Quaternion::Length
     */
    Scalar LengthSq() const;

}; /* Quaternion */

} /* bakge */

#endif /* BAKGE_MATH_QUATERNION_H */

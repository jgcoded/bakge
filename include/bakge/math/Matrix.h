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
 * @file Matrix.h
 * @brief Matrix class declaration.
 */

#ifndef BAKGE_MATH_MATRIX_H
#define BAKGE_MATH_MATRIX_H

#include <bakge/Bakge.h>

namespace bakge
{

/* *
 * 4x4 matrix. Used to store matrices for use in OpenGL
 * The matrices are stored in column-major form, much like OpenGL's, for
 * faster multiplication.
 *
 * They will most often be used to store matrix transforms that need to be
 * quickly loaded into OpenGL on a regular bases -- such as projection
 * matrices for 2D and 3D renderers.
 *
 * Position and/or rotation data can be described with a Node or Pawn object.
 * */
class BGE_API Matrix
{
    union
    {
        struct
        {
            Scalar Val[16];
        };

        struct
        {
            Scalar M00, M01, M02, M03;
            Scalar M10, M11, M12, M13;
            Scalar M20, M21, M22, M23;
            Scalar M30, M31, M32, M33;
        };
    };


public:

    /*! @brief Identity matrix.
     *
     * Use whenever you need an identity matrix instead of allocating a
     * new one.
     */
    static const Matrix Identity;

    /*! @brief Default Matrix constructor.
     *
     * Default Matrix constructor.
     */
    Matrix();

    /*! @brief Matrix deconstructor.
     *
     * Matrix deconstructor.
     */
    ~Matrix();

    /*! @brief Matrix copy-constructor.
     *
     * Matrix copy-constructor.
     */
    Matrix(Matrix BGE_NCP Other);

    /*! @brief Matrix component constructor.
     *
     * Matrix component constructor.
     *
     * @warning May be removed or deprecated in the near future.
     */
    Matrix(Scalar A, Scalar B, Scalar C, Scalar D,
           Scalar E, Scalar F, Scalar G, Scalar H,
           Scalar I, Scalar J, Scalar K, Scalar L,
           Scalar M, Scalar N, Scalar O, Scalar P);

    /*! @brief Matrix column constructor.
     *
     * Construct a matrix with columns.
     */
    Matrix(Vector4 BGE_NCP A, Vector4 BGE_NCP B, Vector4 BGE_NCP C,
                                                Vector4 BGE_NCP D);

    /*! @brief Matrix field accessor.
     *
     * Matrix field accessor.
     *
     * @param[in] At 0-base field index.
     *
     * @return const reference to field at specified index.
     */
    BGE_INL Scalar BGE_NCP operator[](int BGE_NCP At) const
    {
        return Val[At];
    }

    /*! @brief Matrix field mutator.
     *
     * Matrix field mutator.
     *
     * @param[in] At 0-base field index.
     *
     * @return Reference to field at specified index.
     */
    BGE_INL Scalar& operator[](int BGE_NCP At)
    {
        return Val[At];
    }

    /*! @brief Matrix assignment operator.
     *
     * Matrix assignment operator.
     *
     * @return const reference to the Matrix after assignment.
     */
    Matrix BGE_NCP operator=(Matrix BGE_NCP Other);

    /*! @brief Matrix multiplication operator.
     *
     * Matrix multiplication operator.
     *
     * @param[in] Other Right operand.
     *
     * @return Result matrix from multiplication of left and right operands.
     */
    Matrix operator*(Matrix BGE_NCP Other) const;

    /*! @brief Matrix multiplication compound operator.
     *
     * Matrix multiplication compound operator.
     *
     * @param[in] Other Right operand.
     *
     * @return const reference to the Matrix after compounded multiplication
     * with right operand.
     */
    Matrix BGE_NCP operator*=(Matrix BGE_NCP Other);

    /*! @brief Invert the Matrix.
     *
     * Invert the Matrix.
     *
     * @return const reference to the Matrix after it has been inverted.
     */
    Matrix BGE_NCP Invert();

    /*! @brief Get the inverse of the Matrix.
     *
     * Get the inverse of the Matrix.
     *
     * @return Inverse of the Matrix.
     */
    Matrix Inverted() const;

    /*! @brief Get the transpose of the Matrix.
     *
     * Get the transpose of the Matrix.
     *
     * @return Transposition of the Matrix.
     */
    Matrix Transposed() const;

    /*! @brief Transpose the Matrix.
     *
     * Transpose the Matrix.
     *
     * @return const reference to the Matrix after it has been transposed.
     */
    Matrix BGE_NCP Transpose();

    /*! @brief Get the determinant of the Matrix.
     *
     * Get the determinant of the Matrix.
     *
     * @return Determinant of the Matrix.
     */
    Scalar Determinant() const;

    /*! @brief Set the Matrix to the identity matrix.
     *
     * Set the Matrix to the identity matrix.
     *
     * @return const reference to the Matrix after being set to identity.
     */
    Matrix BGE_NCP SetIdentity();

    /*! @brief Set the Matrix to a perspective projection matrix.
     *
     * Set the Matrix to a perspective projection matrix.
     *
     * @param[in] FOV Field of view in degrees.
     * @param[in] Aspect Ratio of view width to height.
     * @param[in] NearClip Near clipping plane.
     * @param[in] FarClip Far clipping plane.
     *
     * @return const reference to the Matrix after being set to a perspective
     * projection.
     */
    Matrix BGE_NCP SetPerspective(Degrees FOV, Scalar Aspect, Scalar NearClip,
                                                            Scalar FarClip);

    /*! @brief Set the Matrix to an orthographic projection matrix.
     *
     * Set the Matrix to an orthographic projection matrix.
     *
     * @param[in] Left X position of the left boundary.
     * @param[in] Right X position of the right boundary.
     * @param[in] Bottom Y position of the bottom boundary.
     * @param[in] Top Y position of the top boundary.
     * @param[in] Near Near clipping plane.
     * @param[in] Far Far clipping plane.
     *
     * @return const reference to the Matrix after being set to an orthographic
     * projection.
     */
    Matrix BGE_NCP SetOrthographic(Scalar Left, Scalar Right, Scalar Bottom,
                                        Scalar Top, Scalar Near, Scalar Far);

    /*! @brief Set the Matrix to a view matrix.
     *
     * Set the Matrix to a view matrix.
     *
     * @param[in] Position Eye position.
     * @param[in] Target Eye target.
     * @param[in] UpVector View up vector. Affects roll of the camera.
     *
     * @return const reference to the Matrix after being set to a view matrix.
     */
    Matrix BGE_NCP SetLookAt(Vector4 BGE_NCP Position, Vector4 BGE_NCP Target,
                                                    Vector4 BGE_NCP UpVector);

    /*! @brief Generate a scale matrix.
     *
     * Generate a scale matrix.
     *
     * @param[in] X Scale along the X axis.
     * @param[in] Y Scale along the Y axis.
     * @param[in] Z Scale along the Z axis.
     *
     * @return Scale matrix.
     */
    static Matrix Scaling(Scalar X, Scalar Y, Scalar Z);

    /*! @brief Generate a translation matrix.
     *
     * Generate a translation matrix.
     *
     * @param[in] X Translation along the X axis.
     * @param[in] Y Translation along the Y axis.
     * @param[in] Z Translation along the Z axis.
     *
     * @return Translation matrix.
     */
    static Matrix Translation(Scalar X, Scalar Y, Scalar Z);

    /*! @brief Generate a rotation matrix from Euler angles.
     *
     * Generate a rotation matrix from Euler angles.
     *
     * @param[in] X Rotation in radians about the X axis.
     * @param[in] Y Rotation in radians about the Y axis.
     * @param[in] Z Rotation in radians about the Z axis.
     *
     * @return Rotation matrix.
     */
    static Matrix Rotation(Radians X, Radians Y, Radians Z);

    /*! @brief Generate a rotation matrix from an axis and angle.
     *
     * Generate a rotation matrix from an axis and angle.
     *
     * @param[in] Angle Rotation about the specified axis in radians.
     * @param[in] X X component of the axis.
     * @param[in] Y Y component of the axis.
     * @param[in] Z Z component of the axis.
     *
     * @return Rotation matrix.
     */
    static Matrix Rotation(Radians Angle, Scalar X, Scalar Y, Scalar Z);

    /*! @brief Translate the Matrix.
     *
     * Translate the Matrix.
     *
     * @param[in] X Translation along the X axis.
     * @param[in] Y Translation along the Y axis.
     * @param[in] Z Translation along the Z axis.
     *
     * @return const reference to the Matrix after translation.
     */
    Matrix BGE_NCP Translate(Scalar X, Scalar Y, Scalar Z);

    /*! @brief Scale the Matrix.
     *
     * Scale the Matrix.
     *
     * @param[in] X Scale along the X axis.
     * @param[in] Y Scale along the Y axis.
     * @param[in] Z Scale along the Z axis.
     *
     * @return const reference to the Matrix after scaling.
     */
    Matrix BGE_NCP Scale(Scalar X, Scalar Y, Scalar Z);

    /*! @brief Rotate the Matrix by Euler angles.
     *
     * Rotate the Matrix by Euler angles.
     *
     * @param[in] X Rotation in radians about the X axis.
     * @param[in] Y Rotation in radians about the Y axis.
     * @param[in] Z Rotation in radians about the Z axis.
     *
     * @return const reference to the Matrix after rotation.
     */
    Matrix BGE_NCP Rotate(Radians X, Radians Y, Radians Z);

    /*! @brief Rotate the Matrix by axis and angle.
     *
     * Rotate the Matrix by axis and angle.
     *
     * @param[in] Angle Rotation about the specified axis in radians.
     * @param[in] X X component of the axis.
     * @param[in] Y Y component of the axis.
     * @param[in] Z Z component of the axis.
     *
     * @return const reference to the Matrix after rotation.
     */
    Matrix BGE_NCP Rotate(Radians Angle, Scalar X, Scalar Y, Scalar Z);

}; /* Matrix */

} /* bakge */

#endif /* BAKGE_MATH_MATRIX_H */

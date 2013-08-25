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
     * @warn May be removed or deprecated in the near future.
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
     * @retval const reference to the Matrix.
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
     * @retval Reference to field at specified index.
     */
    BGE_INL Scalar& operator[](int BGE_NCP At)
    {
        return Val[At];
    }

    /*! @brief Matrix assignment operator.
     *
     * Matrix assignment operator.
     *
     * @retval const reference to the Matrix.
     */
    Matrix BGE_NCP operator=(Matrix BGE_NCP Other);

    /*! @brief Matrix multiplication operator.
     *
     * Matrix multiplication operator.
     *
     * @param[in] Other Right operand.
     *
     * @retval Result matrix from multiplication of left and right operands.
     */
    Matrix operator*(Matrix BGE_NCP Other) const;

    /*! @brief Matrix multiplication compound operator.
     *
     * Matrix multiplication compound operator.
     *
     * @param[in] Other Right operand.
     *
     * @retval const reference to the matrix after compounded multiplication
     * with right operand.
     */
    Matrix BGE_NCP operator*=(Matrix BGE_NCP Other);

    Matrix BGE_NCP Invert();
    Matrix Inverted() const;

    Matrix Transposed() const;
    Matrix BGE_NCP Transpose();

    Scalar Determinant() const;

    /* Set to an identity matrix */
    Matrix BGE_NCP SetIdentity();

    /* Create a perspective matrix transform */
    Matrix BGE_NCP SetPerspective(Scalar FOV, Scalar Aspect, Scalar NearClip,
                                                            Scalar FarClip);

    Matrix BGE_NCP SetOrthographic(Scalar Left, Scalar Right, Scalar Bottom,
                                        Scalar Top, Scalar Near, Scalar Far);

    /* Create a viewing matrix transform */
    Matrix BGE_NCP SetLookAt(Vector4 BGE_NCP Position, Vector4 BGE_NCP Target,
                                                    Vector4 BGE_NCP UpVector);

    static Matrix Scaling(Scalar X, Scalar Y, Scalar Z);
    static Matrix Translation(Scalar X, Scalar Y, Scalar Z);
    static Matrix Rotation(Scalar X, Scalar Y, Scalar Z);
    static Matrix Rotation(Radians Angle, Scalar X, Scalar Y, Scalar Z);

    Matrix BGE_NCP Translate(Scalar X, Scalar Y, Scalar Z);
    Matrix BGE_NCP Scale(Scalar X, Scalar Y, Scalar Z);
    Matrix BGE_NCP Rotate(Radians X, Radians Y, Radians Z);
    Matrix BGE_NCP Rotate(Radians Angle, Scalar X, Scalar Y, Scalar Z);

}; /* Matrix */

} /* bakge */

#endif /* BAKGE_MATH_MATRIX_H */

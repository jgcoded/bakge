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
            /* Individual columns using SSE vectors */
            __m128 C1, C2, C3, C4;
        };

        struct
        {
            Scalar M11, M12, M13, M14; /* Column 1 */
            Scalar M21, M22, M23, M24; /* Column 2 */
            Scalar M31, M32, M33, M34; /* Column 3 */
            Scalar M41, M42, M43, M44; /* Column 4 */
        };

        struct
        {
            Vector4 Vec[4];
        };

        struct
        {
            Scalar Val[16];
        };
    };


public:

    static const Matrix Identity;

    Matrix();
    ~Matrix();
    Matrix(Matrix BGE_NCP Other);
    Matrix(Scalar A, Scalar B, Scalar C, Scalar D,
           Scalar E, Scalar F, Scalar G, Scalar H,
           Scalar I, Scalar J, Scalar K, Scalar L,
           Scalar M, Scalar N, Scalar O, Scalar P);

    BGE_INL Scalar BGE_NCP operator[](int BGE_NCP At) const
    {
        return Val[At];
    }


    BGE_INL Scalar& operator[](int BGE_NCP At)
    {
        return Val[At];
    }

    Matrix BGE_NCP operator=(Matrix BGE_NCP Other);

    Matrix operator*(Matrix BGE_NCP Other) const;

    Matrix BGE_NCP operator*=(Matrix BGE_NCP Other);

    Matrix BGE_NCP Invert();
    Matrix Inverted() const;

    Scalar Determinant() const;

    /* Set to an identity matrix */
    Matrix BGE_NCP SetIdentity();

    /* Create a perspective matrix transform */
    Matrix BGE_NCP SetPerspective(Scalar FOV, Scalar Aspect, Scalar NearClip,
                                                            Scalar FarClip);

    /* Create a viewing matrix transform */
    Matrix BGE_NCP SetLookAt(Vector4 BGE_NCP Position, Vector4 BGE_NCP Target,
                                                    Vector4 BGE_NCP UpVector);

    static Matrix ScaleMatrix(Scalar X, Scalar Y, Scalar Z);
    static Matrix TranslationMatrix(Scalar X, Scalar Y, Scalar Z);

    Matrix BGE_NCP Translate(Scalar X, Scalar Y, Scalar Z);
    Matrix BGE_NCP Scale(Scalar X, Scalar Y, Scalar Z);

}; /* Matrix */

} /* bakge */

#endif /* BAKGE_MATH_MATRIX_H */

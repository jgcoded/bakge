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

#ifdef BGE_USE_SIMD
/* SSE and SSE2 instructions headers */
#include <mmintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#endif /* BGE_USE_SIMD */

namespace bakge
{

const Matrix Matrix::Identity;

Matrix::Matrix()
{
    SetIdentity();
}


Matrix::~Matrix()
{
}


Matrix::Matrix(Scalar A, Scalar B, Scalar C, Scalar D,
           Scalar E, Scalar F, Scalar G, Scalar H,
           Scalar I, Scalar J, Scalar K, Scalar L,
           Scalar M, Scalar N, Scalar O, Scalar P)
{
    Val[0] = A;
    Val[1] = B;
    Val[2] = C;
    Val[3] = D;
    Val[4] = E;
    Val[5] = F;
    Val[6] = G;
    Val[7] = H;
    Val[8] = I;
    Val[9] = J;
    Val[10] = K;
    Val[11] = L;
    Val[12] = M;
    Val[13] = N;
    Val[14] = O;
    Val[15] = P;
}


Matrix::Matrix(Vector4 BGE_NCP A, Vector4 BGE_NCP B, Vector4 BGE_NCP C,
                                                    Vector4 BGE_NCP D)
{
    Val[0] = A[0];
    Val[1] = A[1];
    Val[2] = A[2];
    Val[3] = A[3];
    Val[4] = B[0];
    Val[5] = B[1];
    Val[6] = B[2];
    Val[7] = B[3];
    Val[8] = C[0];
    Val[9] = C[1];
    Val[10] = C[2];
    Val[11] = C[3];
    Val[12] = D[0];
    Val[13] = D[1];
    Val[14] = D[2];
    Val[15] = D[3];
}


Matrix::Matrix(Matrix BGE_NCP Other)
{
    *this = Other;
}


Matrix BGE_NCP Matrix::operator=(Matrix BGE_NCP Other)
{
    for(int i=0;i<16;++i)
        Val[i] = Other.Val[i];

    return *this;
}


Matrix Matrix::operator*(Matrix BGE_NCP Other) const
{
    Matrix Result = *this;
    Result *= Other;
    return Result;
}


Matrix BGE_NCP Matrix::operator*=(Matrix BGE_NCP Other)
{
#ifdef BGE_USE_SIMD
    /* Temp vectors */
    __m128 T1, T2, C1, C2, C3, C4;

    /* Set columns of other matrix */
    C1 = _mm_setr_ps(Other[0], Other[1], Other[2], Other[3]);
    C2 = _mm_setr_ps(Other[4], Other[5], Other[6], Other[7]);
    C3 = _mm_setr_ps(Other[8], Other[9], Other[10], Other[11]);
    C4 = _mm_setr_ps(Other[12], Other[13], Other[14], Other[15]);

    /* Matrix may not be properly aligned. So we'll use a "messenger" */
    BGE_ALIGN(16) Vector4 Messenger;

    T1 = _mm_set1_ps(Val[0]);
    T2 = _mm_mul_ps(C1, T1);
    T1 =_mm_set1_ps(Val[1]);
    T2 = _mm_add_ps(_mm_mul_ps(C2, T1), T2);
    T1 =_mm_set1_ps(Val[2]);
    T2 = _mm_add_ps(_mm_mul_ps(C3, T1), T2);
    T1 =_mm_set1_ps(Val[3]);
    T2 = _mm_add_ps(_mm_mul_ps(C4, T1), T2);

    _mm_store_ps(&Messenger[0], T2);
    Val[0] = Messenger[0];
    Val[1] = Messenger[1];
    Val[2] = Messenger[2];
    Val[3] = Messenger[3];

    T1 = _mm_set1_ps(Val[4]);
    T2 = _mm_mul_ps(C1, T1);
    T1 =_mm_set1_ps(Val[5]);
    T2 = _mm_add_ps(_mm_mul_ps(C2, T1), T2);
    T1 =_mm_set1_ps(Val[6]);
    T2 = _mm_add_ps(_mm_mul_ps(C3, T1), T2);
    T1 =_mm_set1_ps(Val[7]);
    T2 = _mm_add_ps(_mm_mul_ps(C4, T1), T2);

    _mm_store_ps(&Messenger[0], T2);
    Val[4] = Messenger[0];
    Val[5] = Messenger[1];
    Val[6] = Messenger[2];
    Val[7] = Messenger[3];

    T1 = _mm_set1_ps(Val[8]);
    T2 = _mm_mul_ps(C1, T1);
    T1 =_mm_set1_ps(Val[9]);
    T2 = _mm_add_ps(_mm_mul_ps(C2, T1), T2);
    T1 =_mm_set1_ps(Val[10]);
    T2 = _mm_add_ps(_mm_mul_ps(C3, T1), T2);
    T1 =_mm_set1_ps(Val[11]);
    T2 = _mm_add_ps(_mm_mul_ps(C4, T1), T2);

    _mm_store_ps(&Messenger[0], T2);
    Val[8] = Messenger[0];
    Val[9] = Messenger[1];
    Val[10] = Messenger[2];
    Val[11] = Messenger[3];

    T1 = _mm_set1_ps(Val[12]);
    T2 = _mm_mul_ps(C1, T1);
    T1 =_mm_set1_ps(Val[13]);
    T2 = _mm_add_ps(_mm_mul_ps(C2, T1), T2);
    T1 =_mm_set1_ps(Val[14]);
    T2 = _mm_add_ps(_mm_mul_ps(C3, T1), T2);
    T1 =_mm_set1_ps(Val[15]);
    T2 = _mm_add_ps(_mm_mul_ps(C4, T1), T2);

    _mm_store_ps(&Messenger[0], T2);
    Val[12] = Messenger[0];
    Val[13] = Messenger[1];
    Val[14] = Messenger[2];
    Val[15] = Messenger[3];
#else
    Matrix Result;
    memset((void*)&Result[0], 0, sizeof(Scalar) * 16);

    for(int i=0;i<4;++i) {
        for(int j=0;j<4;++j) {
            for(int k=0;k<4;++k) {
                Result[i*4+k] += Val[i*4+j] * Other.Val[j*4+k];
            }
        }
    }

    for(int i=0;i<16;++i)
        Val[i] = Result[i];
#endif /* BGE_USE_SIMD */

    return *this;
}


Matrix BGE_NCP Matrix::SetLookAt(Vector4 BGE_NCP Position,
                                    Vector4 BGE_NCP Target,
                                    Vector4 BGE_NCP UpVector)
{
    Vector4 Forward = Target - Position;
    Forward.Normalize();

    Vector4 Side = Cross(Forward, UpVector);
    Side.Normalize();

    Vector4 Up = Cross(Side, Forward);
    Up.Normalize();

    Val[0] = Side[0];
    Val[4] = Side[1];
    Val[8] = Side[2];

    Val[1] = Up[0];
    Val[5] = Up[1];
    Val[9] = Up[2];

    Val[2] = -Forward[0];
    Val[6] = -Forward[1];
    Val[10] = -Forward[2];

    Val[3] = Val[7] = Val[11] = 0;

    Val[12] = -Dot(Side, Position);
    Val[13] = -Dot(Up, Position);
    Val[14] = Dot(Forward, Position);

    return *this;
}


Matrix BGE_NCP Matrix::SetIdentity()
{
    memset((void*)Val, 0, sizeof(Scalar) * 16);
    Val[0] = 1.0f;
    Val[5] = 1.0f;
    Val[10] = 1.0f;
    Val[15] = 1.0f;

    return *this;
}


Matrix BGE_NCP Matrix::SetPerspective(Scalar FOV, Scalar Aspect,
                                Scalar NearClip, Scalar FarClip)
{
    Scalar Height = 1.0f / tanf(FOV * 0.5f * BGE_RAD_PER_DEG);
    Scalar Depth = NearClip - FarClip;

    if(ScalarCompare(Aspect, 0)) {
        return *this;
    }

    SetIdentity();
    Val[0] = Height / Aspect;
    Val[5] = Height;
    Val[10] = (NearClip + FarClip) / Depth;
    Val[11] = -1;
    Val[14] = (2.0f * NearClip * FarClip) / Depth;
    Val[15] = 0;

    return *this;
}


Matrix BGE_NCP Matrix::SetOrthographic(Scalar Left, Scalar Right,
                                        Scalar Bottom, Scalar Top,
                                        Scalar Near, Scalar Far)
{
    if(ScalarCompare(Left, Right) || ScalarCompare(Bottom, Top))
        return *this;

    SetIdentity();

    Scalar Width = Right - Left;
    Scalar Height = Top - Bottom;

    Val[0] = 2 / Width;
    Val[5] = 2 / Height;

    Scalar Depth = Far - Near;

    if(ScalarCompare(Depth, 0))
        return *this;

    Val[10] = -2 / Depth;
    Val[12] = (Right + Left) / (Left - Right);
    Val[13] = (Top + Bottom) / (Bottom - Top);
    Val[14] = (Far + Near) / -Depth;

    return *this;
}


Matrix Matrix::Scaling(Scalar X, Scalar Y, Scalar Z)
{
    return Matrix(
        X, 0, 0, 0,
        0, Y, 0, 0,
        0, 0, Z, 0,
        0, 0, 0, 1
    );
}


Matrix Matrix::Translation(Scalar X, Scalar Y, Scalar Z)
{
    return Matrix(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        X, Y, Z, 1
    );
}


Matrix Matrix::Rotation(Radians X, Radians Y, Radians Z)
{
    return Quaternion::FromEulerAngles(X, Y, Z).ToMatrix();
}


Matrix Matrix::Rotation(Radians Angle, Radians X, Radians Y, Radians Z)
{
    Scalar Cos = cosf(Angle);
    Scalar Sin = sinf(Angle);

    return Matrix(
        Cos + (X * X * (1 - Cos)),
        (X * Y * (1 - Cos)) + (Z * Sin),
        (X * Z * (1 - Cos)) - (Y * Sin),
        0,
        (X * Y * (1 - Cos)) - (Z * Sin),
        Cos + (Y * Y * (1 - Cos)),
        (Y * Z * (1 - Cos)) + (X * Sin),
        0,
        (X * Z * (1 - Cos)) + (Y * Sin),
        (Y * Z * (1 - Cos)) - (X * Sin),
        Cos + (Z * Z * (1 - Cos)),
        0,
        0, 0, 0, 1
    );
}


Matrix BGE_NCP Matrix::Translate(Scalar X, Scalar Y, Scalar Z)
{
    Val[12] += X;
    Val[13] += Y;
    Val[14] += Z;

    return *this;
}


Matrix BGE_NCP Matrix::Scale(Scalar X, Scalar Y, Scalar Z)
{
    /* May change in the future */
    *this *= Scaling(X, Y, Z);

    return *this;
}


Matrix BGE_NCP Matrix::Rotate(Radians X, Radians Y, Radians Z)
{
    *this *= Rotation(X, Y, Z);

    return *this;
}


Matrix BGE_NCP Matrix::Rotate(Radians Angle, Scalar X, Scalar Y, Scalar Z)
{
    *this *= Rotation(Angle, X, Y, Z);

    return *this;
}


Matrix BGE_NCP Matrix::Invert()
{
    return *this;
}


Matrix Matrix::Inverted() const
{
    return Matrix();
}


Scalar Matrix::Determinant() const
{
    return Scalar(0);
}


Matrix Matrix::Transposed() const
{
    return *this;
}


Matrix BGE_NCP Matrix::Transpose()
{
    return *this;
}

} /* bakge */

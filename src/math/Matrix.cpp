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

/* SSE and SSE2 instructions headers */
#include <mmintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>

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
    T1 =_mm_set1_ps(Val[4]);
    T2 = _mm_add_ps(_mm_mul_ps(C2, T1), T2);
    T1 =_mm_set1_ps(Val[8]);
    T2 = _mm_add_ps(_mm_mul_ps(C3, T1), T2);
    T1 =_mm_set1_ps(Val[12]);
    T2 = _mm_add_ps(_mm_mul_ps(C4, T1), T2);

    _mm_store_ps(&Messenger[0], T2);
    Col[0] = Messenger;

    T1 = _mm_set1_ps(Val[1]);
    T2 = _mm_mul_ps(C1, T1);
    T1 =_mm_set1_ps(Val[5]);
    T2 = _mm_add_ps(_mm_mul_ps(C2, T1), T2);
    T1 =_mm_set1_ps(Val[9]);
    T2 = _mm_add_ps(_mm_mul_ps(C3, T1), T2);
    T1 =_mm_set1_ps(Val[13]);
    T2 = _mm_add_ps(_mm_mul_ps(C4, T1), T2);

    _mm_store_ps(&Messenger[0], T2);
    Col[1] = Messenger;

    T1 = _mm_set1_ps(Val[2]);
    T2 = _mm_mul_ps(C1, T1);
    T1 =_mm_set1_ps(Val[6]);
    T2 = _mm_add_ps(_mm_mul_ps(C2, T1), T2);
    T1 =_mm_set1_ps(Val[10]);
    T2 = _mm_add_ps(_mm_mul_ps(C3, T1), T2);
    T1 =_mm_set1_ps(Val[14]);
    T2 = _mm_add_ps(_mm_mul_ps(C4, T1), T2);

    _mm_store_ps(&Messenger[0], T2);
    Col[2] = Messenger;

    T1 = _mm_set1_ps(Val[3]);
    T2 = _mm_mul_ps(C1, T1);
    T1 =_mm_set1_ps(Val[7]);
    T2 = _mm_add_ps(_mm_mul_ps(C2, T1), T2);
    T1 =_mm_set1_ps(Val[11]);
    T2 = _mm_add_ps(_mm_mul_ps(C3, T1), T2);
    T1 =_mm_set1_ps(Val[15]);
    T2 = _mm_add_ps(_mm_mul_ps(C4, T1), T2);

    _mm_store_ps(&Messenger[0], T2);
    Col[3] = Messenger;
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
    Scalar Max = NearClip * tan(FOV * 0.5f * BGE_RAD_PER_DEG);
    Scalar YMin = -Max;
    Scalar XMin = -Max;
    Scalar Width = Max - XMin;
    Scalar Height = Max - YMin;
    Scalar Depth = FarClip - NearClip;
    Scalar Q = (NearClip + FarClip) / -Depth;
    Scalar QN = 2 * (NearClip * FarClip) / -Depth;
    Scalar W = 2 * NearClip / Width;
    Scalar H = 2 * NearClip / Height;

    if(ScalarCompare(Aspect, 0)) {
        return *this;
    }

    W /= Aspect;

    SetIdentity();
    Val[0] = W;
    Val[5] = H;
    Val[10] = Q;
    Val[11] = -1;
    Val[14] = QN;
    Val[15] = 0;

    return *this;
}


Matrix Matrix::ScaleMatrix(Scalar X, Scalar Y, Scalar Z)
{
    return Matrix(
        X, 0, 0, 0,
        0, Y, 0, 0,
        0, 0, Z, 0,
        0, 0, 0, 1
    );
}


Matrix Matrix::TranslationMatrix(Scalar X, Scalar Y, Scalar Z)
{
    return Matrix(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        X, Y, Z, 1
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
    *this *= ScaleMatrix(X, Y, Z);

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

} /* bakge */

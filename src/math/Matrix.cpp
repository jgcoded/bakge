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

namespace bakge
{
namespace math
{

const Matrix Matrix::Identity;

Matrix::Matrix()
{
    SetIdentity();
}


Matrix::~Matrix()
{
}


Matrix Matrix::CreateLookAt(Vector4 BGE_NCP CameraPos,
                            Vector4 BGE_NCP CameraTarget,
                            Vector4 BGE_NCP CameraUpVector)
{

    Matrix mat;

    Vector4 dPosition = CameraPos - CameraTarget;
    Vector4 dPosUpX = Cross(dPosition, CameraUpVector);

    dPosition.Normalize();
    dPosUpX.Normalize();

    Vector4 dPosOffX = Cross(dPosition, dPosUpX);

    mat[0] = dPosUpX[0];
    mat[1] = dPosOffX[0];
    mat[2] = dPosition[0];
    mat[3] = 0;
    mat[4] = dPosUpX[1];
    mat[5] = dPosOffX[1];
    mat[6] = dPosition[1];
    mat[7] = 0;
    mat[8] = dPosUpX[2];
    mat[9] = dPosOffX[2];
    mat[10] = dPosition[2];
    mat[11] = 0;
    mat[12] = -Dot(dPosUpX, CameraPos);
    mat[13] = -Dot(dPosOffX, CameraPos);
    mat[14] = -Dot(dPosition, CameraPos);
    mat[15] = 1;

    return mat;
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
    Scalar S, Clip1, Clip2;

    SetIdentity();

    S = 1 / tan(FOV * 0.5f * BGE_RAD_PER_DEG);
    Clip1 = -FarClip / (FarClip - NearClip);
    Clip2 = (-FarClip * NearClip) / (FarClip - NearClip);

    Val[0] = S / Aspect;
    Val[5] = S;
    Val[10] = Clip1;
    Val[11] = Clip2;
    Val[14] = -1;

    return *this;
}

} /* math */
} /* bakge */


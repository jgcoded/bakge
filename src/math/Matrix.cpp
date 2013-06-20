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

Matrix::Matrix()
{
}


Matrix::~Matrix()
{
}


Scalar& Matrix::operator[](int BGE_NCP At)
{
    return Val[At];
}


Scalar BGE_NCP Matrix::operator[](int BGE_NCP At) const
{
    return Val[At];
}


static Matrix BGE_NCP CreateLookAt(Vector3 BGE_NCP CameraPos, Vector3 BGE_NCP CameraTarget,
                                                            Vector3 BGE_NCP CameraUpVector)
{
    
    Matrix mat;

    Vector3 dPosition = Vector3::Normalize(CameraPos - CameraTarget);
    Vector3 dPosUpX = Vector3::Normalize(Vector3::Cross(dPosition, CameraUpVector));
    Vector3 dPosOffX = Vector3::Cross(dPosition, dPosUpX);

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
    mat[12] = -Vector3::Dot(dPosUpX, CameraPos);
    mat[13] = -Vector3::Dot(dPosOffX, CameraPos);
    mat[14] = -Vector3::Dot(dPosition, CameraPos);
    mat[15] = 1;
    
    return mat;
}


} /* math */
} /* bakge */


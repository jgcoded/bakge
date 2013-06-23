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


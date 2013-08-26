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

#ifndef BAKGE_GRAPHICS_CAMERA3D_H
#define BAKGE_GRAPHICS_CAMERA3D_H

#include <bakge/Bakge.h>

namespace bakge
{

class BGE_API Camera3D : public Camera
{

protected:

    Vector4 Target;
    Degrees FOV;
    Scalar Aspect;
    Scalar Near;
    Scalar Far;


public:

    Camera3D();
    ~Camera3D();

    Vector4 BGE_NCP SetTarget(Scalar X, Scalar Y, Scalar Z);
    Vector4 BGE_NCP GetTarget() const;

    virtual Result Bind() const;
    virtual Result Unbind() const;

    BGE_INL Degrees SetFOV(Degrees F)
    {
        FOV = F;

        return FOV;
    }

    BGE_INL Degrees GetFOV() const
    {
        return FOV;
    }

    BGE_INL Scalar SetAspect(Scalar R)
    {
        Aspect = R;

        return Aspect;
    }

    BGE_INL Scalar SetNearClip(Scalar N)
    {
        Near = N;

        return Near;
    }

    BGE_INL Scalar GetNearClip() const
    {
        return Near;
    }

    BGE_INL Scalar SetFarClip(Scalar F)
    {
        Far = F;

        return Far;
    }

    BGE_INL Scalar GetFarClip() const
    {
        return Far;
    }

}; /* Camera3D */

} /* bakge */

#endif /* BAKGE_GRAPHICS_CAMERA3D_H */

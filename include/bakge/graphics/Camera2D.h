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

#ifndef BAKGE_GRAPHICS_CAMERA2D_H
#define BAKGE_GRAPHICS_CAMERA2D_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Used for rendering 2D scenes.
 *
 * Camera2D objects are used for rendering 2D scenes. The position of the
 * camera corresponds to the bottom left corner of the viewport. The span
 * of the scene are width and height of the scene. The top right corner
 * is located at position + span.
 *
 * Since Camera2D is used for rendering 2-dimensional scenes, the third
 * field in the position corresponds to the Z location of the near clipping
 * plane, and the third field in the span corresponds to the Z location of
 * the far clipping plane.
 */
class BGE_API Camera2D : public Camera
{

protected:

    Vector4 Span;


public:

    /*! @brief Default Camera2D constructor.
     *
     * Default Camera2D constructor.
     */
    Camera2D();

    /*! @brief Camera2D destructor.
     *
     * Camera2D destructor.
     */
    ~Camera2D();

    /*! @brief Bind viewing and projection transforms in OpenGL.
     *
     * Binding a Camera2D sets up OpenGL state so that the scene is rendered
     * from the camera's position and span. The camera's position and span
     * are measured in pixels.
     */
    virtual Result Bind() const;

    /*! @brief Set viewing and projection transforms to defaults.
     *
     * Set viewing and projection transforms to defaults.
     */
    virtual Result Unbind() const;

    BGE_INL Vector4 BGE_NCP SetSpan(Scalar Width, Scalar Height, Scalar Far)
    {
        Span[0] = Width;
        Span[1] = Height;
        Span[2] = Far;

        return Span;
    }

    BGE_INL Vector4 BGE_NCP GetSpan() const
    {
        return Span;
    }

}; /* Camera2D */

} /* bakge */

#endif /* BAKGE_GRAPHICS_CAMERA2D_H */

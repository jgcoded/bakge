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
 * @file Camera3D.h
 * @brief Camera3D class declaration.
 */

#ifndef BAKGE_GRAPHICS_CAMERA3D_H
#define BAKGE_GRAPHICS_CAMERA3D_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Represents arbitrary view and projection transforms for rendering
 * scenes in 3D Cartesian space.
 *
 * The Camera3D class is used for rendering three-dimensional scenes. It
 * represents an arbitrary viewing transformation from which the scene
 * is viewed, and a perspective projection transformation.
 *
 * @todo Have Camera3D perhaps inherit pawn so a Quaternion can be derived from
 * its look-at configuration.
 */
class BGE_API Camera3D : public Node
{

protected:

    Vector4 Target;
    Degrees FOV;
    Scalar Aspect;
    Scalar Near;
    Scalar Far;


public:

    /*! @brief Default Camera3D constructor.
     *
     * Default Camera3D constructor.
     */
    Camera3D();

    /*! @brief Camera3D destructor.
     *
     * Camera3D destructor.
     */
    ~Camera3D();

    /*! @brief Set the Camera3D's eye target.
     *
     * Set the Camera3D's eye target. The scene is rendered with the camera's
     * position and eye target lined up in the center of the viewport.
     *
     * @param[in] X X position of the eye target.
     * @param[in] Y Y position of the eye target.
     * @param[in] Z Z position of the eye target.
     *
     * @return const reference to the Camera3D's eye target, after assignment.
     */
    Vector4 BGE_NCP SetTarget(Scalar X, Scalar Y, Scalar Z);

    /*! @brief Get the Camera3D's eye target.
     *
     * Get the Camera3D's eye target.
     *
     * @return const reference to the Camera3D's eye target.
     */
    Vector4 BGE_NCP GetTarget() const;

    /*! @brief Bind the Camera3D's viewing and projection transforms in OpenGL.
     *
     * Bind the Camera3D's viewing and projection transforms in OpenGL. If
     * certain shader uniforms are not present in the currently bound Shader,
     * Bind will return BGE_FAILURE, even when the uniforms that are present
     * have successfully been bound.
     *
     * @return BGE_SUCCESS if the camera's transforms were successfully bound
     * to OpenGL state; BGE_FAILURE if any errors occurred or an incomplete
     * binding occurred due to missing uniforms.
     */
    virtual Result Bind() const;

    /*! @brief Bind default viewing and projection transforms in OpenGL.
     *
     * Bind default viewing and projection transforms in OpenGL. If certain
     * shader uniforms are not present in the currently bound Shader, Unbind
     * will return BGE_FAILURE, even when the uniforms that are present have
     * successfully been bound.
     *
     * @return BGE_SUCCESS if default view and projection transforms were
     * bound to OpenGL; BGE_FAILURE if any errors occurred or an incomplete
     * binding occurred due to missing uniforms.
     */
    virtual Result Unbind() const;

    /*! @brief Set the Camera3D's perspective field of view in degrees.
     *
     * Set the Camera3D's perspective field of view in degrees.
     *
     * @param[in] F New field of view in degrees.
     *
     * @return Degree value of the new field of view.
     */
    BGE_INL Degrees SetFOV(Degrees F)
    {
        FOV = F;

        return FOV;
    }

    /*! @brief Get the degree value of the Camera3D's field of view.
     *
     * Get the degree value of the Camera3D's field of view.
     *
     * @return Degree value of the Camera3D's field of view.
     */
    BGE_INL Degrees GetFOV() const
    {
        return FOV;
    }

    /*! @brief Set the aspect ratio of the perspective transformation.
     *
     * Set the aspect ratio of the perspective transformation. The ratio
     * is width to height (Width / Height).
     *
     * @param[in] R New aspect ratio.
     *
     * @return Value of the new aspect ratio.
     */
    BGE_INL Scalar SetAspect(Scalar R)
    {
        Aspect = R;

        return Aspect;
    }

    /*! @brief Set the near clipping plane Z value.
     *
     * Set the near clipping plane Z value.
     *
     * @param[in] N Z value of the new near clipping plane.
     *
     * @return Z value of the new near clipping plane.
     */
    BGE_INL Scalar SetNearClip(Scalar N)
    {
        Near = N;

        return Near;
    }

    /*! @brief Get the near clipping plane Z value.
     *
     * Get the near clipping plane Z value.
     *
     * @return Z value of the near clipping plane.
     */
    BGE_INL Scalar GetNearClip() const
    {
        return Near;
    }

    /*! @brief Set the far clipping plane Z value.
     *
     * Set the far clipping plane Z value.
     *
     * @param[in] F Z value of the new far clipping plane.
     *
     * @return Z value of the new far clipping plane.
     */
    BGE_INL Scalar SetFarClip(Scalar F)
    {
        Far = F;

        return Far;
    }

    /*! @brief Get the far clipping plane Z value.
     *
     * Get the far clipping plane Z value.
     *
     * @return Z value of the far clipping plane.
     */
    BGE_INL Scalar GetFarClip() const
    {
        return Far;
    }

}; /* Camera3D */

} /* bakge */

#endif /* BAKGE_GRAPHICS_CAMERA3D_H */

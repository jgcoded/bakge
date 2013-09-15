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
 * @file Pawn.h
 * @brief Pawn class declaration.
 */

#ifndef BAKGE_GRAPHICS_PAWN_H
#define BAKGE_GRAPHICS_PAWN_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief A representation of an object with a position, facing and scale.
 *
 * Pawns describe an object that has a facing (rotation) and scale, in
 * addition to the inherent Node position. When rendering objects in space
 * a pawn is bound to send OpenGL state so the object is rendered in that
 * position, rotation and scale.
 */
class BGE_API Pawn : public Node
{

protected:

    /*! @brief Default Pawn constructor.
     *
     * Default Pawn constructor.
     */
    Pawn();


public:

    /*! @brief Virtual Pawn destructor.
     *
     * Virtual Pawn destructor.
     */
    virtual ~Pawn();

    /*! @brief Allocates and initializes a Pawn instance.
     *
     * Allocates and initializes a Pawn instance.
     *
     * @return Pointer to allocated Pawn; NULL if any errors occurred.
     */
    BGE_FACTORY Pawn* Create();

    /*! @brief Set OpenGL state so objects are rendered in this Pawn's
     * orientation.
     *
     * Set OpenGL state so objects are rendered in this Pawn's orientation.
     *
     * @return BGE_SUCCESS if the Pawn was successfully bound; BGE_FAILURE if
     * any errors occurred.
     */
    virtual Result Bind() const;

    /*! @brief Set OpenGL state to arbitrary defaults, preventing this Pawn's
     * orientation from being used to render objects.
     *
     * Set OpenGL state to arbitrary defaults, preventing this Pawn's
     * orientation from being used to render objects.
     *
     * @return BGE_SUCCESS if the Pawn was successfully unbound; BGE_FAILURE
     * if any errors occurred.
     */
    virtual Result Unbind() const;

    /*! @brief Non-uniformly scale the Pawn by given amounts.
     *
     * Non-uniformly scale the Pawn by given amounts.
     *
     * @param[in] X Amount to scale along the X axis.
     * @param[in] Y Amount to scale along the Y axis.
     * @param[in] Z Amount to scale along the Z axis.
     *
     * @return BGE_SUCCESS if the Pawn was successfully scaled; BGE_FAILURE
     * if any errors occurred.
     *
     * @todo Return constref to Pawn's scale from this method, instead of a
     * bakge::Result.
     */
    virtual Result SetScale(Scalar X, Scalar Y, Scalar Z);

    /*! @brief Get the Pawn's scale along three axes (X, Y, Z).
     *
     * Get the Pawn's scale along three axes (X, Y, Z).
     *
     * @return constref to Pawn's scale.
     */
    virtual Vector4 BGE_NCP GetScale() const;

    /*! @brief Set the Pawn's Quaternion rotation.
     *
     * Set the Pawn's Quaternion rotation.
     *
     * @param[in] Rotation Quaternion representing new rotation for the Pawn.
     *
     * @return constref to Pawn's rotation, after assignment.
     *
     * @todo Pass Rotation as a constref to prevent copy.
     */
    Quaternion BGE_NCP SetRotation(Quaternion Rotation);

    /*! @brief Get the Pawns' Quaternion rotation.
     *
     * Get the Pawns' Quaternion rotation.
     *
     * @return constref to Pawn's rotation.
     */
    Quaternion BGE_NCP GetRotation() const;


protected:

    Quaternion Facing;
    Vector4 Scale;

}; /* Pawn */

} /* bakge */

#endif /* BAKGE_GRAPHICS_PAWN_H */

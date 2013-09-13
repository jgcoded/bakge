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
 * @file Crowd.h
 * @brief Crowd class declaration.
 */

#ifndef BAKGE_GRAPHICS_CROWD_H
#define BAKGE_GRAPHICS_CROWD_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief A grouping of Pawns typically used for instanced rendering.
 *
 * Crowds are large groups of pawns that are drawn using instanced rendering
 * techniques, to avoid the large overhead associated with numerous draw calls.
 * The Crowd class provides a way to manage its members as a whole or as
 * individuals through various methods. Internally the Crowd uses a dynamically
 * allocated array to store data about its members.
 *
 * Typically the Crowd is used for instanced rendering, but it could also see
 * use as a storage class for arbitrary groups of Pawns or Nodes that don't
 * necessarily get rendered, such as pathing waypoints.
 *
 * When rendered using Mesh::DrawInstanced, Crowds use a different set of
 * shader attributes than Nodes or Pawns.
 *
 * @see VertexLib
 */
class BGE_API Crowd : public Pawn
{

protected:

    /* Number of active members in Crowd */
    int Population;

    /* Maximum number of members without resizing the buffer */
    int Capacity;

    /* Dynamically allocated arrays - members' transforms */
    Scalar* Positions;
    Quaternion* Rotations;
    Scalar* Scales;

    /* Buffer for the Crowd's members' model matrices */
    GLuint CrowdBuffer;

    /*! @brief Default Crowd constructor.
     *
     * Default Crowd constructor.
     */
    Crowd();


public:

    /*! @brief Virtual Crowd destructor.
     *
     * Virtual Crowd destructor.
     */
    virtual ~Crowd();

    /*! @brief Create a Crowd with a given capacity.
     *
     * Allocates a Crowd and creates storage for a given number of members.
     *
     * @param[in] ReserveMembers Capacity for the new Crowd.
     *
     * @return Pointer to allocated Crowd; NULL if any errors occurred.
     */
    BGE_FACTORY Crowd* Create(int ReserveMembers);

    virtual Result Bind() const;
    virtual Result Unbind() const;

    BGE_INL int GetCapacity() const
    {
        return Capacity;
    }

    BGE_INL int GetPopulation() const
    {
        return Population;
    }

    Result Clear();
    Result Reserve(int NumMembers);

    Result TranslateMember(int MemberIndex, Scalar X, Scalar Y, Scalar Z);
    Result RotateMember(int MemberIndex, Quaternion Rotation);
    Result ScaleMember(int MemberIndex, Scalar X, Scalar Y, Scalar Z);

}; /* Crowd */

} /* bakge */

#endif /* BAKGE_GRAPHICS_CROWD_H */

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

#ifndef BAKGE_GRAPHICS_CROWD_H
#define BAKGE_GRAPHICS_CROWD_H

#include <bakge/Bakge.h>

namespace bakge
{

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

    Crowd();


public:

    virtual ~Crowd();

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
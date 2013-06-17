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

#ifndef BAKGE_MATH_QUATERNION_H
#define BAKGE_MATH_QUATERNION_H

#include <bakge/Bakge.h>

namespace bakge
{
namespace math
{

/* *
 * Quaternions are used to describe rotational orientations in 3D space.
 * They consist of four parts - Three which represent an axis, and the fourth
 * which represents a rotation about that axis (right-handed rule).
 * Quaternions are extremely useful because they avoid gimbal lock, a problem
 * that can arise from the use of Euler angles to store info.
 * Not only that, but quaternions are easy to turn into 4x4 matrices, split
 * into the individual parts (axis and angle) and can easily be created
 * from Euler angles.
 *
 * Quaternions also see use in animation keyframing, where joints' or bones'
 * rotations are relative to their parent joint.
 * */
class Quaternion
{

public:

    Quaternion();
    ~Quaternion();


private:

    Vector4 Val; /* X, Y, Z - vector, W - real */

}; /* Quaternion */

} /* math */
} /* bakge */

#endif /* BAKGE_MATH_QUATERNION_H */


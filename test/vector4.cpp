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

#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>

void printVector(bakge::math::Vector4 vec)
{
    for(int i = 0; i < 3; ++i)
        printf("[%d] = %f\n", i, vec[i]);
    printf("\n");
}

int main(int argc, char* argv[])
{
    bakge::Init(argc, argv);

    bakge::math::Vector4 Vec1(5, -2, 0, 0);

    /* *
     * Run some operations for testing
     * */

    /* Equate two vectors */
    printf("Equate two Vectors:\n");
    bakge::math::Vector4 Vec2 = Vec1;
    printVector(Vec2);
    printf("%s\n\n", (Vec1 == Vec2) ? "True" : "False");

    /* Multiply and Divide Vector3 */
    printf("Multiply and Divide two Vectors:\n");
    Vec2 *= bakge::math::Scalar(1.5);
    Vec1 /= bakge::math::Scalar(1.5);
    printVector(Vec2);
    printVector(Vec1);

    /* Normalize a Vector4 */
    printf("Normalize a Vector4:\n");
    printVector(Vec1);
    Vec1.Normalize();
    printVector(Vec1);

    /* Unit Vector */
    printf("Unit Vector:\n");
    bakge::math::Vector4 Vec3 = bakge::math::UnitVector(4, 3, 2);
    printVector(Vec3);

    /* Length and Length^2 */
    printf("Length Length^2:\nVec1 Length: %f\nVec2 Length^2: %f\n\n",
                                Vec1.Length(), Vec2.LengthSquared());

    /* Dot */
    bakge::math::Scalar dot = bakge::math::Dot(Vec1, Vec2);
    printf("Dot:\n%f\n\n", dot);

    /* Cross */
    printf("Cross:\n");
    bakge::math::Vector4 Vec4, x1(2, 3, 2, 0), x2(1, 2, 3, 0);
    Vec4 = bakge::math::Cross(x1, x2);
    printVector(Vec4);


    /* *
     *This will send an assertion failure!
     * */

    /* Add and Subtract two points*/
    printf("Add and Subtract two points:\n");
    Vec2 += Vec1;
    printVector(Vec2);
    
    Vec1 -= bakge::math::Point(4, -1, 4);
    printVector(Vec1);

    bakge::Deinit();

    return 0;
}


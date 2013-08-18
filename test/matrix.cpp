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

 /* SSE and SSE2 instructions headers */
#include <mmintrin.h>
#include <emmintrin.h>

#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>

void PrintMatrix(bakge::Matrix BGE_NCP M)
{
    printf("[ %03.2f %03.2f %03.2f %03.2f ]\n", M[0], M[4], M[8], M[12]);
    printf("[ %03.2f %03.2f %03.2f %03.2f ]\n", M[1], M[5], M[9], M[13]);
    printf("[ %03.2f %03.2f %03.2f %03.2f ]\n", M[2], M[6], M[10], M[14]);
    printf("[ %03.2f %03.2f %03.2f %03.2f ]\n", M[3], M[7], M[11], M[15]);
}

int main(int argc, char* argv[])
{
    bakge::Init(argc, argv);

    bakge::Matrix M;
    bakge::Microseconds Time = bakge::GetRunningTime();

    M.SetIdentity();
    for(int i=0;i<50000;++i)
        M *= bakge::Matrix::Identity;

    Time = bakge::GetRunningTime() - Time;
    printf("Running for %ul microseconds\n", Time);

    M.Translate(1, 1, 1);
    PrintMatrix(M);

    bakge::Deinit();

    return 0;
}

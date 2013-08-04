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

Remote::Remote()
{
    IP[0] = 0;
    IP[1] = 0;
    IP[2] = 0;
    IP[3] = 0;
    Port = 0;
    FullAddress = 0;
}


Remote::~Remote()
{
}


Remote BGE_NCP Remote::SetAddress(Byte A, Byte B, Byte C, Byte D)
{
    IP[0] = A;
    IP[1] = B;
    IP[2] = C;
    IP[3] = D;

    FullAddress = (IP[0] << 24) | (IP[1] << 16) | (IP[2] << 8) | IP[3];

    return *this;
}


void Remote::GetAddressParts(Byte* A, Byte* B, Byte* C, Byte* D) const
{
    *A = IP[0];
    *B = IP[1];
    *C = IP[2];
    *D = IP[3];
}


int Remote::GetAddress() const
{
    return FullAddress;
}


Remote BGE_NCP Remote::SetPort(int P)
{
    Port = P;

    return *this;
}


int Remote::GetPort() const
{
    return Port;
}

} /* bakge */

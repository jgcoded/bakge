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
 * @file Format.h
 * @brief Data layout structs used in decoding Bakge file formats.
 */

#ifndef BAKGE_INTERNAL_FORMAT_H
#define BAKGE_INTERNAL_FORMAT_H

#include <bakge/Bakge.h>

#define BGE_BMF_V100 "BAKGEMESHFILE0000000000000000000"

namespace bakge
{
namespace bmf
{
namespace layout100
{

struct Header
{
    char FormatName[32]; // Always BAKGEMESHFILE0000000000000000000
    union
    {
        struct
        {
            Byte Type;
            Byte Major;
            Byte Minor;
            Byte Revision;
        };
    };
};

struct Vertex
{
    Scalar Position[3];
    Scalar Normal[3];
    Scalar TexCoord[2];
};

struct Triangle
{
    uint32 Indices[3];
};

} // layout100
} // bmf
} // bakge

#endif // BAKGE_INTERNAL_FORMAT_H

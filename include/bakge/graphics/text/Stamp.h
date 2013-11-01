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
 * @file Stamp.h
 * @brief Stamp class declaration.
 */

#ifndef BAKGE_GRAPHICS_TEXT_STAMP_H
#define BAKGE_GRAPHICS_TEXT_STAMP_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief A Rectangle specifically used for rending text glyphs.
 *
 * The dimensions of the quad (two triangles) drawn on screen are
 * changed to match the properties of the currently picked glyph.
 */
class BGE_API Stamp : public Rectangle
{

public:

    /*! @brief Default Stamp constructor.
     *
     * Default Stamp constructor.
     */
    Stamp();

    /*! @brief Stamp destructor.
     *
     * Stamp destructor.
     */
    ~Stamp();

    Result Pick(const Glyph* G);

    virtual Result Bind() const;

    virtual Result Unbind() const;

    virtual Result Draw() const;

}; // Stamp

} // bakge

#endif // BAKGE_GRAPHICS_TEXT_STAMP_H

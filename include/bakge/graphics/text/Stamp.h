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
    struct {
        Scalar X;
        Scalar Y;
    } Start, Current, Offset;

    Scalar Adv;
    Scalar ScaleFactor;


protected:

    /*! @brief Default Stamp constructor.
     *
     * Default Stamp constructor.
     */
    Stamp();


public:

    /*! @brief Stamp destructor.
     *
     * Stamp destructor.
     */
    ~Stamp();

    BGE_FACTORY Stamp* Create();

    Result SetDimensions(Scalar Width, Scalar Height);

    Result SetTexCoords(Scalar S0, Scalar T0, Scalar S1, Scalar T1);

    virtual Result Bind() const;

    Result Advance();

    Result Begin(Scalar X, Scalar Y);

    Result Kern(Scalar Amount);

    BGE_INL Scalar SetAdvance(Scalar A)
    {
        Adv = A;

        return A;
    }

    BGE_INL Scalar GetAdvance() const
    {
        return Adv;
    }

    BGE_INL void SetOffsets(Scalar X, Scalar Y)
    {
        Offset.X = X;
        Offset.Y = Y;
    }

    BGE_INL void GetOffsets(Scalar* X , Scalar* Y)
    {
        *X = Offset.X;
        *Y = Offset.Y;
    }

    BGE_INL Scalar SetScaleFactor(Scalar F)
    {
        ScaleFactor = F;

        return F;
    }

    BGE_INL Scalar GetScaleFactor() const
    {
        return ScaleFactor;
    }

}; // Stamp

} // bakge

#endif // BAKGE_GRAPHICS_TEXT_STAMP_H

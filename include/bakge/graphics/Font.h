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
 * @file Font.h
 * @brief Font class delcaration.
 */

#ifndef BAKGE_GRAPHICS_FONT_H
#define BAKGE_GRAPHICS_FONT_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Wrapper class for TrueType fonts.
 *
 * The Font class serves as a wrapper for font metadata. It has a public API
 * for getting key information about a font such as vertical line spacing,
 * kerning advance, and more. It also provides an API for baking glyph maps
 * into a bakge::Texture.
 *
 * This class does not serve to render text in any way. Baking glyph map
 * textures simply collects glyph bitmaps into a large texture and uploads
 * them into OpenGL textures. Text rendering itself is usually done with
 * quads drawn on the screen; managing different glyph maps as well as
 * determining positioning and metrics of these quads is left to end-users.
 *
 * The glyph maps are uploaded as alphamaps; the raw data sent to OpenGL
 * contains only alpha values with no color information. As such it is
 * recommended you use a specialized text rendering shader.
 */
class BGE_API Font
{
    stbtt_fontinfo FontInfo;

    Font();


public:

    ~Font();

    BGE_FACTORY Font* Load(const char* FontData);

    int Bake(Texture** Target, int GlyphStart, int GlyphEnd, int PixelHeight);

}; /* Font */

} /* bakge */

#endif /* BAKGE_GRAPHICS_FONT_H */

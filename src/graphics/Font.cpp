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

Font::Font()
{
    NumGlyphs = 0;
    GlyphData = NULL;
    Glyphs = NULL;
    ScaleValue = 0;
}


Font::~Font()
{
    if(GlyphData != NULL)
        delete[] GlyphData;

    if(Glyphs != NULL)
        delete Glyphs;
}


Result Font::Bind() const
{
    return Glyphs->Bind();
}


Result Font::Unbind() const
{
    return Glyphs->Unbind();
}


Font* Font::Load(const char* FontData, Scalar FontHeight)
{
    PHYSFS_addToSearchPath("C:/", 0);

    if(PHYSFS_exists(FontData) == 0) {
        printf("Unable to locate file %s\n", FontData);
        return NULL;
    }

    PHYSFS_file* FontFile = PHYSFS_openRead(FontData);
    if(FontFile == NULL) {
        printf("Unable to load font file\n");
        return NULL;
    }

    PHYSFS_sint64 Size = PHYSFS_fileLength(FontFile);
    if(Size < 0) {
        printf("Unable to get file length\n");
        return NULL;
    }

    unsigned char* Data = new unsigned char[Size];
    if(Data == NULL) {
        printf("Error allocating file data buffer\n");
        return NULL;
    }

    int BytesRead = PHYSFS_read(FontFile, (void*)Data, 1, Size);
    if(BytesRead < 0) {
        printf("Error reading file data\n");
        return NULL;
    }

    stbtt_fontinfo FontInfo;
    stbtt_InitFont(&FontInfo, Data, 0);

    Font* F = new Font;
    if(F == NULL) {
        printf("Error allocating Font memory\n");
        return NULL;
    }

    F->NumGlyphs = FontInfo.numGlyphs;
    F->GlyphData = new stbtt_bakedchar[F->NumGlyphs];
    F->ScaleValue = stbtt_ScaleForPixelHeight(&FontInfo, FontHeight);

#define FSZ 512
    Byte* GlyphsAlpha = new Byte[FSZ * FSZ];

    int BakeResult = stbtt_BakeFontBitmap(Data, 0, FontHeight, GlyphsAlpha,
                                                            FSZ, FSZ, 0,
                                                            F->NumGlyphs,
                                                            (F->GlyphData));
    if(BakeResult == 0) {
        printf("Unable to bake any characters to texture\n");
        delete F;
        return NULL;
    } else if(BakeResult > 0) {
        printf("Baked all %d glyphs to texture\n", F->NumGlyphs);
    } else {
        printf("Baked %d of %d glyphs to texture\n", -BakeResult,
                                                    F->NumGlyphs);
    }

    // Create glyphs alpha-only texture. Use a special shader to render text.
    F->Glyphs = bakge::Texture::Create(FSZ, FSZ, GL_ALPHA, GL_UNSIGNED_BYTE,
                                                            GlyphsAlpha);
    if(F->Glyphs == NULL) {
        printf("Error creating font glyphs texture\n");
        delete F;
        return NULL;
    }

    // Cleanup
    PHYSFS_close(FontFile);
    delete[] GlyphsAlpha;

    return F;
}

} /* bakge */

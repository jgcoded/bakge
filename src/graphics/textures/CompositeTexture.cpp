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

CompositeTexture::CompositeTexture()
{
}


CompositeTexture::~CompositeTexture()
{
}


CompositeTexture* CompositeTexture::Create(int W, int H, int C,
                                const void* BL, const void* TL,
                                const void* TR, const void* BR,
                                const void* HG, const void* VG,
                                                const void* F)
{
    BeginLogBlock();
    Log("CompositeTexture::Create %dx%d\n", W, H);

    if(W < C * 2 || H < C * 2) {
        Log("  ERROR: Invalid dimensions based on corner size.\n");
        EndLogBlock();
        return NULL;
    }

    CompositeTexture* Tex = new CompositeTexture;
    if(Tex == NULL) {
        Log("  ERROR: Couldn't allocate memory.\n");
        EndLogBlock();
        return NULL;
    }

    // Working memory. We'll fill this with appropriate data before creating
    // the texture
    Byte* Bitmap = new Byte[W * H * 4];
    if(Bitmap == NULL) {
        Log("  ERROR: Couldn't allocate working memory.\n");
        EndLogBlock();
        delete Tex;
        return NULL;
    }

    Byte* Offset = Bitmap;

    // Copy bottom-left corner
    for(int i=0;i<C;++i)
        memcpy(Offset+(i*W*4), (Byte*)BL+((C-i-1)*4*C), sizeof(Byte)*4*C);

    // Copy bottom-right corner
    Offset = Bitmap + ((W-C) * 4);
    for(int i=0;i<C;++i)
        memcpy(Offset + (i*W*4), (Byte*)BR+((C-i-1)*4*C), sizeof(Byte)*4*C);

    // Copy top-left corner
    Offset = Bitmap + (W * 4 * (H-C));
    for(int i=0;i<C;++i)
        memcpy(Offset + (i*W*4), (Byte*)TL+((C-i-1)*4*C), sizeof(Byte)*4*C);

    // Copy top-right corner
    Offset = Bitmap + (W * 4 * (H-C)) + ((W-C) * 4);
    for(int i=0;i<C;++i)
        memcpy(Offset + (i*W*4), (Byte*)TR+((C-i-1)*4*C), sizeof(Byte)*4*C);

    // Copy vertical gradients
    Offset = Bitmap + (C * 4);
    Byte* Offset2 = Bitmap + (W*4*(H-C)) + (C*4);
    for(int i=0;i<C;++i) {
        for(int j=0;j<W - (C * 2);++j) {
            memcpy(Offset+(i*W*4)+(j*4), (Byte*)VG+(i*4), sizeof(Byte)*4);
            memcpy(Offset2+(i*W*4)+(j*4), (Byte*)VG+((C-i-1)*4),
                                                sizeof(Byte)*4);
        }
    }

    Offset = Bitmap + (W*4*C);
    for(int i=0;i<H - (C * 2);++i) {
        memcpy(Offset + (i*W*4), HG, sizeof(Byte) * 4  * C);
    }

    // Copy right-edge in reverse
    Offset = Bitmap + (W*4*C) + ((W-C)*4);
    for(int i=0;i<C;++i) {
        memcpy(Offset+(i*4), (Byte*)HG + ((C-i-1)*4), sizeof(Byte) * 4);
    }

    // Copy through-out the rest of the edge
    for(int i=0;i<H - (C*2);++i) {
        memcpy(Offset + (i*W*4), Offset, sizeof(Byte) * 4 * C);
    }

    // Copy in fill
    Offset = Bitmap + (C*4*W) + (C*4);
    for(int i=0;i<H - (C*2);++i) {
        for(int j=0;j<W - (C*2);++j) {
            memcpy(Offset + (i*4*W) + (j*4), F, sizeof(Byte) * 4);
        }
    }

    glGenTextures(1, &Tex->TextureID);

    Tex->Width = W;
    Tex->Height = H;

    glBindTexture(GL_TEXTURE_2D, Tex->TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA,
                                    GL_UNSIGNED_BYTE, Bitmap);
    glBindTexture(GL_TEXTURE_2D, 0);

    EndLogBlock();

    delete Bitmap;

    return Tex;
}

} // bakge

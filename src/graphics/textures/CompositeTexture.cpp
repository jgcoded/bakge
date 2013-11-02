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
namespace gdk
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
    static const GLint DefaultParams[] = {
        GL_TEXTURE_MIN_FILTER, GL_NEAREST,
        GL_TEXTURE_MAG_FILTER, GL_NEAREST,
        GL_TEXTURE_WRAP_S, GL_REPEAT,
        GL_TEXTURE_WRAP_T, GL_REPEAT,
        0
    };

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

    // Copy bottom-left corner
    for(int i=0;i<C;++i)
        memcpy(Bitmap + (i*H), BL, sizeof(Byte) * 4 * C);

    glGenTextures(1, &Tex->TextureID);

    Tex->Width = W;
    Tex->Height = H;

    glBindTexture(GL_TEXTURE_2D, Tex->TextureID);

    // Pick out and set texture parameters/values
    const GLint* Params = DefaultParams;
    GLint i = 0;
    GLint Pair[2]; // Index 0 is parameter name; 1 is value
    GLint At = 0;
    while(Params[i] != 0) {
        Pair[At] = Params[i];
        // If we just picked a value, set the texture parameter
        if(At == 1)
            glTexParameteri(GL_TEXTURE_2D, Pair[0], Pair[1]);

#ifdef _DEBUG
        if(glGetError() == GL_INVALID_ENUM) {
            Log("Texture: Invalid parameter name %x or value %x\n", Pair[0],
                                                                    Pair[1]);
            return NULL;
        }
#endif // _DEBUG

        At ^= 1; // Flip between 0 and 1
        ++i;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA,
                                    GL_UNSIGNED_BYTE, Bitmap);
    glBindTexture(GL_TEXTURE_2D, 0);

    EndLogBlock();

    return Tex;
}

} // gdk
} // bakge

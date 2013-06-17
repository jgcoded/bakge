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

Texture::Texture()
{
    TextureID = 0;
}


Texture::~Texture()
{
    if(TextureID != 0)
        glDeleteTextures(1, &TextureID);
}


Result Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, TextureID);
    return BGE_SUCCESS;
}


Result Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
    return BGE_SUCCESS;
}


Texture* Texture::Create(int Width, int Height, GLint Format, GLenum Type,
                                                              void* Data)
{
    Texture* NewTexture = new Texture;

    /* Generate an "ID" that we can reference */
    glGenTextures(1, &(NewTexture->TextureID));

    /* Check if Generate worked */
    if(NewTexture->TextureID == 0) {
        printf("GL Generate Texture Error\n");
        delete NewTexture;
        return NULL;
    }

    /* Bind the texture, code below applies only to this texture */
    NewTexture->Bind();

    /* *
     * START TEXTURE PARAMETERS CONFIG
     * See: http://www.opengl.org/sdk/docs/man/xhtml/glTexParameter.xml
     * For definitions of the parameters in glTexParamterf
     * */
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    /* END TEXTURE PARAMETERS */

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, Format, Type,
                                                                    Data);

    NewTexture->Unbind();

    return NewTexture;
}

} /* bakge */

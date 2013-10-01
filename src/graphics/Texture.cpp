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
#ifdef _DEBUG
#include <bakge/internal/Debug.h>
#endif // _DEBUG

namespace bakge
{

Texture::Texture()
{
    Location = GL_TEXTURE0;
    TextureID = 0;
    Width = 0;
    Height = 0;
}


Texture::~Texture()
{
    if(TextureID != 0)
        glDeleteTextures(1, &TextureID);
}


Result Texture::Bind() const
{
#ifdef _DEBUG
    while(glGetError() != GL_NO_ERROR)
        ;
#endif // _DEBUG

    glActiveTexture(Location);

    glBindTexture(GL_TEXTURE_2D, TextureID);

#ifdef _DEBUG
    if(glGetError() == GL_INVALID_VALUE) {
        printf("Invalid texture name %d\n", TextureID);
        return BGE_FAILURE;
    }
#endif // _DEBUG

    return BGE_SUCCESS;
}


Result Texture::Unbind() const
{
    glActiveTexture(Location);
    glBindTexture(GL_TEXTURE_2D, 0);

    return BGE_SUCCESS;
}


Texture* Texture::Create(int Width, int Height, const GLint* Params,
                                            GLint Format, GLenum Type,
                                                            void* Data)
{
    static const GLint DefaultParams[] = {
        GL_TEXTURE_MIN_FILTER, GL_LINEAR,
        GL_TEXTURE_MAG_FILTER, GL_LINEAR,
        GL_TEXTURE_WRAP_S, GL_REPEAT,
        GL_TEXTURE_WRAP_T, GL_REPEAT,
        0
    };

#ifdef _DEBUG
    int Max;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max);

    if(Width < 0 || Width >= Max) {
        printf("Invalid texture width %d\n", Width);
        return NULL;
    }

    if(Height < 0 || Height >= Max) {
        printf("Invalid texture height %d\n", Height);
        return NULL;
    }

    /* *
     * When a buffer is bound to GL_PIXEL_UNPACK_BUFFER, there are a few
     * misleading GL_INVALID_OPERATION errors that can occur.
     * */
    GLint BufferBinding;
    glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &BufferBinding);
    if(BufferBinding != 0) {
        printf("Cannot create a texture while a non-zero name is bound to "
                                                "GL_PIXEL_UNPACK_BUFFER\n");
        return NULL;
    }
#endif // _DEBUG

    Texture* NewTexture = new Texture;

    NewTexture->Width = Width;
    NewTexture->Height = Height;

    /* Generate an OpenGL texture */
    glGenTextures(1, &(NewTexture->TextureID));

#ifdef _DEBUG
    /* Check if error occured while generating the texture */
    if(NewTexture->TextureID == 0) {
        printf("Error generating texture\n");
        delete NewTexture;
        return NULL;
    }
#endif /* _DEBUG */

    /* Bind the texture so we can set its parameters below */
    NewTexture->Bind();

    if(Params == NULL)
        Params = DefaultParams;

#ifdef _DEBUG
    while(glGetError() != GL_NO_ERROR)
        ;
#endif //_DEBUG

    // Pick out and set texture parameters/values
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
            printf("Invalid parameter name %x or value %x\n", Pair[0],
                                                            Pair[1]);
            delete NewTexture;
            return NULL;
        }
#endif // _DEBUG

        At ^= 1; // Flip between 0 and 1
        ++i;
    }

#ifdef _DEBUG
    while(glGetError() != GL_NO_ERROR)
        ;
#endif // _DEBUG

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, Format, Type,
                                                                    Data);

#ifdef _DEBUG
    GLenum Error;
    do {
        Error = glGetError();
        switch(Error) {

        case GL_INVALID_ENUM:
            printf("Invalid pixel data type %x\n", Type);
            break;

        // Some pixel types require specific formats (we only use GL_RGBA)
        case GL_INVALID_OPERATION:
            printf("Incompatible pixel data type %x\n", Type);
            break;

        case GL_NO_ERROR:
            break;

        default:
            printf("Unexpected OpenGL error %x\n", Error);
        }
    } while(Error != GL_NO_ERROR);
#endif // _DEBUG

    NewTexture->Unbind();

    return NewTexture;
}


Result Texture::SetLocation(GLenum Loc)
{
#ifdef _DEBUG
    // Determine max texture units available
    int TexUnits;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &TexUnits);

    if(Loc < GL_TEXTURE0 || Loc >= (GLenum)(GL_TEXTURE0 + TexUnits)) {
        printf("Invalid texture location %d. Valid range is "
                                    "[GL_TEXTURE0, GL_TEXTURE%d]\n",
                                            Location, TexUnits - 1);
        return BGE_FAILURE;
    }
#endif // _DEBUG

    Location = Loc;

    return BGE_SUCCESS;
}

} /* bakge */

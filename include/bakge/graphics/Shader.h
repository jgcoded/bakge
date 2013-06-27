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

#ifndef BAKGE_GRAPHICS_SHADER_H
#define BAKGE_GRAPHICS_SHADER_H

#include <bakge/Bakge.h>

namespace bakge
{

class Shader
{
    GLuint Handle;

    /* *
     * Private version of the shader factory. The public
     * static methods are really just for convenience. This
     * function does all the heavy lifting.
     * */
    static Shader* LoadFromFile(GLenum Type, const char* FilePath);
    static Shader* LoadFromString(GLenum Type, const char* Source,
                                                const char* Name);


public:

    Shader();
    ~Shader();

    /* *
     * Loads the vertex and fragment shaders from provided paths.
     * Shaders can then be attached to a ShaderProgram object
     * */
    BGE_FACTORY Shader* LoadVertexShaderFile(const char* FilePath);
    BGE_FACTORY Shader* LoadFragmentShaderFile(const char* FilePath);

    /* Name helps identify a shader when compiling it */
    BGE_FACTORY Shader* LoadVertexShaderString(const char* Source,
                                               const char* Name);
    BGE_FACTORY Shader* LoadFragmentShaderString(const char* Source,
                                                 const char* Name);

    GLuint GetHandle() const;

}; /* Shader */

} /* bakge */

#endif /* BAKGE_GRAPHICS_SHADER_H */

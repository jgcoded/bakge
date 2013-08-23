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

#define BGE_VIEW_UNIFORM "bge_View"
#define BGE_PERSPECTIVE_UNIFORM "bge_Perspective"
#define BGE_DIFFUSE_UNIFORM "bge_Diffuse"
#define BGE_CROWD_UNIFORM "bge_Crowd"

#define BGE_MODEL_ATTRIBUTE "bge_Model"
#define BGE_VERTEX_ATTRIBUTE "bge_Vertex"
#define BGE_NORMAL_ATTRIBUTE "bge_Normal"
#define BGE_TEXCOORD_ATTRIBUTE "bge_TexCoord"

namespace bakge
{

class BGE_API Shader : public Bindable
{
    static Shader* GenericShader;
    static GLuint VertexLib;
    static GLuint FragmentLib;
    friend Window* Window::Create(int, int);

    static Result InitShaderLibrary();
    static Result DeinitShaderLibrary();
    friend BGE_API Result Init(int, char*[]);
    friend BGE_API Result Deinit();

    GLuint Vertex;
    GLuint Fragment;
    GLuint Program;

    Result Link();
    Result Unlink();
    Result DeleteShaders();
    Result DeleteProgram();

    /* *
     * Compile a shader and report any errors or warnings
     * Returns BGE_FAILURE if compilation failed
     * */
    static Result Compile(GLuint Handle);


public:

    Shader();
    ~Shader();

    BGE_FACTORY Shader* LoadFromStrings(int NumVertex, int NumFragment,
                                            const char** VertexShaders,
                                            const char** FragmentShaders);

    Result Bind() const;
    Result Unbind() const;

}; /* Shader */

} /* bakge */

#endif /* BAKGE_GRAPHICS_SHADER_H */

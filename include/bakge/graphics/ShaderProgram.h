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

#ifndef BAKGE_GRAPHICS_SHADERPROGRAM_H
#define BAKGE_GRAPHICS_SHADERPROGRAM_H

#include <bakge/Bakge.h>

#define BGE_VIEW_UNIFORM "bge_View"
#define BGE_PERSPECTIVE_UNIFORM "bge_Perspective"
#define BGE_DIFFUSE_UNIFORM "bge_Diffuse"

#define BGE_MODEL_ATTRIBUTE "bge_Model"
#define BGE_VERTEX_ATTRIBUTE "bge_Vertex"
#define BGE_NORMAL_ATTRIBUTE "bge_Normal"
#define BGE_TEXCOORD_ATTRIBUTE "bge_TexCoord"

namespace bakge
{

class BGE_API ShaderProgram : public Bindable
{
    friend BGE_API Result Init(int argc, char* argv[]);
    friend BGE_API Result Deinit();

    /* Initialize all library Shaders */
    static Result InitShaderLibrary();
    static Result DeinitShaderLibrary();

    static Shader* VertexShaderLib;
    static Shader* FragmentShaderLib;
    static Shader* GenericVertexShader;
    static Shader* GenericFragmentShader;

    Shader* VertexShader;
    Shader* FragmentShader;

    GLuint ProgramHandle;


public:

    ShaderProgram();
    ~ShaderProgram();

    Result Bind() const;
    Result Unbind() const;

    /* *
     * Create a shader program from given vertex and fragment shaders
     * If NULL is passed, a generic default shader is instead used.
     * */
    BGE_FACTORY ShaderProgram* Create(Shader* Vertex, Shader* Fragment);

}; /* ShaderProgram */

} /* bakge */

#endif /* BAKGE_GRAPHICS_SHADERPROGRAM_H */

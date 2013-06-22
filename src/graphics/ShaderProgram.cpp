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

Shader* ShaderProgram::GenericVertexShader = NULL;
Shader* ShaderProgram::GenericFragmentShader = NULL;
Shader* ShaderProgram::bgeWorldTransform = NULL;

const char* bgeWorldTransformSource =
    "#version 120\n"
    "\n"
    "uniform vec4 bge_Position;\n"
    "uniform mat4x4 bge_Rotation;\n"
    "uniform mat4x4 bge_Scale;\n"
    "\n"
    "vec4 bgeWorldTransform(vec4 Vertex)\n"
    "{\n"
    "    return Vertex + bge_Position;\n"
    "}\n"
    "\n";

const char* GenericVertexShaderSource =
    "#version 120\n"
    "\n"
    "vec4 bgeWorldTransform(vec4);\n"
    "\n"
    "attribute vec4 bge_VertexArray;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = bgeWorldTransform(bge_VertexArray);\n"
    "}\n"
    "\n";

const char* GenericFragmentShaderSource =
    "#version 120\n"
    "\n"
    "uniform sampler2D bge_Diffuse;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = texture2D(bge_Diffuse, gl_TexCoord[0].st);\n"
    "}\n"
    "\n";


Result ShaderProgram::InitShaderLibrary()
{
    /* Load the default plain vertex shader */
    GenericVertexShader = Shader::LoadVertexShaderString(
                                    GenericVertexShaderSource);
    if(GenericVertexShader == NULL)
        return BGE_FAILURE;

    /* Load the default plain fragment shader */
    GenericFragmentShader = Shader::LoadFragmentShaderString(
                                    GenericFragmentShaderSource);
    if(GenericFragmentShader == NULL)
        return BGE_FAILURE;

    /* Load the shader library function bgeWorldTransform(vec4) */
    bgeWorldTransform = Shader::LoadVertexShaderString(
                                    bgeWorldTransformSource);
    if(bgeWorldTransform == NULL)
        return BGE_FAILURE;

    return BGE_SUCCESS;
}


Result ShaderProgram::DeinitShaderLibrary()
{
    delete GenericVertexShader;
    delete GenericFragmentShader;
    delete bgeWorldTransform;

    return BGE_SUCCESS;
}


ShaderProgram::ShaderProgram()
{
}


ShaderProgram::~ShaderProgram()
{
}


ShaderProgram* ShaderProgram::Create(Shader* Vertex, Shader* Fragment)
{
    return NULL;
}

} /* bakge */


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
Shader* ShaderProgram::bgeFragmentShaderLib = NULL;

const char* bgeWorldTransformSource =
    "#version 120\n"
    "\n"
    "uniform vec4 bge_Position;\n"
    "uniform mat4x4 bge_Rotation;\n"
    "uniform mat4x4 bge_Scale;\n"
    "uniform mat4x4 bge_Perspective;\n"
    "uniform mat4x4 bge_View;\n"
    "\n"
    "attribute vec4 bge_Vertex;\n"
    "attribute vec4 bge_Normal;\n"
    "\n"
    "attribute vec2 bge_TexCoord;\n"
    "varying vec2 bge_TexCoord0;\n"
    "\n"
    "varying vec4 bge_TransformedNormal;\n"
    "\n"
    "vec4 bgeWorldTransform()\n"
    "{\n"
    "    bge_TransformedNormal = (bge_Perspective * bge_View) * bge_Normal;\n"
    "    bge_TexCoord0 = bge_TexCoord;\n"
    "    return (bge_Perspective * bge_View) * bge_Vertex;\n"
    "}\n"
    "\n";

const char* GenericVertexShaderSource =
    "#version 120\n"
    "\n"
    "vec4 bgeWorldTransform();\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = bgeWorldTransform();\n"
    "}\n"
    "\n";

const char* bgeFragmentShaderLibSource =
    "#version 120\n"
    "\n"
    "varying vec4 bge_TransformedNormal;\n"
    "varying vec2 bge_TexCoord0;\n"
    "\n"
    "uniform sampler2D bge_Diffuse;\n"
    "\n"
    "vec4 bgeColor()\n"
    "{\n"
    "    float ShadeValue = dot(vec4(bge_TransformedNormal.xyz, 0),"
    "                                           vec4(0, 0, 1, 0));\n"
    "    ShadeValue = pow(max(abs(ShadeValue), 0.1f), 0.15f);\n"
    "    return texture2D(bge_Diffuse, bge_TexCoord0) * ShadeValue;"
    "}\n"
    "\n";

const char* GenericFragmentShaderSource =
    "#version 120\n"
    "\n"
    "vec4 bgeColor();\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = bgeColor();\n"
    "}\n"
    "\n";


Result ShaderProgram::InitShaderLibrary()
{
    /* Load the default plain vertex shader */
    GenericVertexShader = Shader::LoadVertexShaderString(
                                    GenericVertexShaderSource,
                                    "GenericVertexShader");
    if(GenericVertexShader == NULL)
        return BGE_FAILURE;

    /* Load the default plain fragment shader */
    GenericFragmentShader = Shader::LoadFragmentShaderString(
                                GenericFragmentShaderSource,
                                "GenericFragmentShaderSource");
    if(GenericFragmentShader == NULL)
        return BGE_FAILURE;

    /* Load the shader library function bgeWorldTransform(vec4) */
    bgeWorldTransform = Shader::LoadVertexShaderString(
                                    bgeWorldTransformSource,
                                    "bgeWorldTransform");
    if(bgeWorldTransform == NULL)
        return BGE_FAILURE;

    bgeFragmentShaderLib = Shader::LoadFragmentShaderString(
                                    bgeFragmentShaderLibSource,
                                    "bgeFragmentShaderLib");
    if(bgeFragmentShaderLib == NULL)
        return BGE_FAILURE;

    return BGE_SUCCESS;
}


Result ShaderProgram::DeinitShaderLibrary()
{
    delete GenericVertexShader;
    delete GenericFragmentShader;
    delete bgeWorldTransform;
    delete bgeFragmentShaderLib;

    return BGE_SUCCESS;
}


ShaderProgram::ShaderProgram()
{
    ProgramHandle = 0;
}


ShaderProgram::~ShaderProgram()
{
    if(ProgramHandle != 0) {
        /* Detach shaders from our program and delete it */
        glDetachShader(ProgramHandle, VertexShader->GetHandle());
        glDetachShader(ProgramHandle, FragmentShader->GetHandle());
        glDetachShader(ProgramHandle, bgeWorldTransform->GetHandle());
        glDeleteProgram(ProgramHandle);

        /* *
         * We only want to delete the vertex/frag shaders if they are
         * not the default generic shaders (part of the library)
         * */
        if(VertexShader != GenericVertexShader)
            delete VertexShader;

        if(FragmentShader != GenericFragmentShader)
            delete FragmentShader;
    }
}


ShaderProgram* ShaderProgram::Create(Shader* Vertex, Shader* Fragment)
{
    ShaderProgram* Program;
    GLuint Handle;

    Program = new ShaderProgram;

    Program->ProgramHandle = glCreateProgram();
    if(Program->ProgramHandle == 0) {
        printf("Error creating shader program resource\n");
        delete Program;
        return NULL;
    }

    /* Alias for shader program's handle, for convenience */
    Handle = Program->ProgramHandle;

    /* Attach library shaders */
    glAttachShader(Handle, bgeWorldTransform->GetHandle());
    glAttachShader(Handle, bgeFragmentShaderLib->GetHandle());

    /* If user passes NULL to vertex shader arg, use default generic one */
    if(Vertex == NULL) {
        glAttachShader(Handle, GenericVertexShader->GetHandle());
        Program->VertexShader = GenericVertexShader;
    } else {
        glAttachShader(Handle, Vertex->GetHandle());
        Program->VertexShader = Vertex;
    }

    /* If user passes NULL to fragment shader arg, use default generic one */
    if(Fragment == NULL) {
        glAttachShader(Handle, GenericFragmentShader->GetHandle());
        Program->FragmentShader = GenericFragmentShader;
    } else {
        glAttachShader(Handle, Fragment->GetHandle());
        Program->FragmentShader = Fragment;
    }

    /* Now link the shader program and bind it as active */
    glLinkProgram(Handle);

    glUseProgram(Handle);

    return Program;
}


Result ShaderProgram::Bind() const
{
    glUseProgram(ProgramHandle);

    GLint DiffuseLocation;

    DiffuseLocation = glGetUniformLocation(ProgramHandle, BGE_DIFFUSE_UNIFORM);
    if(DiffuseLocation < 0) {
        printf("Invalid uniform requested\n");
        return BGE_FAILURE;
    }

    glUniform1i(DiffuseLocation, 0);

    return BGE_SUCCESS;
}


Result ShaderProgram::Unbind() const
{
    glUseProgram(0);
    return BGE_SUCCESS;
}

} /* bakge */

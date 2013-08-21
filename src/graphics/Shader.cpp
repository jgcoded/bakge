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

Shader* Shader::GenericShader = NULL;
GLuint Shader::VertexLib = 0;
GLuint Shader::FragmentLib = 0;

const char* VertexShaderLibSource =
    "#version 120\n"
    "\n"
    "attribute mat4x4 bge_Model;\n"
    "\n"
    "uniform mat4x4 bge_Perspective;\n"
    "uniform mat4x4 bge_View;\n"
    "\n"
    "uniform mat4x4 bge_Crowd;\n"
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
    "    mat4x4 bge_ModelMatrix = bge_Crowd * bge_Model;\n"
    "    mat4x4 bge_ViewProjectionMatrix = bge_Perspective * bge_View;\n"
    "\n"
    "    mat4x4 bge_ModelViewProjectionMatrix = bge_ViewProjectionMatrix\n"
    "                                                * bge_ModelMatrix;\n"
    "    bge_TransformedNormal = transpose(inverse(\n"
    "           bge_ModelViewProjectionMatrix)) * vec4(bge_Normal.xyz, 0);\n"
    "\n"
    "    bge_TexCoord0 = bge_TexCoord;\n"
    "\n"
    "    return bge_View * bge_ModelMatrix * bge_Vertex;\n"
    "}\n"
    "\n"
    "mat4x4 bgeProjection()\n"
    "{\n"
    "    return bge_Perspective;\n"
    "}\n"
    "\n";

const char* GenericVertexShaderSource =
    "varying vec4 bge_Position;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    bge_Position = bgeWorldTransform();\n"
    "    gl_Position = bgeProjection() * bge_Position;\n"
    "}\n"
    "\n";

const char* FragmentShaderLibSource =
    "#version 120\n"
    "\n"
    "varying vec4 bge_TransformedNormal;\n"
    "varying vec2 bge_TexCoord0;\n"
    "varying vec4 bge_Position;\n"
    "\n"
    "uniform sampler2D bge_Diffuse;\n"
    "\n"
    "vec4 bgeColor()\n"
    "{\n"
    "    float ShadeValue = dot(normalize(vec4(bge_TransformedNormal.xyz, 0)),"
    "                                                   vec4(0, 0, 1, 0));\n"
    "    ShadeValue = pow(min(abs(ShadeValue), 1.0f), 5.0f);\n"
    "    return texture2D(bge_Diffuse, bge_TexCoord0) * ShadeValue;"
    "}\n"
    "\n";

const char* GenericFragmentShaderSource =
    "void main()\n"
    "{\n"
    "    gl_FragColor = bgeColor();\n"
    "}\n"
    "\n";

const char* FragmentShaderLibHeader =
    "#version 120\n"
    "\n"
    "vec4 bgeColor();\n"
    "\n";

const char* VertexShaderLibHeader =
    "#version 120\n"
    "\n"
    "vec4 bgeWorldTransform();\n"
    "mat4x4 bgeProjection();\n";

Result Shader::InitShaderLibrary()
{
    VertexLib = glCreateShader(GL_VERTEX_SHADER);
    if(VertexLib == 0) {
        printf("Error creating library vertex shader\n");
        return BGE_FAILURE;
    }

    FragmentLib = glCreateShader(GL_FRAGMENT_SHADER);
    if(FragmentLib == 0) {
        printf("Error creating library fragment shader\n");
        return BGE_FAILURE;
    }

    glShaderSource(VertexLib, 1, &VertexShaderLibSource, NULL);
    glShaderSource(FragmentLib, 1, &FragmentShaderLibSource, NULL);

    if(Compile(VertexLib) == BGE_FAILURE) {
        printf("Error compiling library vertex shader\n");
        return BGE_FAILURE;
    }

    if(Compile(FragmentLib) == BGE_FAILURE) {
        printf("Error compiling library fragment shader\n");
        return BGE_FAILURE;
    }

    GenericShader = Shader::LoadFromStrings(1, 1, &GenericVertexShaderSource,
                                                &GenericFragmentShaderSource);
    if(GenericShader == NULL) {
        printf("Error creating generic shader\n");
        return BGE_FAILURE;
    }

    return BGE_SUCCESS;
}


Result Shader::DeinitShaderLibrary()
{
    if(GenericShader == NULL)
        return BGE_FAILURE;

    delete GenericShader;
    GenericShader = NULL;

    glDeleteShader(VertexLib);
    glDeleteShader(FragmentLib);

    return BGE_SUCCESS;
}


Shader::Shader()
{
    Program = 0;
    Vertex = 0;
    Fragment = 0;
}


Shader::~Shader()
{
    Unlink();
    DeleteShaders();
    DeleteProgram();
}


Result Shader::Link()
{
    if(Program == 0)
        return BGE_FAILURE;

    if(Vertex == 0 || Fragment == 0)
        return BGE_FAILURE;

    glAttachShader(Program, Vertex);
    glAttachShader(Program, Fragment);

    // Attach library shaders
    glAttachShader(Program, VertexLib);
    glAttachShader(Program, FragmentLib);

    glLinkProgram(Program);

    return BGE_SUCCESS;
}


Result Shader::Unlink()
{
    if(Program == 0)
        return BGE_FAILURE;

    if(Vertex == 0 || Fragment == 0)
        return BGE_FAILURE;

    glDetachShader(Program, Vertex);
    glDetachShader(Program, Fragment);

    // Detach library shaders
    glDetachShader(Program, VertexLib);
    glDetachShader(Program, FragmentLib);

    return BGE_SUCCESS;
}


Result Shader::DeleteShaders()
{
    Result Errors = BGE_SUCCESS;

    if(Vertex != 0) {
        glDeleteShader(Vertex);
        Vertex = 0;
    } else {
        Errors = BGE_FAILURE;
    }

    if(Fragment != 0) {
        glDeleteShader(Fragment);
        Vertex = 0;
    } else {
        Errors = BGE_FAILURE;
    }

    return Errors;
}


Result Shader::DeleteProgram()
{
    if(Program == 0)
        return BGE_FAILURE;

    glDeleteProgram(Program);
    Program = 0;

    return BGE_SUCCESS;
}


Shader* Shader::LoadFromStrings(int NumVertex, int NumFragment,
                                    const char** VertexShaders,
                                    const char** FragmentShaders)
{
    Shader* S;

    /* Allocate memory for the new Shader */
    S = new Shader;
    if(S == NULL) {
        printf("Unable to allocate new shader\n");
        return NULL;
    }

    S->Program = glCreateProgram();
    if(S->Program == 0) {
        printf("Error creating shader program\n");
        delete S;
        return NULL;
    }

    // Allocate a vertex shader
    S->Vertex = glCreateShader(GL_VERTEX_SHADER);
    if(S->Vertex == 0) {
        printf("Error creating vertex shader\n");
        delete S;
        return NULL;
    }

    // Allocate a fragment shader
    S->Fragment = glCreateShader(GL_FRAGMENT_SHADER);
    if(S->Fragment == 0) {
        printf("Error creating fragment shader\n");
        delete S;
        return NULL;
    }

    // Create new buffers which contain the shader libraries as well
    const char** VertexShaderBuffer = new const char*[NumVertex + 1];
    const char** FragmentShaderBuffer = new const char*[NumFragment + 1];

    for(int i=1;i<=NumVertex;++i)
        VertexShaderBuffer[i] = VertexShaders[i-1];

    for(int i=1;i<=NumFragment;++i)
        FragmentShaderBuffer[i] = FragmentShaders[i-1];

    FragmentShaderBuffer[0] = FragmentShaderLibHeader;
    VertexShaderBuffer[0] = VertexShaderLibHeader;

    // Set our shaders' sources
    glShaderSource(S->Vertex, NumVertex + 1, VertexShaderBuffer, NULL);
    glShaderSource(S->Fragment, NumFragment + 1, FragmentShaderBuffer, NULL);

    // Compile vertex shader and check for errors
    if(Compile(S->Vertex) == BGE_FAILURE) {
        printf("Vertex shader compilation failed\n");
        delete S;
        return NULL;
    }

    // Compile fragment shader and check for errors
    if(Compile(S->Fragment) == BGE_FAILURE) {
        printf("Fragment shader compilation failed\n");
        delete S;
        return NULL;
    }

    if(S->Link() == BGE_FAILURE) {
        printf("Shader link failed\n");
        delete S;
        return NULL;
    }

    return S;
}



Result Shader::Compile(GLuint Handle)
{
    if(Handle == 0)
        return BGE_FAILURE;

    Result Errors = BGE_SUCCESS;

    glCompileShader(Handle);

    GLint Status, Length;

    glGetShaderiv(Handle, GL_COMPILE_STATUS, &Status);
    if(Status == GL_FALSE)
        Errors = BGE_FAILURE;

    glGetShaderiv(Handle, GL_INFO_LOG_LENGTH, &Length);
    if(Length > 1) {
        char* Info = new char[Length];
        glGetShaderInfoLog(Handle, Length, NULL, Info);
        printf("%s\n", Info);
        delete[] Info;
    }

    return Errors;
}


Result Shader::Bind() const
{
    if(Program == 0)
        return BGE_FAILURE;

    glUseProgram(Program);

    return BGE_SUCCESS;
}


Result Shader::Unbind() const
{
    return GenericShader->Bind();
}

} /* bakge */

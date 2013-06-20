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

Shader::Shader()
{
    Handle = 0;
}


Shader::~Shader()
{
    if(Handle != 0)
        glDeleteShader(Handle);
}


Shader* Shader::Create(GLenum Type, const char* SourcePath)
{
    Shader* S;
    Byte* Source;
    GLint Status, Length;

    /* Load the contents of the shader file */
    Source = LoadFileContents(SourcePath);
    if(Source == NULL) {
        printf("Unable to load shader source \"%s\"\n", SourcePath);
        return NULL;
    }

    /* Allocate memory for the new Shader */
    S = new Shader;
    if(S == NULL) {
        printf("Unable to allocate new shader\n");
        return NULL;
    }

    /* Allocate a shader resource of provided type (vertex or fragment) */
    S->Handle = glCreateShader(Type);
    if(S->Handle == 0) {
        printf("Unable to create vertex shader resource\n");
        delete S;
        return NULL;
    }

    /* *
     * Set source for shader resource. Do the const cast since
     * compiler whines when passing non-const char*
     * */
    glShaderSource(S->Handle, 1, (const Byte**)&Source, NULL);
    delete[] Source;

    /* Compile the shader source */
    glCompileShader(S->Handle);

    /* Now get any errors or warnings */
    glGetShaderiv(S->Handle, GL_COMPILE_STATUS, &Status);
    if(Status == GL_FALSE)
        printf("Shader compilation failed: \"%s\"\n", SourcePath);

    glGetShaderiv(S->Handle, GL_INFO_LOG_LENGTH, &Length);
    if(Length > 0) {
        /* Re-use Source variable too. Waste not. */
        Source =  new Byte[Length];
        glGetShaderInfoLog(S->Handle, Length, &Length, Source);
        printf("%s\n", Source);
        delete[] Source;
        /* Don't return shader if compilation failed */
        if(Status == GL_FALSE) {
            delete S;
            S = NULL;
        }
    }

    return S;
}


Shader* Shader::CreateVertexShader(const char* SourcePath)
{
    return Shader::Create(GL_VERTEX_SHADER, SourcePath);
}


Shader* Shader::CreateFragmentShader(const char* SourcePath)
{
    return Shader::Create(GL_FRAGMENT_SHADER, SourcePath);
}

} /* bakge */


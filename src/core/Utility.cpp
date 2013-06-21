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

Byte* LoadFileContents(const char* Path)
{
    FILE* FileHandle;
    long Length;
    Byte* FileContent;

    FileHandle = fopen(Path, "rb");
    if (FileHandle != NULL) {
        /* Get character count of file */
        fseek(FileHandle, 0, SEEK_END);
        Length = ftell(FileHandle);
        fseek(FileHandle, 0, SEEK_SET);
        /* Allocate memory and read in file contents */
        FileContent = (Byte*)malloc(Length + 1);
        FileContent[Length] = '\0';
        fread(FileContent, Length, 1, FileHandle);
        fclose(FileHandle);
        return FileContent;
    } else {
        return NULL;
    }
}


Window* SharedWindow;

Result Init(int argc, char* argv[])
{
    /* *
     * Will be defined in platform-specific utility sources.
     * This weird declaration is so that this function isn't
     * exposed as end-user API
     * */
    extern Result PlatformInit(int, char*[]);

    if(!glfwInit()) {
        printf("GLFW initialization failed\n");
        return BGE_FAILURE;
    }

    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    SharedWindow = Window::Create(16, 16);
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

    if(glewInit() != GLEW_OK) {
        printf("GLEW initialization failed\n");
        return BGE_FAILURE;
    }

    /* Initialize our Bakge shader library */
    if(ShaderProgram::InitShaderLibrary() != BGE_SUCCESS)
        return BGE_FAILURE;

    /* Run platform-specific initialization protocol */
    if(PlatformInit(argc, argv) != BGE_SUCCESS)
        return BGE_FAILURE;

    return BGE_SUCCESS;
}


Result Deinit()
{
    Result Ok;

    Ok = SharedWindow->Close();
    delete SharedWindow;

    ShaderProgram::DeinitShaderLibrary();

    glfwTerminate();

    return Ok;
}

} /* bakge */

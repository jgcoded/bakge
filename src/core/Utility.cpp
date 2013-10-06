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
#include <bakge/internal/Utility.h>
#ifdef _DEBUG
#include <bakge/internal/Debug.h>
#endif // _DEBUG
#define HAVE_SNPRINTF // Always use portable_*printf functions
#define PREFER_PORTABLE_SNPRINTF
extern "C"
{
#include <snprintf/snprintf.h>
}

namespace bakge
{

PHYSFS_File* LogFile = NULL;

Result Init(int argc, char* argv[])
{
    PHYSFS_init(argv[0]);
    PHYSFS_addToSearchPath(".", 0);
    PHYSFS_setWriteDir(".");

    LogFile = PHYSFS_openWrite("bakge.log");
    if(LogFile == NULL) {
        printf("Error opening log file: %s\n", PHYSFS_getLastError());
        return BGE_FAILURE;
    }

    if(!glfwInit()) {
        printf("GLFW initialization failed\n");
        return BGE_FAILURE;
    }

#ifdef _DEBUG
    glfwSetErrorCallback(GLFWErrorHandler);
#endif // _DEBUG

    /* We don't want the shared context window visible */
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

    /* Create our shared context window */
    Window::SharedContext = glfwCreateWindow(16, 16, "", NULL, NULL);
    if(Window::SharedContext == NULL) {
        printf("Error creating shared context\n");
        return BGE_FAILURE;
    }

    /* Need to make context current so we can init the shader library */
    glfwMakeContextCurrent(Window::SharedContext);

    /* So future GLFW windows are visible */
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        printf("Error initializing GLEW\n");
        return BGE_FAILURE;
    }

    // Check for required OpenGL extensions to run Bakge
    if(!CheckRequiredExtensions()) {
        return BGE_FAILURE;
    }

    /* Run platform-specific initialization protocol */
    if(PlatformInit(argc, argv) != BGE_SUCCESS)
        return BGE_FAILURE;

    /* Initialize our Bakge shader library */
    if(Shader::InitShaderLibrary() != BGE_SUCCESS)
        return BGE_FAILURE;

    printf("Bakersfield Game Engine v%d.%d.%d\n", BGE_VER_MAJ, BGE_VER_MIN,
                                                                BGE_VER_REV);

    SystemInfo();

    return BGE_SUCCESS;
}


Result Deinit()
{
    PHYSFS_deinit();

    if(PHYSFS_close(LogFile) == 0) {
        printf("Error closing log file\n");
    }

    /* Run platform-specific deinitialization protocol */
    PlatformDeinit();

    Shader::DeinitShaderLibrary();

    /* Destroy our shared context window */
    glfwDestroyWindow(Window::SharedContext);

    glfwTerminate();

    return BGE_SUCCESS;
}


void SystemInfo()
{
    extern void PlatformSystemInfo();

    PlatformSystemInfo();

    printf("OpenGL v%s\n", glGetString(GL_VERSION));
    printf("GLSL v%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}


int Log(const char* Format, ...)
{
    int i;
    va_list ArgList;

    va_start(ArgList, Format);
    i = vprintf(Format, ArgList);
    va_end(ArgList);

    return i;
}

} /* bakge */

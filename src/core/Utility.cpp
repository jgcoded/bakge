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

    /* Check if required extensions are supported */
    if(!glewIsSupported(VERTEX_BUFFER_OBJECT_EXT)) {
        printf("Extension %s required.\n", VERTEX_BUFFER_OBJECT_EXT);
        return BGE_FAILURE;
    }

    /* Run platform-specific initialization protocol */
    if(PlatformInit(argc, argv) != BGE_SUCCESS)
        return BGE_FAILURE;

    /* Initialize our Bakge shader library */
    if(ShaderProgram::InitShaderLibrary() != BGE_SUCCESS)
        return BGE_FAILURE;

    printf("Bakersfield Game Engine v%d.%d.%d\n", BGE_VER_MAJ, BGE_VER_MIN,
                                                                BGE_VER_REV);

    SystemInfo();

    return BGE_SUCCESS;
}


Result Deinit()
{
    extern Result PlatformDeinit();

    /* Run platform-specific deinitialization protocol */
    PlatformDeinit();

    ShaderProgram::DeinitShaderLibrary();

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

} /* bakge */

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

void Window::WindowMoved(GLFWwindow* Handle,  int X, int Y)
{
}


void Window::WindowResized(GLFWwindow* Handle, int Width, int Height)
{
}


void Window::WindowClosed(GLFWwindow* Handle)
{
    Window* BakgeWindow = (Window*)glfwGetWindowUserPointer(Handle);
    BakgeWindow->Close();
}


Window::Window()
{
    WindowHandle = NULL;
}


Window::~Window()
{
    Close();
}


Window* Window::Create(int Width, int Height)
{
    Window* Win = new Window;

    Win->WindowHandle = glfwCreateWindow(Width, Height, "Bakge", NULL, NULL);
    if(Win->WindowHandle == NULL) {
        delete Win;
        return NULL;
    }

    /* Store pointer to Bakge window so global callbacks can access it */
    glfwSetWindowUserPointer(Win->WindowHandle, (void*)Win);

    glfwSetWindowCloseCallback(Win->WindowHandle, WindowClosed);
    glfwSetWindowSizeCallback(Win->WindowHandle, WindowResized);
    glfwSetWindowPosCallback(Win->WindowHandle, WindowMoved);

    Win->Bind();

    return Win;
}


Result Window::SwapBuffers()
{
    glfwSwapBuffers(WindowHandle);
    return BGE_SUCCESS;
}


Result Window::Bind() const
{
    glfwMakeContextCurrent(WindowHandle);
    return BGE_SUCCESS;
}


Result Window::Unbind() const
{
    glfwMakeContextCurrent(NULL);
    return BGE_SUCCESS;
}


Result Window::Close()
{
    if(IsOpen()) {
        /* Destroy the GLFW window */
        GLFWwindow* Handle = WindowHandle;
        WindowHandle = NULL;
        glfwDestroyWindow(Handle);

        return BGE_SUCCESS;
    } else {
        return BGE_FAILURE;
    }
}


bool Window::IsOpen()
{
    return WindowHandle != NULL && !glfwWindowShouldClose(WindowHandle);
}


Result Window::PollEvent(Event* Ev)
{
    glfwPollEvents();
    return BGE_FAILURE;
}

} /* bakge */

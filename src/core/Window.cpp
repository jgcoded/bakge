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

void Window::Moved(GLFWwindow* Handle,  int X, int Y)
{
    Window* Win;
    EventHandler* Handler;

    Win = (Window*)glfwGetWindowUserPointer(Handle);
    Handler = Win->Handler;

    if(Handler != NULL) {
        /* Deploy event here */
    }
}


void Window::Resized(GLFWwindow* Handle, int Width, int Height)
{
    Window* Win;
    EventHandler* Handler;

    Win = (Window*)glfwGetWindowUserPointer(Handle);
    Handler = Win->Handler;

    if(Handler != NULL) {
        /* Deploy event here */
    }
}


void Window::Closed(GLFWwindow* Handle)
{
    Window* Win;
    EventHandler* Handler;

    Win = (Window*)glfwGetWindowUserPointer(Handle);
    Handler = Win->Handler;

    /* Deploy closed event before closing the window */
    if(Handler != NULL) {
        /* Deploy event here */
    }

    Win->Close();
}


void Window::Key(GLFWwindow* Handle, int Key, int Code, int Pressed, int Mod)
{
    Window* Win;
    EventHandler* Handler;

    Win = (Window*)glfwGetWindowUserPointer(Handle);
    Handler = Win->Handler;

    if(Handler != NULL) {
        /* Deploy event here */
    }
}


void Window::Mouse(GLFWwindow* Handle, int Button, int Pressed, int Mod)
{
    Window* Win;
    EventHandler* Handler;

    Win = (Window*)glfwGetWindowUserPointer(Handle);
    Handler = Win->Handler;

    if(Handler != NULL) {
        /* Ok to pass int, ButtonID, ModField etc are just typedef int */
        Handler->MouseEvent(Button, Pressed, Mod);
    }
}


void Window::MouseMotion(GLFWwindow* Handle, double X, double Y)
{
    Window* Win;
    EventHandler* Handler;

    Win = (Window*)glfwGetWindowUserPointer(Handle);
    Handler = Win->Handler;

    if(Handler != NULL) {
        /* Floor values, we want integral arguments */
        Handler->MotionEvent(floor(X), floor(Y));
    }
}


void Window::Scroll(GLFWwindow* Handle, double X, double Y)
{
    Window* Win;
    EventHandler* Handler;

    Win = (Window*)glfwGetWindowUserPointer(Handle);
    Handler = Win->Handler;

    if(Handler != NULL) {
        /* Floor values, we want integral arguments */
        Handler->ScrollEvent(floor(X), floor(Y));
    }
}


Window::Window()
{
    WindowHandle = NULL;
    Handler = NULL;
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

    glfwSetWindowCloseCallback(Win->WindowHandle, Window::Closed);
    glfwSetWindowSizeCallback(Win->WindowHandle, Window::Resized);
    glfwSetWindowPosCallback(Win->WindowHandle, Window::Moved);
    glfwSetKeyCallback(Win->WindowHandle, Window::Key);
    glfwSetMouseButtonCallback(Win->WindowHandle, Window::Mouse);
    glfwSetCursorPosCallback(Win->WindowHandle, Window::MouseMotion);
    glfwSetScrollCallback(Win->WindowHandle, Window::Scroll);

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


EventHandler* Window::SetEventHandler(EventHandler* Who)
{
    EventHandler* Previous;

    Previous = Handler;
    Handler = Who;

    return Previous;
}

} /* bakge */

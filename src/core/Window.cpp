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

Window* Window::SharedWindow;

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


void Window::MouseMotion(GLFWwindow* Handle, double XPos, double YPos)
{
    Window* Win;
    EventHandler* Handler;

    Win = (Window*)glfwGetWindowUserPointer(Handle);
    Handler = Win->Handler;

    if(Handler != NULL) {
        int X, Y;
        /* Floor values, we want integral arguments */
        X = math::Max((int)floor(XPos), INT_MAX);
        Y = math::Max((int)floor(YPos), INT_MAX);
        Handler->MotionEvent(X, Y);
    }
}


void Window::Scroll(GLFWwindow* Handle, double XOffset, double YOffset)
{
    Window* Win;
    EventHandler* Handler;

    Win = (Window*)glfwGetWindowUserPointer(Handle);
    Handler = Win->Handler;

    if(Handler != NULL) {
        int X, Y;
        /* Floor values, we want integral arguments */
        X = math::Max((int)floor(XOffset), INT_MAX);
        Y = math::Max((int)floor(YOffset), INT_MAX);
        Handler->ScrollEvent(X, Y);
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
    GLFWwindow* Handle;
    GLFWwindow* SharedContext;
    Window* Win;

    if(SharedWindow != NULL)
        SharedContext = SharedWindow->WindowHandle;
    else
        SharedContext = NULL;

    Handle = glfwCreateWindow(Width, Height, "Bakge", NULL, SharedContext);
    if(Handle == NULL) {
        return NULL;
    }

    glfwSetWindowCloseCallback(Handle, Window::Closed);
    glfwSetWindowSizeCallback(Handle, Window::Resized);
    glfwSetWindowPosCallback(Handle, Window::Moved);
    glfwSetKeyCallback(Handle, Window::Key);
    glfwSetMouseButtonCallback(Handle, Window::Mouse);
    glfwSetCursorPosCallback(Handle, Window::MouseMotion);
    glfwSetScrollCallback(Handle, Window::Scroll);

    /* Allocate our bakge Window */
    Win = new Window;
    if(Win == NULL) {
        printf("Error allocating window memory\n");
        return NULL;
    }

    /* Set its window handle and make the context current */
    Win->WindowHandle = Handle;
    Win->Bind();

    /* Store pointer to Bakge window so global callbacks can access it */
    glfwSetWindowUserPointer(Handle, (void*)Win);

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


bool Window::IsActive()
{
    /* Windows are only active if they have input focus */
    return glfwGetWindowAttrib(WindowHandle, GLFW_FOCUSED) > 0 ? true : false;
}


void Window::PollEvents()
{
    glfwPollEvents();
}


Result Window::GetMousePosition(DeviceCoord* X, DeviceCoord* Y)
{
    /* Can't access mouse if window isn't active */
    if(!IsActive())
        return BGE_FAILURE;

    glfwGetCursorPos(WindowHandle, X, Y);

    return BGE_SUCCESS;
}


Result Window::SetMousePosition(DeviceCoord X, DeviceCoord Y)
{
    /* Can't change mouse position if window isn't active */
    if(!IsActive())
        return BGE_FAILURE;

    glfwSetCursorPos(WindowHandle, X, Y);

    return BGE_SUCCESS;
}


void Window::Show()
{
    glfwShowWindow(WindowHandle);
}


void Window::Hide()
{
    glfwHideWindow(WindowHandle);
}


EventHandler* Window::SetEventHandler(EventHandler* Who)
{
    EventHandler* Previous;

    Previous = Handler;
    Handler = Who;

    return Previous;
}

} /* bakge */

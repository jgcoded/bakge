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

#ifndef BAKGE_CORE_WINDOW_H
#define BAKGE_CORE_WINDOW_H

#include <bakge/Bakge.h>

namespace bakge
{

#define GLFWCALLBACK static

class Window : public Bindable
{
    friend Result Init(int argc, char* argv[]);

    /* GLFW callbacks. Private for protection against bogus events */
    GLFWCALLBACK void Moved(GLFWwindow*,  int, int);
    GLFWCALLBACK void Resized(GLFWwindow*, int, int);
    GLFWCALLBACK void Closed(GLFWwindow*);
    GLFWCALLBACK void Key(GLFWwindow*, int, int, int, int);
    GLFWCALLBACK void Mouse(GLFWwindow*, int, int, int);
    GLFWCALLBACK void MouseMotion(GLFWwindow*, double, double);
    GLFWCALLBACK void Scroll(GLFWwindow*, double, double);

    GLFWwindow* WindowHandle;

    /* Who receives events from the window? */
    EventHandler* Handler;

    Window();


public:

    ~Window();

    BGE_FACTORY Window* Create(int Width, int Height);

    /* Call manually to process events for all windows */
    static void PollEvents();

    bool IsOpen();
    bool IsActive();

    Result Close();

    Result SwapBuffers();

    /* Binding makes this window's context current on the calling thread */
    Result Bind() const;
    Result Unbind() const;

    EventHandler* SetEventHandler(EventHandler* Who);

    Result GetMousePosition(DeviceCoord* X, DeviceCoord* Y);
    Result SetMousePosition(DeviceCoord X, DeviceCoord Y);

    /* *
     * Hide and Show can fail if window is already hidden/shown,
     * but will do so silently
     * */
    void Hide();
    void Show();

}; /* Window */

} /* bakge */

#endif /* BAKGE_CORE_WINDOW_H */

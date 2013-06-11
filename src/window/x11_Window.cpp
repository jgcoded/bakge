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

Display* x11_Window::XDisplay = NULL;
XVisualInfo* x11_Window::XVisual = NULL;
GLXContext x11_Window::Context = None;
Colormap x11_Window::ColorMap = None;
Atom x11_Window::CloseProtocol;

x11_Window::x11_Window()
{
    XWindow = None;
}


x11_Window::~x11_Window()
{
    Close();
}


x11_Window* x11_Window::Create(int Width, int Height)
{

    if(XDisplay == NULL) {
        printf("No connection to X server\n");
        return NULL;
    }

    x11_Window* Win = new x11_Window();
    /* TODO Assert Win != NULL */

    return Win;
}


Result x11_Window::Close()
{
    /* Prevent closing a window that isn't open */
    if(XWindow != None) {
        /* Close the window */
        XDestroyWindow(XDisplay, XWindow);
        XWindow = None;
    }

    return BGE_FAILURE;
}

} /* bakge */

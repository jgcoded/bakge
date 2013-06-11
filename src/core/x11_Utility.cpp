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
    /* Visual info settings */
    int DoubleBuffer[] = { GLX_RGBA, GLX_DEPTH_SIZE, 16, None };
    int Dummy;

    /* Connect to X server */
    x11_Window::XDisplay = XOpenDisplay(NULL);
    if(x11_Window::XDisplay == NULL) {
        printf("Unable to connect to X server\n");
        return BGE_FAILURE;
    }

    /* Check if X server has GLX extension */
    if(glXQueryExtension(x11_Window::XDisplay, &Dummy, &Dummy) == False) {
        printf("X server has no GLX extension\n");
        return BGE_FAILURE;
    }

    /* Get visual mode */
    x11_Window::XVisual = glXChooseVisual(x11_Window::XDisplay, DefaultScreen
                                       (x11_Window::XDisplay), DoubleBuffer);
    if(x11_Window::XVisual == NULL) {
        printf("Unable to find RGBA display with depth buffer\n");
        return BGE_FAILURE;
    }

    /* Create OpenGL context for our window(s) */
    x11_Window::Context = glXCreateContext(x11_Window::XDisplay,
                               x11_Window::XVisual, None, GL_TRUE);
    if(x11_Window::Context == NULL) {
        printf("Unable to create OpenGL context\n");
        return BGE_FAILURE;
    }

    /* Create a colormap */
    x11_Window::ColorMap = XCreateColormap(x11_Window::XDisplay,
                              RootWindow(x11_Window::XDisplay, 
                              x11_Window::XVisual->screen),
                              x11_Window::XVisual->visual, AllocNone);
    if(x11_Window::ColorMap == None) {
        printf("Unable to create colormap attachment\n");
        return BGE_FAILURE;
    }

    /* Create window close event atom */
    x11_Window::CloseProtocol = XInternAtom(x11_Window::XDisplay,
                                        "WM_DELETE_WINDOW", True);

    return BGE_FAILURE;
}


Result Deinit()
{
    /* Free colormap */
    if(x11_Window::ColorMap != None) {
        XFreeColormap(x11_Window::XDisplay, x11_Window::ColorMap);
        x11_Window::ColorMap = None;
    }

    /* Free OpenGL Context */
    if(x11_Window::Context != None) {
        glXMakeCurrent(x11_Window::XDisplay, None, NULL);
        glXDestroyContext(x11_Window::XDisplay, x11_Window::Context);
        x11_Window::Context = None;
    }

    /* Free visual info */
    if(x11_Window::XVisual != NULL) {
        XFree((void*)x11_Window::XVisual);
        x11_Window::XVisual = NULL;
    }

    /* Close X server connection */
    if(x11_Window::XDisplay != NULL) {
        XCloseDisplay(x11_Window::XDisplay);
    }

    return BGE_FAILURE;
}

} /* bakge */

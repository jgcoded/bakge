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

#define ALL_X11_EVENTS (\
    KeyPressMask                |\
    KeyReleaseMask              |\
    ButtonPressMask             |\
    ButtonReleaseMask           |\
    EnterWindowMask             |\
    LeaveWindowMask             |\
    PointerMotionMask           |\
    PointerMotionHintMask       |\
    Button1MotionMask           |\
    Button2MotionMask           |\
    Button3MotionMask           |\
    Button4MotionMask           |\
    Button5MotionMask           |\
    ButtonMotionMask            |\
    KeymapStateMask             |\
    ExposureMask                |\
    VisibilityChangeMask        |\
    StructureNotifyMask         |\
    ResizeRedirectMask          |\
    SubstructureNotifyMask      |\
    SubstructureRedirectMask    |\
    FocusChangeMask             |\
    PropertyChangeMask          |\
    ColormapChangeMask          |\
    OwnerGrabButtonMask         \
    )

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

    Win->XAttrib.colormap = ColorMap;
    Win->XAttrib.border_pixel = 0;
    Win->XAttrib.event_mask = ALL_X11_EVENTS;

    Win->XWindow = XCreateWindow(XDisplay, RootWindow(XDisplay,
                                    XVisual->screen), 0, 0, Width,
                                    Height, 0, XVisual->depth,
                                    InputOutput, XVisual->visual,
                                    CWBorderPixel | CWColormap | CWEventMask,
                                    &(Win->XAttrib));
    if(Win->XWindow == None) {
        printf("Unable to create window\n");
        delete Win;
        return NULL;
    }

    /* Set OpenGL context as current for this window */
    if(glXMakeCurrent(XDisplay, Win->XWindow, Context) == False) {
        printf("Unable to make OpenGL context current\n");
        delete Win;
        return NULL;
    }

    XSetStandardProperties(XDisplay, Win->XWindow, "Bakge", "Bakge", None,
                                                         NULL, 0, NULL);

    XMapWindow(XDisplay, Win->XWindow);
    XFlush(XDisplay);

    XSetWMProtocols(XDisplay, Win->XWindow, &CloseProtocol, 1);

    return Win;
}


bool x11_Window::IsOpen()
{
    return (XWindow != None) ? true : false;
}


Result x11_Window::Close()
{
    /* Prevent closing a window that isn't open */
    if(IsOpen()) {
        /* Close the window */
        XDestroyWindow(XDisplay, XWindow);
        XWindow = None;
    }

    return BGE_FAILURE;
}


Result x11_Window::PollEvent(Event* Ev)
{
    static XEvent XEv;

    Bool HasEvent;

    if(!IsOpen())
        return BGE_FAILURE;

    /* If no events in the queue, no need to poll */
    if(XPending(XDisplay) == 0) {
        return BGE_FAILURE;
    }

    XNextEvent(XDisplay, &XEv);

    /* If not for this window, send it back to queue */
    if(XEv.xany.window != XWindow) {
        XSendEvent(XDisplay, XEv.xany.window, False, ALL_X11_EVENTS, &XEv);
        return BGE_FAILURE;
    }

    /* *
     * Else it is for this window, clear the Bakge event and translate
     * the X11 event
     * */
    Ev->Clear();

    switch(XEv.type) {
    case ClientMessage:
        if(XEv.xclient.data.l[0] == (long)CloseProtocol)
            Ev->Type = -1;
        break;
    }

    return BGE_SUCCESS;
}


Result x11_Window::SwapBuffers()
{
    glXSwapBuffers(XDisplay, XWindow);
    return BGE_SUCCESS;
}

} /* bakge */

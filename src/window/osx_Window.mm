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

NSOpenGLContext* osx_Window::SharedContext;
NSOpenGLPixelFormat* osx_Window::PixelFormat;

osx_Window::osx_Window()
{
    GLView = NULL;
}


osx_Window::~osx_Window()
{
    Close();
}


osx_Window* osx_Window::Create(int Width, int Height)
{
    osx_Window* Win;
    NSOpenGLContext* Context;
    NSRect Frame;

    /* Allocate a window */
    Win = new osx_Window;

    Frame.origin.x = 50.0f;
    Frame.origin.y = 50.0f;
    Frame.size.width = Width;
    Frame.size.height = Height;

    /* Create our OpenGL view */
    Win->GLView = [[NSOpenGLView alloc] initWithFrame: Frame
                                        pixelFormat: PixelFormat];

    if(Win->GLView == NULL) {
        printf("Error creating OpenGL view\n");
        delete Win;
        return NULL;
    }

    /* Allocate a OpenGL context sharing our SharedContext */
    Win->Context = [[NSOpenGLContext alloc] initWithFormat: PixelFormat
                                            shareContext: SharedContext];

    if(Win->Context == NULL) {
        printf("Error creating OpenGL context\n");
        delete Win;
        return NULL;
    }

    /* Set our view's context & set our context's view */
    [Win->GLView setOpenGLContext: Win->Context];
    [Win->Context setView: Win->GLView];

    /* Make our window's context current on this thread */
    [Win->Context makeCurrentContext];

    [Win->Context clearDrawable];

    return Win;
}


bool osx_Window::IsOpen()
{
    return GLView != NULL;
}


Result osx_Window::Close()
{
    if(IsOpen()) {

        [GLView release];
        GLView = NULL;

    }

    return BGE_FAILURE;
}


Result osx_Window::SwapBuffers()
{
    [Context flushBuffer];
    return BGE_SUCCESS;
}


Result osx_Window::PollEvent(Event* Ev)
{
    return BGE_FAILURE;
}

} /* bakge */

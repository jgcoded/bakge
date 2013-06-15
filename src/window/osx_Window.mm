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

@implementation BakgeOpenGLView

- (void) prepareOpenGL
{
}


- (void) drawRect: (NSRect) bounds
{
    printf("DrawRect\n");
}


- (void) reshape
{
}


- (BOOL) acceptsFirstResponder
{
    return YES;
}

@end

namespace bakge
{

NSOpenGLPixelFormat* osx_Window::PixelFormat;
NSOpenGLContext* osx_Window::SharedContext;

osx_Window::osx_Window()
{
    WindowHandle = NULL;
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
    NSView* WindowView;

    /* Allocate a window */
    Win = new osx_Window;

    Win->WindowHandle = [[NSWindow alloc] initWithContentRect:
                                            NSMakeRect(0, 0, Width, Height)
                                          styleMask:
                                            NSTitledWindowMask | 
                                            NSClosableWindowMask | 
                                            NSMiniaturizableWindowMask 
                                          backing: NSBackingStoreBuffered 
                                          defer: NO]; 

    [Win->WindowHandle makeKeyAndOrderFront: nil];
    [Win->WindowHandle setTitle: @"Bakge"];

    Frame.origin.x = 50.0f;
    Frame.origin.y = 50.0f;
    Frame.size.width = Width;
    Frame.size.height = Height;

    /* Create our OpenGL view */
    Win->GLView = [[BakgeOpenGLView alloc] initWithFrame: Frame
                                        pixelFormat: PixelFormat];

    if(Win->GLView == NULL) {
        printf("Error creating OpenGL view\n");
        delete Win;
        return NULL;
    }

    printf("Creating window's context\n");

    Win->Context = [Win->GLView openGLContext];

    GLint SwapInterval, Opaque;
    SwapInterval = 1;
    Opaque = 0;
    [Win->Context setValues: &SwapInterval forParameter: NSOpenGLCPSwapInterval];
    [Win->Context setValues: &Opaque forParameter: NSOpenGLCPSurfaceOpacity];

    printf("Making context current\n");
    [Win->Context makeCurrentContext];

    WindowView = [Win->WindowHandle contentView];
    [WindowView addSubview: Win->GLView];

    return Win;
}


bool osx_Window::IsOpen()
{
    return WindowHandle != NULL;
}


Result osx_Window::Close()
{
    if(IsOpen()) {
        /* Release NS window */
        [WindowHandle release];
        WindowHandle = NULL;

        return BGE_SUCCESS;
    } else {
        return BGE_FAILURE;
    }
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


Result osx_Window::Bind() const
{
    return BGE_SUCCESS;
}


Result osx_Window::Unbind() const
{
    [GLView setNeedsDisplay: YES];
    return BGE_SUCCESS;
}

} /* bakge */

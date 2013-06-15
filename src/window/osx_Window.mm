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

@implementation BakgeApplicationDelegate

- (NSApplicationTerminateReply) applicationShouldTerminate:
                                    (NSApplication*) Sender
{
    printf("Termination sent to application\n");
    return NSTerminateCancel;
}

@end


@implementation BakgeWindowDelegate

- (BOOL) windowShouldClose: (id) Sender
{
    printf("Window closing\n");
    return YES;
}


- (void) windowDidResize: (NSNotification*) Notification
{
    printf("Resized\n");
}

@end


@implementation BakgeContentView

- (id) init
{
    self = [super init];
    return self;
}

@end


@implementation BakgeWindow

- (BOOL) canBecomeKeyWindow
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

    Win->WindowHandle = [[BakgeWindow alloc] initWithContentRect:
                                            NSMakeRect(0, 0, Width, Height)
                                          styleMask:
                                            NSTitledWindowMask | 
                                            NSClosableWindowMask | 
                                            NSResizableWindowMask | 
                                            NSMiniaturizableWindowMask 
                                          backing: NSBackingStoreBuffered 
                                          defer: NO]; 

    [Win->WindowHandle makeKeyAndOrderFront: nil];
    [Win->WindowHandle setTitle: @"Bakge"];

    Win->WindowDelegate = [[BakgeWindowDelegate alloc] init];
    if(Win->WindowDelegate == NULL) {
        printf("Error creating window delegate\n");
        delete Win;
        return NULL;
    }
    [Win->WindowHandle setDelegate: Win->WindowDelegate];

    Frame.origin.x = 0;
    Frame.origin.y = 0;
    Frame.size.width = Width;
    Frame.size.height = Height;

    printf("Creating window's content view\n");
    Win->ContentView = [[BakgeContentView alloc] init];
    if(Win->ContentView == NULL) {
        printf("Error creating window content view\n");
        delete Win;
        return NULL;
    }

    GLint SwapInterval, Opaque;
    SwapInterval = 1;
    Opaque = 0;
    [Win->Context setValues: &SwapInterval forParameter: NSOpenGLCPSwapInterval];
    [Win->Context setValues: &Opaque forParameter: NSOpenGLCPSurfaceOpacity];
    [Win->Context setView: Win->ContentView];

    [Win->WindowHandle setContentView: Win->ContentView];

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
    [Context update];
    return BGE_SUCCESS;
}


Result osx_Window::Unbind() const
{
    return BGE_SUCCESS;
}

} /* bakge */


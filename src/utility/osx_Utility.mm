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

BakgeApplicationDelegate* AppDelegate;
NSAutoreleasePool* NSPool;
NSDate* StartTime;

Result Init(int argc, char* argv[])
{
    NSMenu* MenuBar;
    NSMenuItem* MenuItem;
    /* Attributes for our OpenGL pixel format */
    NSOpenGLPixelFormatAttribute FormatAttribs[] = {
        NSOpenGLPFAWindow,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        0
    };

    NSPool = [[NSAutoreleasePool alloc] init];

    /* Set start date of app */
    StartTime = [NSDate date];

    [NSApplication sharedApplication];

    /* Menu bar */
    MenuBar = [[NSMenu alloc] init];
    [NSApp setMainMenu: MenuBar];

    [NSApp performSelector: @selector(setAppleMenu:) withObject: MenuBar];

    [NSApp finishLaunching];

    AppDelegate = [[BakgeApplicationDelegate alloc] init];

    [NSApp setDelegate: AppDelegate];

    /* Get start date of application */
    StartTime = [NSDate date];

    printf("Creating OpenGL pixel format\n");

    /* Create our pixel format */
    osx_Window::PixelFormat = [[NSOpenGLPixelFormat alloc]
                              initWithAttributes: FormatAttribs];

    printf("Setting shared context\n");

    /* Create our OpenGL context */
    osx_Window::SharedContext = [[NSOpenGLContext alloc] initWithFormat:
                             osx_Window::PixelFormat shareContext: nil];

    return BGE_SUCCESS;
}


Result Deinit()
{
    /* Release pixel format and OpenGL context */
    [osx_Window::PixelFormat release];
    [osx_Window::SharedContext release];

    [NSPool release];

    return BGE_SUCCESS;
}

} /* bakge */


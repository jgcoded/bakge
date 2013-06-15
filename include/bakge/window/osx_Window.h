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

#ifndef BAKGE_WINDOW_OSX_WINDOW_H
#define BAKGE_WINDOW_OSX_WINDOW_H

#include <bakge/Bakge.h>

/* Our OpenGL view class */
@interface BakgeOpenGLView : NSOpenGLView
@end

namespace bakge
{

typedef class osx_Window : api::Window
{
    friend Result Init(int argc, char* argv[]);
    friend Result Deinit();

    __strong NSWindow* WindowHandle;

    static NSOpenGLContext* SharedContext;
    static NSOpenGLPixelFormat* PixelFormat;

    NSOpenGLView* GLView;
    NSOpenGLContext* Context;

    osx_Window();


public:

    ~osx_Window();

    BGE_FACTORY osx_Window* Create(int Width, int Height);

    Result Bind() const;
    Result Unbind() const;

    bool IsOpen();
    Result Close();
    Result SwapBuffers();
    Result PollEvent(Event* Ev);

} Window; /* osx_Window */

} /* bakge */

#endif /* BAKGE_WINDOW_OSX_WINDOW_H */

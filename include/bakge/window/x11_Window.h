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

#ifndef BAKGE_WINDOW_X11_WINDOW_H
#define BAKGE_WINDOW_X11_WINDOW_H

#include <bakge/Bakge.h>

namespace bakge
{

typedef class x11_Window
{
    friend Result Init(int argc, char* argv[]);
    friend Result Deinit();

    static Display* XDisplay;
    static XVisualInfo* XVisual;
    static GLXContext Context;
    static Colormap ColorMap;
    static Atom CloseProtocol;

    x11_Window();


public:

    ~x11_Window();

    BGE_FACTORY x11_Window* Create(int Width, int Height);

    bool IsOpen();

    Result Close();

    Result PollEvent(Event* Ev);

    Result SwapBuffers();


private:

    ::Window XWindow;
    XSetWindowAttributes XAttrib;


} Window; /* x11_Window */

} /* bakge */

#endif /* BAKGE_WINDOW_X11_WINDOW_H */

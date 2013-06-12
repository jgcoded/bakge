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

#ifndef BAKGE_WINDOW_WIN32_WINDOW_H
#define BAKGE_WINDOW_WIN32_WINDOW_H

#include <bakge/Bakge.h>

namespace bakge
{

typedef class win32_Window
{
    friend Result Init(int argc, char* argv[]);
    friend Result Deinit();

    static HINSTANCE Instance;
    static WNDCLASSEX WindowClass;
    static HDC Device; /* Device context */
    static HGLRC Context; /* OpenGL context */
    static PIXELFORMATDESCRIPTOR PixFormat;
    static int Format;
    
    static LRESULT CALLBACK WindowProcCallback(HWND, UINT, WPARAM, LPARAM);

    win32_Window();


public:

    ~win32_Window();
    
    BGE_FACTORY win32_Window* Create(int Width, int Height);

    bool IsOpen();

    Result Close();
    
    Result PollEvent(Event* Ev);

    Result SwapBuffers();


protected:

    HWND Window;
    HGLRC LocalContext;

} Window; /* win32_Window */

} /* bakge */

#endif /* BAKGE_WINDOW_WIN32_WINDOW_H */

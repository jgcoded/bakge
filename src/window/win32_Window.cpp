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

HINSTANCE win32_Window::Instance;
WNDCLASSEX win32_Window::WindowClass;
HDC win32_Window::Device;
HGLRC win32_Window::Context;
PIXELFORMATDESCRIPTOR win32_Window::PixFormat;
int win32_Window::Format;

LRESULT CALLBACK
win32_Window::WindowProcCallback(HWND Win, UINT Msg, WPARAM W, LPARAM L)
{
    if(Msg == WM_CLOSE) {
        PostMessage(Win, Msg, W, L);
        return 0;
    }
    
    return DefWindowProc(Win, Msg, W, L);
}


win32_Window::win32_Window()
{
    Window = 0;
    LocalContext = 0;
}


win32_Window::~win32_Window()
{
    Close();
}


win32_Window* win32_Window::Create(int Width, int Height)
{
    /* Make sure init was called and succeeded */
    if(WindowClass.cbSize == 0) {
        printf("Unable to create window\n");
        return NULL;
    }
    
    /* Allocate window memory */
    win32_Window* Win = new win32_Window;
    if(Win == NULL) {
        printf("Error allocating window\n");
        return NULL;
    }
    
    /* Create the window */
    Win->Window = CreateWindowEx(0, WindowClass.lpszClassName, "Bakge",
                            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                            CW_USEDEFAULT, Width, Height, NULL, NULL,
                            Instance, NULL);
    if(Win->Window == 0) {
        printf("Error creating window\n");
        delete Win;
        return NULL;
    }

    /* Set this window's device pixel format */
    if(!SetPixelFormat(GetDC(Win->Window), Format, &PixFormat)) {
        printf("Unable to set window's pixel format\n");
        delete Win;
        return NULL;
    }

    /* Create a local context for this window */
    Win->LocalContext = wglCreateContext(GetDC(Win->Window));
    if(Win->LocalContext == 0) {
        printf("Error creating window's OpenGL context\n");
        delete Win;
        return NULL;
    }

    /* Connect to the shared context */
    wglShareLists(Context, Win->LocalContext);
    if(!wglMakeCurrent(GetDC(Win->Window), Win->LocalContext)) {
        printf("Error making window context current\n");
        delete Win;
        return NULL;
    }
    
    /* Display our window */
    ShowWindow(Win->Window, SW_SHOWDEFAULT);

    return Win;
}


Result win32_Window::PollEvent(Event* Ev)
{
    static MSG Msg;
    
    if(!PeekMessage(&Msg, Window, 0, 0, PM_REMOVE)) {
        return BGE_FAILURE;
    }
    
    Ev->Clear();
    
    switch(Msg.message) {

    case WM_CLOSE:
        Ev->Type = -1;
        break;

    default:
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    
    return BGE_SUCCESS;
}


bool win32_Window::IsOpen()
{
    return Window != 0 ? true : false;
}


Result win32_Window::Close()
{
    if(IsOpen()) {
        if(Window != 0) {
            DestroyWindow(Window);
            Window = 0;
        }
    }

    return BGE_SUCCESS;
}


Result win32_Window::SwapBuffers()
{
    return ::SwapBuffers(GetDC(Window)) ? BGE_SUCCESS : BGE_FAILURE;
}

} /* bakge */

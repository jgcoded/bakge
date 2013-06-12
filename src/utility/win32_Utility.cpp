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

#define BAKGE_WINDOW_CLASS_NAME "BakgeWinClass"

Result Init(int argc, char* argv[])
{
    win32_Window::Instance = GetModuleHandle(0);
    
    /* Convenience */
    WNDCLASSEX* WinClass = &(win32_Window::WindowClass);
    WinClass->cbSize = sizeof(WNDCLASSEX);
    WinClass->style = CS_OWNDC;
    WinClass->lpfnWndProc = win32_Window::WindowProcCallback;
    WinClass->cbClsExtra = 0;
    WinClass->cbWndExtra = 0;
    WinClass->hInstance = win32_Window::Instance;
    WinClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WinClass->hCursor = LoadCursor(NULL, IDC_ARROW);
    WinClass->hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WinClass->lpszMenuName = NULL;
    WinClass->lpszClassName = BAKGE_WINDOW_CLASS_NAME;
    WinClass->hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    if(RegisterClassEx(WinClass) == 0) {
        printf("Unable to register window class\n");
        return BGE_FAILURE;
    }
    
    win32_Window::Device = GetDC(NULL);
    if(win32_Window::Device == NULL) {
        printf("Unable to get device context\n");
        return BGE_FAILURE;
    }
    
    PIXELFORMATDESCRIPTOR* PixFormat = &(win32_Window::PixFormat);
    ZeroMemory(PixFormat, sizeof(*PixFormat));
    PixFormat->nSize = sizeof(*PixFormat);
    PixFormat->nVersion = 1;
    PixFormat->iPixelType = PFD_TYPE_RGBA;
    PixFormat->cColorBits = 24;
    PixFormat->cDepthBits = 16;
    PixFormat->iLayerType = PFD_MAIN_PLANE;
    PixFormat->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                                                    PFD_DOUBLEBUFFER;
    /* Choose a pixel format for our device */
    win32_Window::Format = ChoosePixelFormat(win32_Window::Device, PixFormat);
    if(win32_Window::Format == 0) {
        printf("Unable to choose pixel format\n");
        return BGE_FAILURE;
    }
    
    SetPixelFormat(win32_Window::Device, win32_Window::Format, PixFormat);
    
    /* Create our OpenGL context */
    win32_Window::Context = wglCreateContext(win32_Window::Device);
    if(win32_Window::Context == 0) {
        printf("Error creating OpenGL context\n");
        return BGE_FAILURE;
    }

    return BGE_SUCCESS;
}


Result Deinit()
{
    /* Delete OpenGL context */
    if(win32_Window::Context != 0) {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(win32_Window::Context);
        win32_Window::Context = 0;
    }
    
    if(win32_Window::WindowClass.cbSize > 0)
        UnregisterClass(BAKGE_WINDOW_CLASS_NAME, win32_Window::Instance);

    ReleaseDC(NULL, win32_Window::Device);
    
    return BGE_FAILURE;
}

} /* bakge */

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

LARGE_INTEGER ClockFreq;
LARGE_INTEGER StartCount;

Result Init(int argc, char* argv[])
{
    HANDLE CurrentThread;
    DWORD_PTR OldThreadMask;

    if(!glfwInit()) {
        printf("Unable to initialize GLFW 3.0\n");
        return BGE_FAILURE;
    }

    /* Grab current thread handle */
    CurrentThread = GetCurrentThread();

    /* Run clock stuff on processor 1 only */
    OldThreadMask = SetThreadAffinityMask(CurrentThread, 1);

    /* Get PerformanceCounter frequency and start tick count */
    QueryPerformanceFrequency(&ClockFreq);
    QueryPerformanceCounter(&StartCount);

    /* Reset thread affinity mask for this thread */
    SetThreadAffinityMask(CurrentThread, OldThreadMask);

    return BGE_SUCCESS;
}


Result Deinit()
{
    glfwTerminate();

    return BGE_FAILURE;
}

} /* bakge */

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

Result Delay(Microseconds BGE_NCP Time)
{
    Microseconds End = Time + GetRunningTime();

    while(GetRunningTime() < End)
        ;

    return BGE_SUCCESS;
}


Microseconds GetRunningTime()
{
    /* Defined in src/utility/win32_Utility.cpp */
    extern LARGE_INTEGER ClockFreq;
    extern LARGE_INTEGER StartCount;
    LARGE_INTEGER TickCount;
    HANDLE CurrentThread;
    DWORD_PTR OldThreadMask;

    /* Grab current thread handle */
    CurrentThread = GetCurrentThread();

    /* Run this on processor 1 only */
    OldThreadMask = SetThreadAffinityMask(CurrentThread, 1);

    /* Get tick count */
    QueryPerformanceCounter(&TickCount);

    /* Reset thread affinity mask for this thread */
    SetThreadAffinityMask(CurrentThread, OldThreadMask);

    return (Microseconds)(1000000 * TickCount.QuadPart / ClockFreq.QuadPart)
          - (Microseconds)(1000000 * StartCount.QuadPart / ClockFreq.QuadPart);
}

} /* bakge */

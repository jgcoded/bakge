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

#ifndef BAKGE_THREAD_WIN32_THREAD_H
#define BAKGE_THREAD_WIN32_THREAD_H

namespace bakge
{

typedef class win32_Thread : api::Thread
{
    /* Internal thread entry function */
    static DWORD WINAPI Entry(LPVOID Data);

    int (*UserEntry)(void*); /* End-user thread entry function */
    void* UserData; /* End-user specificied argument */
    int ExitCode; /* Exit code returned from user thread entry function */

    HANDLE ThreadHandle;
    DWORD ThreadIdentifier;

    win32_Thread();


public:

    virtual ~win32_Thread();

    BGE_FACTORY win32_Thread* Create(int (*EntryFunc)(void*), void* Data);

    Result Kill();
    int Wait();
    int GetExitCode();

} Thread; /* win32_Thread */

} /* bakge */

#endif /* BAKGE_THREAD_WIN32_THREAD_H */

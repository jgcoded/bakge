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

win32_Mutex::win32_Mutex()
{
    MutexHandle = NULL;
}


win32_Mutex::~win32_Mutex()
{
    if(MutexHandle != NULL)
        CloseHandle(MutexHandle);
}


win32_Mutex* win32_Mutex::Create()
{
    win32_Mutex* M = new win32_Mutex;

    // Create an unnamed mutex object
    M->MutexHandle = CreateMutex(NULL, FALSE, NULL);
    if(M->MutexHandle == NULL) {
        printf("Error creating mutex object\n");
        delete M;
        return NULL;
    }

    return M;
}


Result win32_Mutex::Lock()
{
    DWORD WaitResult = WaitForSingleObject(MutexHandle, INFINITE);
    if(WaitResult != WAIT_OBJECT_0) {
        printf("Error locking mutex object\n");
        return BGE_FAILURE;
    }

    return BGE_SUCCESS;
}


Result win32_Mutex::Unlock()
{
    if(ReleaseMutex(MutexHandle) == 0) {
        printf("Error releasing mutex object\n");
        return BGE_FAILURE;
    }

    return BGE_SUCCESS;
}

} /* bakge */

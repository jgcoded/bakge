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
    pthread_mutex_t WaitLock;
    timespec Delay;
    timeval Now;

    if(pthread_mutex_init(&WaitLock, NULL) < 0) {
        return BGE_FAILURE;
    }

    /* Implementation inspired by SFML */
    gettimeofday(&Now, NULL);

    Delay.tv_nsec = (Now.tv_usec + (Time % 1000000)) * 1000;
    Delay.tv_sec = Now.tv_sec + (Time / 1000000)
                   + (Delay.tv_nsec / 1000000000L);
    Delay.tv_nsec %= 1000000000L;

    pthread_mutex_lock(&WaitLock);
    pthread_mutex_timedlock(&WaitLock, &Delay);
    pthread_mutex_unlock(&WaitLock);
    pthread_mutex_destroy(&WaitLock);

    return BGE_SUCCESS;
}


Microseconds GetRunningTime()
{
    extern timespec StartTime; /* Defined in src/utility/x11_Utility.cpp */
    timespec Time;

    /* Get current time; convert it to milliseconds */
    clock_gettime(CLOCK_MONOTONIC, &Time);

    return ((Time.tv_sec - StartTime.tv_sec) * 1000000)
             + ((Time.tv_nsec - StartTime.tv_nsec) / 1000);
}

} /* bakge */

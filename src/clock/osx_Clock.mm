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
    NSTimeInterval DelayTime;

    DelayTime = Time / 1000000;
    DelayTime += 0.001 * (Time % 1000000);

    [NSThread sleepForTimeInterval: DelayTime];

    return BGE_FAILURE;
}


Microseconds GetRunningTime()
{
    extern NSDate* StartTime; /* Defined in src/utility/osx_Utility.mm */
    NSDate* Now;
    NSTimeInterval NowSec;

    /* Get current time & use it to get time since StartTime */
    Now = [NSDate date];
    NowSec = [Now timeIntervalSinceDate: StartTime];

    return NowSec * 1000000;
}

} /* bakge */

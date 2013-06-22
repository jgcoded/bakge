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

#ifndef BAKGE_CORE_EVENTHANDLER_H
#define BAKGE_CORE_EVENTHANDLER_H

#include <bakge/Bakge.h>

namespace bakge
{

/* *
 * EventHandler is really just a coupling interface class. Window classes
 * can be their own event handler, but can also link to an external handler.
 * This interface is used to ensure whatever the designated event handling
 * class is implements the proper methods for responding to events.
 *
 * Bakge will also have an ElectiveEventHandler class which lets you
 * "hook" into certain events and ignore others, with an easy way
 * to active/deactivate specific event types.
 * */
class EventHandler
{

public:

    EventHandler();
    virtual ~EventHandler();

    /* Key press/release and mouse button click/release events */
    virtual Result KeyEvent(KeyID K, KeyState S, ScanCode C, ModField M) = 0;
    virtual Result MouseEvent(ButtonID B, ButtonState S, ModField M) = 0;

    /* Relative device motion events */
    virtual Result MotionEvent(DeviceMotion X, DeviceMotion Y) = 0;
    virtual Result ScrollEvent(DeviceMotion X, DeviceMotion Y) = 0;

}; /* EventHandler */

} /* bakge */

#endif /* BAKGE_CORE_EVENTHANDLER_H */


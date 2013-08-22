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

/*!
 * @file EventHandler.h
 * @brief Contains EventHandler interface declaration.
 */

#ifndef BAKGE_CORE_EVENTHANDLER_H
#define BAKGE_CORE_EVENTHANDLER_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Interface for objects able to process Window events
 *
 * When a window event is processed, the appropriate callback is run
 * if an event handler exists for that window. The event is received
 * and processed internally; users need only implement methods for
 * responding to events.
 *
 * Certain events are only processed for the active window, such as key and
 * mouse input.
 */
class BGE_API EventHandler
{

public:

    EventHandler();
    virtual ~EventHandler();

    /*! @brief Called when a keyboard key is pressed or released
     *
     * @param[in] K The GLFW key identifier.
     * @param[in] S The GLFW key state identifier.
     * @param[in] C The OS-specific key scan-code.
     * @param[in] M Active modifiers bitfield.
     * 
     * @see http://www.glfw.org/docs/latest/glfw3_8h.html
     * @see ShiftPressed, AltPressed, ControlPressed, SuperPressed
     */
    virtual Result KeyEvent(KeyID K, KeyState S, ScanCode C, ModField M) = 0;

    /*! @brief Called when a mouse button is pressed or released
     */
    virtual Result MouseEvent(ButtonID B, ButtonState S, ModField M) = 0;

    /*! @brief Called when mouse motion is detected
     */
    virtual Result MotionEvent(DeviceMotion X, DeviceMotion Y) = 0;

    /*! @brief Called when the mouse wheel is scrolled
     */
    virtual Result ScrollEvent(DeviceMotion X, DeviceMotion Y) = 0;

    /*! @brief Called just before the Window closes
     */
    virtual Result CloseEvent() = 0;

}; /* EventHandler */

} /* bakge */

#endif /* BAKGE_CORE_EVENTHANDLER_H */

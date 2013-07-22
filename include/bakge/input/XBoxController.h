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

#ifndef BAKGE_INPUT_XBOXCONTROLLER_H
#define BAKGE_INPUT_XBOXCONTROLLER_H

#include <bakge/Bakge.h>

namespace bakge
{

enum XBOX_AXES
{
    XBOX_AXIS_LEFT_ANALOG_X = 0,
    XBOX_AXIS_LEFT_ANALOG_Y,
    XBOX_AXIS_TRIGGERS, /* Left trigger < 0, right trigger > 0 */
    XBOX_AXIS_RIGHT_ANALOG_Y,
    XBOX_AXIS_RIGHT_ANALOG_X,
    NUM_XBOX_AXES
};

enum XBOX_BUTTONS
{
    XBOX_BUTTON_A = 0,
    XBOX_BUTTON_B,
    XBOX_BUTTON_X,
    XBOX_BUTTON_Y,
    XBOX_BUTTON_LEFT_BUMPER,
    XBOX_BUTTON_RIGHT_BUMPER,
    XBOX_BUTTON_BACK,
    XBOX_BUTTON_START,
    XBOX_BUTTON_LEFT_ANALOG_STICK,
    XBOX_BUTTON_RIGHT_ANALOG_STICK,
    XBOX_BUTTON_DPAD_NORTH,
    XBOX_BUTTON_DPAD_UP = XBOX_BUTTON_DPAD_NORTH,
    XBOX_BUTTON_DPAD_EAST,
    XBOX_BUTTON_DPAD_RIGHT = XBOX_BUTTON_DPAD_EAST,
    XBOX_BUTTON_DPAD_SOUTH,
    XBOX_BUTTON_DPAD_DOWN = XBOX_BUTTON_DPAD_SOUTH,
    XBOX_BUTTON_DPAD_WEST,
    XBOX_BUTTON_DPAD_LEFT = XBOX_BUTTON_DPAD_WEST,
    NUM_XBOX_BUTTONS
};

} /* bakge */

#endif /* BAKGE_INPUT_XBOXCONTROLLER_H */

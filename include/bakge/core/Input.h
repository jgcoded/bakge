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

#ifndef BAKGE_CORE_INPUT_H
#define BAKGE_CORE_INPUT_H

#include <bakge/Bakge.h>

namespace bakge
{

/* GLFW key or button symbol */
typedef int KeyID;
typedef int ButtonID;

/* Bitfield containing active key modifiers */
typedef int ModField;

/* Platform code for the key */
typedef int ScanCode;

#define KEY_STATE_PRESSED GLFW_PRESS
#define KEY_STATE_RELEASED GLFW_RELEASE
#define KEY_STATE_REPEAT GLFW_REPEAT
typedef int KeyState;

#define BUTTON_STATE_PRESSED GLFW_PRESS
#define BUTTON_STATE_RELEASED GLFW_RELEASE
typedef int ButtonState;


inline bool ShiftPressed(ModField M)
{
    return M & GLFW_MOD_SHIFT > 0 ? true : false;
}


inline bool AltPressed(ModField M)
{
    return M & GLFW_MOD_ALT > 0 ? true : false;
}


inline bool ControlPressed(ModField M)
{
    return M & GLFW_MOD_CONTROL > 0 ? true : false;
}


inline bool SuperPressed(ModField M)
{
    return M & GLFW_MOD_SUPER > 0 ? true : false;
}

} /* bakge */

#endif /* BAKGE_CORE_INPUT_H */

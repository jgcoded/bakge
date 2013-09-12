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
 * @file Input.h
 * @brief Typedefs and methods for processing key and mouse input.
 */

#ifndef BAKGE_CORE_INPUT_H
#define BAKGE_CORE_INPUT_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief GLFW key identifier
 */
typedef int KeyID;

/*! @brief GLFW mouse button identifier
 */
typedef int ButtonID;

/*! @brief Bitfield containing pressed key modifiers
 */
typedef int ModField;

/*! @brief Platform-specific code for a key
 */
typedef int ScanCode;

/*! @brief Pressed, released or repeated key state
 */
typedef int KeyState;

/*! @brief Pressed or released mouse button state
 */
typedef int ButtonState;

/*! @brief Check if shift key is pressed in modfield.
 *
 * @param[in] M The bitfield containing modifier states
 *
 * @return true if M shows that a shift key is pressed, false if not.
 */
inline bool ShiftPressed(ModField M)
{
    return (M & GLFW_MOD_SHIFT) > 0 ? true : false;
}

/*! @brief Check if alt key is pressed in modfield.
 *
 * @param[in] M The bitfield containing modifier states
 *
 * @return true if M shows that a alt key is pressed, false if not.
 */
inline bool AltPressed(ModField M)
{
    return (M & GLFW_MOD_ALT) > 0 ? true : false;
}

/*! @brief Check if control key is pressed in modfield.
 *
 * @param[in] M The bitfield containing modifier states
 *
 * @return true if M shows that a control key is pressed, false if not.
 */
inline bool ControlPressed(ModField M)
{
    return (M & GLFW_MOD_CONTROL) > 0 ? true : false;
}

/*! @brief Check if super key is pressed in modfield.
 *
 * The super key differs in appearance and name across hardware and operating
 * systems. On Windows, the super key is the Windows key; on OS it is the
 * Home key.
 *
 * @param[in] M The bitfield containing modifier states
 *
 * @return true if M shows that a super key is pressed, false if not.
 */
inline bool SuperPressed(ModField M)
{
    return (M & GLFW_MOD_SUPER) > 0 ? true : false;
}

} /* bakge */

#endif /* BAKGE_CORE_INPUT_H */

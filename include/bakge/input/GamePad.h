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
 * @file GamePad.h
 * @brief GamePad class declaration.
 */

#ifndef BAKGE_INPUT_GAMEPAD_H
#define BAKGE_INPUT_GAMEPAD_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief A joystick or controller used for player input.
 *
 * GamePads allow players to use a joystick or controller for game input.
 * The API provides methods for getting raw axis values and button states.
 * Currently GamePads do not trigger EventHandler events; you will have to
 * implement your own way to detect changes in GamePad state.
 */
class BGE_API GamePad
{
    int Handle;

    int NumButtons;
    const unsigned char* ButtonStates;

    int NumAxes;
    const Scalar* AxesValues;

    /*! @brief Default GamePad constructor.
     *
     * Default GamePad constructor.
     */
    GamePad();


public:

    static GamePad* AvailableGamePads;

    /*! @brief Default GamePad destructor.
     *
     * Default GamePad destructor.
     */
    ~GamePad();

    /*! @brief Detects the first available joystick/controller and creates
     * a GamePad instance if one is found.
     *
     * This factory method scans for any available joysticks or controllers
     * and creates a new GamePad instance for the first available pad.
     *
     * @return Pointer to allocated GamePad or NULL if none are detected.
     */
    BGE_FACTORY GamePad* Detect();

    /*! @brief Get the number of buttons on the GamePad.
     *
     * Get the number of buttons on the GamePad.
     *
     * @return Number of buttons on the joystick/controller.
     */
    BGE_INL int GetNumButtons() const
    {
        return NumButtons;
    }

    /*! @brief Check if a GamePad button is pressed.
     *
     * Check if a GamePad button is pressed.
     *
     * @param[in] ButtonID The button's index on the GamePad.
     *
     * @return true if the button is pressed; false if it is not.
     */
    BGE_INL bool GetButtonPressed(int ButtonID)
    {
        ButtonStates = glfwGetJoystickButtons(Handle, &NumButtons);
        return ButtonStates[ButtonID] == GLFW_PRESS;
    }

    /*! @brief Get the number of axes on the GamePad.
     *
     * Get the number of axes on the GamePad.
     *
     * @return Number of axes on the joystick/controller.
     */
    BGE_INL int GetNumAxes() const
    {
        return NumAxes;
    }

    /*! @brief Get the value of an axis.
     *
     * The value of any given GamePad axis ranges from -1 to 1. The
     * orientation may vary depending on the layout or type of GamePad.
     *
     * @return Floating-point value of the axis, ranging from -1.0 to 1.0.
     */
    BGE_INL Scalar GetAxis(int AxisID)
    {
        AxesValues = glfwGetJoystickAxes(Handle, &NumAxes);
        return AxesValues[AxisID];
    }

}; /* GamePad */

} /* bakge */

#endif /* BAKGE_INPUT_GAMEPAD_H */

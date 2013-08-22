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

#ifndef BAKGE_CORE_WINDOW_H
#define BAKGE_CORE_WINDOW_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief GLFW window wrapper class
 *
 * Windows in Bakge have their own contexts, but have a shared context
 * across which they can share resources such as meshes, textures and
 * more.
 */
class BGE_API Window : public Bindable
{
    friend BGE_API Result Init(int argc, char* argv[]);
    friend BGE_API Result Deinit();

    static GLFWwindow* SharedContext;

    /* GLFW callbacks. Private for protection against bogus events */
    static void Moved(GLFWwindow*,  int, int);
    static void Resized(GLFWwindow*, int, int);
    static void Closed(GLFWwindow*);
    static void Key(GLFWwindow*, int, int, int, int);
    static void Mouse(GLFWwindow*, int, int, int);
    static void MouseMotion(GLFWwindow*, double, double);
    static void Scroll(GLFWwindow*, double, double);

    GLFWwindow* WindowHandle;

    /* Who receives events from the window? */
    EventHandler* Handler;

    /* Store last mouse position */
    struct {
        double X;
        double Y;
    } MouseCache;

    /* Store last scroll positions */
    struct {
        double X;
        double Y;
    } ScrollCache;

    Window();


public:

    ~Window();

    /*! @brief Create and initialize a Window
     *
     * This factory function creates and initializes a window. If any errors
     * occur, Create returns NULL.
     *
     * @param[in] Width The width of the created window.
     * @param[in] Height The height of the created window.
     *
     * @retval Pointer to allocated Window, or NULL if any errors occur.
     */
    BGE_FACTORY Window* Create(int Width, int Height);

    /*! @brief Poll all events for all existing windows
     *
     * GLFW polls all window events at the same time, calling a given
     * callback for each event.
     */
    static void PollEvents();

    /*! @brief Check if a window is currently open.
     *
     * An instance of Window doesn't guarantee that the actual window exists.
     * If a window is flagged for closing or doesn't exist, it is considered
     * closed.
     *
     * @retval true if the window exists and is not marked for deletion.
     * false otherwise.
     */
    bool IsOpen();

    /* Active windows are open, visible and in focus. */
    /*! @brief Check if a window is open, visible and in focus.
     *
     * Active windows are open and visible and currently have input focus,
     * meaning key, mouse and other device input is processed only for that
     * window.
     *
     * @retval true if window is open, visible and in focus. false otherwise.
     */
    bool IsActive();

    /*! @brief Mark a window for closing.
     *
     * @retval BGE_SUCCESS if the window was successfully closed, or
     * BGE_FAILURE if the window was unable to be closed.
     */
    Result Close();

    /*! @brief Swap a window's framebuffers.
     *
     * After rendering a scene, call SwapBuffers to flip the buffer onto the
     * screen. If a window is closed or iconified this function will fail.
     *
     * @retval BGE_SUCCESS if the window buffers were successfully swapped.
     * BGE_FAILURE if the window is closed, iconified or another error
     * occurred.
     */
    Result SwapBuffers();

    /*! @brief Bind the Window's context to the calling thread.
     *
     * Only one OpenGL context can be current on any given thread. This
     * method sets a window's context as current on the thread from which
     * it is called. Any previous bound window's context will no longer
     * be current on the thread.
     *
     * @retval BGE_SUCCESS if the context was successfully made current, and
     * BGE_FAILURE if any error occurred.
     */
    Result Bind() const;

    /*! @brief Unbind the Window's context from the calling thread.
     *
     * This method removes the window's context as the current context on the
     * thread from which it is called. The current context is set to none,
     * and no code that requires an active OpenGL context can be safely run
     * until a new Window is bound.
     *
     * @retval BGE_SUCCESS if the window context was removed as the current
     * context, or BGE_FAILURE if any error occurred.
     */
    Result Unbind() const;

    /*! @brief Set the event handler object for this window.
     *
     * This method sets the window's active event handler. If it is not NULL,
     * the appropriate EventHandler callback is run when the GLFW window
     * receives and processes an event.
     *
     * @param[in] Who Pointer to the new event handler object.
     *
     * @retval Pointer to the previous event handler object, or NULL if none
     * existed previously.
     */
    EventHandler* SetEventHandler(EventHandler* Who);

    /*! @brief Get the mouse's position
     *
     * @param[out] X Set to mouse's X position relative to the window.
     * @param[out] Y Set to mouse's Y position relative to the window.
     *
     * @retval BGE_SUCCESS if the device coordinates were successfully set. If
     * the window is not currently active, returns BGE_FAILURE.
     *
     * @see Window::IsActive()
     */
    Result GetMousePosition(DeviceCoord* X, DeviceCoord* Y);

    /*! @brief Set the mouse's position
     *
     * @param[in] X New X position of the mouse, relative to the window.
     * @param[in] Y New Y position of the mouse, relative to the window.
     *
     * @retval BGE_SUCCESS if the mouse position was successfully set. If the
     * window is not currently active, returns BGE_FAILURE.
     *
     * @see Window::IsActive()
     */
    Result SetMousePosition(DeviceCoord X, DeviceCoord Y);

    /*! @brief Hide a window, making it invisible.
     *
     * Hide a window, making it invisible.
     */
    void Hide();

    /*! @brief Show a window, making it visible.
     *
     * Show a window, making it visible.
     */
    void Show();

}; /* Window */

} /* bakge */

#endif /* BAKGE_CORE_WINDOW_H */

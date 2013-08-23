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
 * @file Engine.h
 * @brief Contains Engine interface declaration.
 */

#ifndef BAKGE_CORE_ENGINE_H
#define BAKGE_CORE_ENGINE_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief A framework interface for creating a game/application class
 *
 * This interface serves as a guide and framework when designing your
 * engine class. By no means is it required, but many typical game engines
 * will be implemented very similarly to this. By no means does your engine
 * implementation have to implement this interface, and even if you do
 * your implementation is entirely up to you, including how to handle errors
 * and determine how to report Results from each of the methods.
 */
class BGE_API Engine
{

public:

    /*! @brief Default Engine constructor
     *
     * Most classes in Bakge are not explicitly instantiable. You must create
     * one using an appropriate factory function. As this interface is simply
     * a guide when creating your engine class, you can implement your own
     * techniques for allocating and configuring new instances.
     */
    Engine();

    /*! @brief Pure-virtual Engine destructor
     *
     * Engine is an abstract interface class.
     */
    virtual ~Engine() = 0;

    /*! @brief Initialize the Engine and its components
     *
     * Engines require starting. Implementations of this method should
     * initialize all of the engine's components such as Renderers, UIs
     * and scene managers.
     *
     * @retval BGE_SUCCESS if engine initialization was successful, BGE_FAILURE
     * otherwise.
     */
    virtual Result Initialize() = 0;

    /*! @brief Shut down the engine and do clean up
     *
     * Clean up code should be done in this method instead of the destructor.
     *
     * @retval BGE_SUCCESS if the engine was successfully shut down,
     * BGE_FAILURE if any errors occurred.
     */
    virtual Result ShutDown() = 0;

    /*! @brief Run the Engine, entering the main loop
     *
     * The Run method should house the engine's main loop, which updates the
     * game world and renders it to the screen. Bakge does not control your
     * engine's main loop. You will have to measure time between updates and
     * dispatch Update and render stage calls yourself.
     *
     * @retval The exit code for the engine. Typically zero means no error
     * while any non-zero represents an arbitrary error.
     */
    virtual int Run() = 0;

    /*! @brief Update the game world with a time step of DeltaTime
     *
     * Time between Update calls should be measured and sent to the next
     * call as the DeltaTime parameter. This keeps the world updated at
     * a constant speed.
     *
     * @param[in] DeltaTime Time in seconds since the last update call.
     *
     * @retval BGE_SUCCESS if the application successfully updated, and
     * BGE_FAILURE if any error occurred.
     */
    virtual Result Update(Seconds DeltaTime) = 0;

    /*! @brief Prepare the engine for rendering
     *
     * This method will typically clear framebuffers and set up state for
     * rendering objects from the scene.
     *
     * @retval BGE_SUCCESS if the engine is ready for the RenderStage, or
     * BGE_FAILURE if any error occurred.
     */
    virtual Result PreRenderStage() = 0;

    /*! @brief Render the scene
     *
     * Render the scene's objects in this method.
     *
     * @retval BGE_SUCCESS if rendering completed successfully, and BGE_FAILURE
     * if any errors occurred.
     */
    virtual Result RenderStage() = 0;

    /*! @brief Run after the scene has been rendered
     *
     * This method will typically do things like blitting framebuffers,
     * swapping window buffers or setting default OpenGL state to protect
     * data from unintentional modification.
     *
     * @retval BGE_SUCCESS if the post-render stage completed successfully,
     * and BGE_FAILURE if any errors occurred.
     */
    virtual Result PostRenderStage() = 0;

}; /* Engine */

} /* bakge */

#endif /* BAKGE_CORE_ENGINE_H */

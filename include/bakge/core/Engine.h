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

#ifndef BAKGE_CORE_ENGINE_H
#define BAKGE_CORE_ENGINE_H

#include <bakge/Bakge.h>

namespace bakge
{

class Engine
{

public:

    Engine();
    virtual ~Engine();

    /* Initialize and clean up any components */
    virtual Result Initialize() = 0;
    virtual Result ShutDown() = 0;

    /* Run the application main loop */
    virtual int Run() = 0;

    /* *
     * The main loop updates the application/game world here.
     * Physics world steps, animation and anything that relates
     * to time is done here.
     * */
    virtual Result Update(Seconds DeltaTime) = 0;

    /* *
     * Rendering is split up into 3 stages, to allow for flexible
     * rendering targets such as offscreen framebuffers or textures.
     *
     * The PreRender stage is used to clear and set up framebuffers,
     * set modelview transforms, etc.
     *
     * The Render stage is when scene and GUI rendering takes place.
     *
     * The PostRender stage usually does things like blitting framebuffers
     * to the screen, switch to projection transforms, etc.
     * */
    virtual Result PreRenderStage() = 0;
    virtual Result RenderStage() = 0;
    virtual Result PostRenderStage() = 0;

}; /* Engine */

} /* bakge */

#endif /* BAKGE_CORE_ENGINE_H */

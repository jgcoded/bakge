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

#ifndef BAKGE_ENGINE_TESTENGINE_H
#define BAKGE_ENGINE_TESTENGINE_H

#include <bakge/Bakge.h>

namespace bakge
{

/* * 
 * A Generic Callback does not take a parameter.
 * It is used for Initialize, Shutdown, Pre/On/Post
 * RenderStage, etc.
 * */
typedef Result (*GenericCallback)(void*);

typedef Result (*UpdateCallback)(Seconds DeltaTime);
typedef Result (*KeyEventCallback)(KeyID K, KeyState S, ScanCode C, ModField M);
typedef Result (*MouseEventCallback)(ButtonID B, ButtonState S, ModField M);
typedef Result (*MotionEventCallback)(DeviceMotion X, DeviceMotion Y);
typedef Result (*ScrollEventCallback)(DeviceMotion X, DeviceMotion Y);

class BGE_API TestEngine : public Engine, public EventHandler
{

    /* *
     * Internal engine logic is private. TestEngine will provide
     * callbacks to the user so that different parts of his/her
     * code can be ran independent of the functionality of the
     * entire engine.
     *
     * All callbacks that are provided to TestEngine will be invoked
     * after TestEngine's internal logic has executed. If a callback
     * a certain callback is not provided, TestEngine will continue
     * running as if the callback did not exist. The idea is that
     * now the user is able to focus on the parts of the code that
     * require testing, without needing to write unrelated code.
     *
     * Input callbacks can be subscribed to by the user by setting
     * a callback.
     * */

    /* Initialize/Clean up components */
    Result Initialize();
    Result ShutDown();

    /* Run will have no callback */
    int Run();

    Result Update(Seconds DeltaTime);

    Result PreRenderStage();
    Result RenderStage();
    Result PostRenderStage();

    /* Input callbacks */
    /* Key press/release and mouse button click/release events */
    Result KeyEvent(KeyID K, KeyState S, ScanCode C, ModField M);
    Result MouseEvent(ButtonID B, ButtonState S, ModField M);

    /* Relative device motion events */
    Result MotionEvent(DeviceMotion X, DeviceMotion Y);
    Result ScrollEvent(DeviceMotion X, DeviceMotion Y);

    /* Called just before the window is closed */
    Result CloseEvent();

    Window* EngineWindow;

public:

    TestEngine();
    ~TestEngine();

    void SetInitializeCallback(GenericCallback Callback);
    void SetShutDownCallback(GenericCallback Callback);

    void SetUpdateCallback(UpdateCallback Callback);

    void SetPreRenderCallback(GenericCallback Callback);
    void SetRenderCallback(GenericCallback Callback);
    void SetPostRenderCallback(GenericCallback Callback);

    void SetKeyEventCallback(KeyEventCallback Callback);
    void SetMouseEventCallback(MouseEventCallback Callback);
    void SetMotionEventCallback(MotionEventCallback Callback);
    void ScrollEventCallback(ScrollEventCallback Callback);
    void SetCloseEventCallback(GenericCallback Callback);

}; /* TestEngine */

} /* bakge */

#endif /* BAKGE_ENGINE_TESTENGINE_H */
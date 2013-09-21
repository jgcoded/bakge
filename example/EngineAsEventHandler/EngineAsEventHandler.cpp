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

#include "EngineAsEventHandler.h"

EngineAsEventHandler::EngineAsEventHandler()
{
    printf("Creating a EngineAsEventHandler\n");
}


EngineAsEventHandler::~EngineAsEventHandler()
{
    printf("Destroying a EngineAsEventHandler\n");
}

bakge::Result EngineAsEventHandler::KeyEvent(bakge::KeyID K, bakge::ScanCode C,
                                        bakge::KeyState S, bakge::ModField M)
{
    printf("You %s %c\n", S == GLFW_PRESS ? "pressed" : "released", K);
    return BGE_SUCCESS;
}


bakge::Result EngineAsEventHandler::MouseEvent(bakge::ButtonID B,
                            bakge::ButtonState S, bakge::ModField M)
{
    printf("You %s mouse button %d\n", S == GLFW_PRESS ? "pressed" :
                                                        "released", B);
    return BGE_SUCCESS;
}


bakge::Result EngineAsEventHandler::MotionEvent(bakge::Motion X,
                                                bakge::Motion Y)
{
    printf("You moved the mouse %lf, %lf\n", X, Y);
    return BGE_SUCCESS;
}


bakge::Result EngineAsEventHandler::ScrollEvent(bakge::Motion X,
                                                bakge::Motion Y)
{
    printf("You scrolled the mouse wheel %lf, %lf\n", X, Y);
    return BGE_SUCCESS;
}


bakge::Result EngineAsEventHandler::CloseEvent()
{
    printf("Goodbye!\n");
    return BGE_SUCCESS;
}


int EngineAsEventHandler::Run()
{
    int ExitCode;

    while(1) {
        /* Poll events for all windows */
        bakge::Window::PollEvents();

        if(AppWindow->IsOpen() == false) {
            printf("Closing EngineAsEventHandler window\n");
            ExitCode = 0;
            break;
        }

        Update(0);
        PreRenderStage();
        RenderStage();
        PostRenderStage();
    }

    return ExitCode;
}


bakge::Result EngineAsEventHandler::ShutDown()
{
    gluDeleteQuadric(Quadric);

    delete AppWindow;
    delete SceneRenderer;

    return BGE_SUCCESS;
}


bakge::Result EngineAsEventHandler::Initialize()
{
    SceneRenderer = bakge::FrontRenderer::Create();
    if(SceneRenderer == NULL)
        return BGE_FAILURE;

    AppWindow = bakge::Window::Create(600, 400, 0);
    if(AppWindow == NULL)
        return BGE_FAILURE;

    /* Engine is the event handler! */
    AppWindow->SetEventHandler(this);

    Quadric = gluNewQuadric();

    glClearColor(0, 0.3f, 0.5f, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, 1.5, 0.1, 500.0);

    SceneRenderer->Bind();

    return BGE_SUCCESS;
}


bakge::Result EngineAsEventHandler::PreRenderStage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);
    return BGE_SUCCESS;
}


bakge::Result EngineAsEventHandler::PostRenderStage()
{
    glMatrixMode(GL_PROJECTION);
    AppWindow->SwapBuffers();
    return BGE_SUCCESS;
}


bakge::Result EngineAsEventHandler::RenderStage()
{
    /* *
     * Usually it would be SceneRenderer->Draw(&Something)
     * But there are on shape classes YET, so just do this
     * */
    glColor3f(0.7f, 0.7f, 0.7f);
    gluSphere(Quadric, 1.0f, 32, 32);
    return BGE_SUCCESS;
}


bakge::Result EngineAsEventHandler::Update(bakge::Seconds DeltaTime)
{
    /* Nothing to do really */
    return BGE_SUCCESS;
}

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

#include "SimpleEngine.h"

SimpleEngine::SimpleEngine()
{
    printf("Creating a SimpleEngine\n");
}


SimpleEngine::~SimpleEngine()
{
    printf("Destroying a SimpleEngine\n");
}


int SimpleEngine::Run()
{
    int ExitCode;

    while(1) {
        /* Poll events for all windows */
        bakge::Window::PollEvents();

        if(AppWindow->IsOpen() == false) {
            printf("Closing SimpleEngine window\n");
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


bakge::Result SimpleEngine::ShutDown()
{
    delete AppWindow;

    return BGE_SUCCESS;
}


bakge::Result SimpleEngine::Initialize()
{
    AppWindow = bakge::Window::Create(600, 400, 0);
    if(AppWindow == NULL)
        return BGE_FAILURE;

    glClearColor(0, 0.3f, 0.5f, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, 1.5, 0.1, 500.0);

    return BGE_SUCCESS;
}


bakge::Result SimpleEngine::PreRenderStage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);
    return BGE_SUCCESS;
}


bakge::Result SimpleEngine::PostRenderStage()
{
    glMatrixMode(GL_PROJECTION);
    AppWindow->SwapBuffers();
    return BGE_SUCCESS;
}


bakge::Result SimpleEngine::RenderStage()
{
    glColor3f(0.7f, 0.7f, 0.7f);
    return BGE_SUCCESS;
}


bakge::Result SimpleEngine::Update(bakge::Seconds DeltaTime)
{
    /* Nothing to do really */
    return BGE_SUCCESS;
}

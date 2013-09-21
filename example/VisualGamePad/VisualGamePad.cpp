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

#include "VisualGamePad.h"

const char* VertexShader =
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 VertexPosition = bge_View * bge_Model * bge_Vertex;\n"
    "    gl_Position = bge_Projection * VertexPosition;\n"
    "}\n"
    "\n";

const char* FragmentShader =
    "\n"
    "void main()\n"
    "{\n"
    "   gl_FragColor = vec4(1, 0, 0, 1);\n"
    "}\n"
    "\n";

VisualGamePad::VisualGamePad()
{
}


VisualGamePad::~VisualGamePad()
{
}


int VisualGamePad::Run()
{
    int ExitCode;

    while(1) {
        /* Poll events for all windows */
        bakge::Window::PollEvents();

        if(AppWindow->IsOpen() == false) {
            printf("Closing VisualGamePad window\n");
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


bakge::Result VisualGamePad::ShutDown()
{
    delete AppWindow;
    delete PadShader;
    delete Cam;
    delete AxisPoint;
    delete Pad;
    delete AxisTracker;

    return BGE_SUCCESS;
}


bakge::Result VisualGamePad::Initialize()
{
    AppWindow = bakge::Window::Create(800, 400, 0);
    if(AppWindow == NULL)
        return BGE_FAILURE;

    Cam = new bakge::Camera2D;
    if(Cam == NULL) {
        printf("Couldn't create Camera2D\n");
        return BGE_FAILURE;
    }

    glClearColor(0.2f, 0.5f, 0.9f, 1.0f);

    Cam->SetPosition(-400, -200, -1);
    Cam->SetSpan(800, 400, 2);

    Pad = bakge::GamePad::Detect();
    if(Pad == NULL) {
        printf("Couldn't detect any connected gamepads\n");
        return BGE_FAILURE;
    }

    AxisPoint = bakge::Rectangle::Create(10, 10);

    AxisTracker = bakge::Pawn::Create();
    AxisTracker->SetPosition(0, 0, 0);

    PadShader = bakge::Shader::LoadFromStrings(1, 1, &VertexShader,
                                                    &FragmentShader);
    if(PadShader == NULL) {
        printf("Error creating shader\n");
        return BGE_FAILURE;
    }

    PadShader->Bind();

    return BGE_SUCCESS;
}


bakge::Result VisualGamePad::PreRenderStage()
{
    glClear(GL_COLOR_BUFFER_BIT);

    return BGE_SUCCESS;
}


bakge::Result VisualGamePad::PostRenderStage()
{
    AppWindow->SwapBuffers();

    return BGE_SUCCESS;
}


bakge::Result VisualGamePad::RenderStage()
{
    Cam->Bind();
    AxisPoint->Bind();

    AxisTracker->Bind();
    AxisPoint->Draw();
    AxisTracker->Unbind();

    AxisPoint->Unbind();
    Cam->Unbind();

    return BGE_SUCCESS;
}


bakge::Result VisualGamePad::Update(bakge::Seconds DeltaTime)
{
    bakge::Scalar X = Pad->GetAxis(0);
    bakge::Scalar Y = Pad->GetAxis(1);
    AxisTracker->SetPosition(50 * X, 50 * Y, 0);

    return BGE_SUCCESS;
}

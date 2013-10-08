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

#include <bakge/gdk/engine/Common.h>

namespace bakge
{
namespace gdk
{

Application::Application()
{
}


Application::~Application()
{
    if(Gui != NULL)
        delete Gui;
}


Application* Application::Create()
{
    Application* App = new Application;

    App->Gui = GUI::Create();
    if(App->Gui == NULL) {
        Log("Application: Error creating GUI\n");
	return NULL;
    }

    return App;
}


Result Application::Initialize()
{
    return BGE_SUCCESS;
}


Result Application::ShutDown()
{
    return BGE_SUCCESS;
}


int Application::Run()
{
    return 0;
}


Result Application::Update(Seconds DeltaTime)
{
    return BGE_SUCCESS;
}


Result Application::PreRenderStage()
{
    return BGE_SUCCESS;
}


Result Application::PostRenderStage()
{
    return BGE_SUCCESS;
}


Result Application::RenderStage()
{
    return BGE_SUCCESS;
}

} /* gdk */
} /* bakge */

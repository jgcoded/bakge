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

#include <bakge/Bakge.h>

namespace bakge
{

TestEngine::TestEngine()
{
}


TestEngine::~TestEngine()
{
}


Result TestEngine::Initialize()
{

	EngineWindow = Window::Create(600, 400);
	if(EngineWindow == NULL)
		return BGE_FAILURE;

	glClearColor(0, 0.3f, 0.5f, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, 1.5, 0.1, 500.0);

    EngineWindow->SetEventHandler(&this);
    EngineWindow->Bind();

    if(InitCB != NULL)
    	InitCB();

    return BGE_SUCCESS;
}


Result TestEngine::ShutDown()
{

	EngineWindow->Unbind();
	delete EngineWindow;

	if(ShutDownCB != NULL)
		ShutDownCB();
}


int TestEngine::Run()
{

	int ExitCode;

	while(1)
	{

		Window::PollEvents();

		if(EngineWindow->IsOpen() == false) {

			ExitCode = 0;

			if(CloseEventCB != NULL)
				CloseEventCB();

			break;
		}


		Update(0);
		if(UpdateCB != NULL)
			UpdateCB();

		PreRenderStage();
		if(PreRenderCB != NULL)
			PreRenderCB();

		RenderStage();
		if(RenderCB != NULL)
			RenderCB();

		PostRenderStage();
		if(PostRenderCB != NULL)
			PostRenderCB();
	}

	return ExitCode;
}


Result TestEngine::Update(Seconds DeltaTime)
{
	/* Reserved for future logic */
	return BGE_SUCCESS;
}


Result TestEngine::PreRenderStage()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);
	return BGE_SUCCESS;
}


Result TestEngine::RenderStage()
{
	/* Reserved for future logic */
	return BGE_SUCCESS;
}


Result TestEngine::PostRenderStage()
{

	glMatrixMode(GL_PROJECTION);
	EngineWindow->SwapBuffers();
	return BGE_SUCCESS;
}


Result TestEngine::KeyEvent(KeyID K, KeyState S, ScanCode C, ModField M)
{
	if(KeyEventCB != NULL)
		return KeyEventCB(K, S, C, M);

	return BGE_FAILURE;
}


Result TestEngine::MouseEvent(ButtonID B, ButtonState S, ModField M)
{
	if(MouseEventCB != NULL)
		return MouseEventCB(B, S, M);

	return BGE_FAILURE;
}


Result TestEngine::MotionEvent(DeviceMotion X, DeviceMotion Y)
{
	if(MotionEventCB != NULL)
		MotionEventCB(X, Y);

	return BGE_FAILURE;
}


Result TestEngine::ScrollEvent(DeviceMotion X, DeviceMotion Y)
{
	if(ScrollEventCB != NULL)
		ScrollEventCB(X, Y);

	return BGE_FAILURE;
}


Result TestEngine::CloseEvent()
{
	if(CloseEventCB != NULL)
		return CloseEventCB();

	return BGE_FAILURE;
}


void TestEngine::SetInitializeCallback(GenericCallback Callback)
{
	InitCB = Callback;
}


void TestEngine::SetShutDownCallback(GenericCallback Callback)
{
	ShutDownCB = Callback;
}

} /* bakge */
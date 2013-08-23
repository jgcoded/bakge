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
#include "TestEngine.h"

using bakge::UIElement;

UIElement* E;
bakge::Camera* TestCam;
bakge::Texture* Tex;
bakge::Pawn* It;
GLint ShaderProgram;

bakge::Result InitTest()
{

    glEnable(GL_DEPTH_TEST);

    GLubyte* Bitmap = new GLubyte[512 * 512 * 3];

    memset((void*)Bitmap, 255, sizeof(Bitmap[0]) * 512 * 512 * 3);

    It = bakge::Pawn::Create();
    It->SetPosition(0, 0, 0);

    Tex = bakge::Texture::Create(512, 512, GL_RGB, GL_UNSIGNED_BYTE,
                                                (void*)Bitmap);

    E = bakge::UIElement::Create(0.8f, 0.5f);

    GLint Location;

    TestCam = new bakge::Camera;

    TestCam->SetPosition(0, 0, 3);
    TestCam->Bind();

    delete[] Bitmap;

    return BGE_SUCCESS;
}


bakge::Result PreRenderTest()
{
    Tex->Bind();
    E->Bind();
    It->Bind();

    return BGE_SUCCESS;
}


bakge::Result RenderTest()
{
    E->Draw();
    return BGE_SUCCESS;
}


bakge::Result PostRenderTest()
{
    It->Unbind();
    E->Unbind();
    Tex->Unbind();
    return BGE_SUCCESS;
}


bakge::Result ShutDownTest()
{
    if(E != NULL)
        delete E;

    if(Tex != NULL)
        delete Tex;

    if(It != NULL)
        delete It;

    return BGE_SUCCESS;
}


int main(int argc, char* argv[])
{

    bakge::Init(argc, argv);

    bakge::TestEngine* Engine = new bakge::TestEngine;

    Engine->SetInitializeCallback(InitTest);
    Engine->SetPreRenderCallback(PreRenderTest);
    Engine->SetRenderCallback(RenderTest);
    Engine->SetPostRenderCallback(PostRenderTest);
    Engine->SetShutDownCallback(ShutDownTest);

    Engine->StartEngine();


    bakge::Deinit();

    return 0;
}
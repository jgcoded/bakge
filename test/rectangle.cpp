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

#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>
#include "TestEngine.h"

bakge::Rectangle* Obj;
bakge::Pawn* It;
bakge::Texture* Tex;
GLint ShaderProgram;
bakge::Camera* TestCam;
GLubyte* Bitmap;

float Rot;
bakge::Microseconds NowTime;
bakge::Microseconds LastTime;

bakge::Result InitTest()
{
    Bitmap = new GLubyte[512 * 512 * 3];
    Rot = 0;
    LastTime = bakge::GetRunningTime();

    glEnable(GL_DEPTH_TEST);

    memset((void*)Bitmap, 0, sizeof(Bitmap[0]) * 512 * 512 * 2);

    for(int i=0;i<512;++i) {
        for(int j=0;j<512;++j){
            Bitmap[3 * (i*512+j)] = i % 100;
            Bitmap[3 * (i*512+j) + 1] = i % 75;
            Bitmap[3 * (i*512+j)] = i % 50;
        }
    }

    Tex = bakge::Texture::Create(512, 512, GL_RGB, GL_UNSIGNED_BYTE,
                                                    (void*)Bitmap);

    It = bakge::Pawn::Create();
    Obj = bakge::Rectangle::Create(0.8f, 0.5f);

    Obj->SetDrawStyle(bakge::BGE_SHAPE_STYLE_SOLID);

    It->SetPosition(0, 0, 0);

    GLint Location;

    TestCam = new bakge::Camera;
    TestCam->SetPosition(0, 0, 3);
    TestCam->Bind();

    return BGE_SUCCESS;
}
1

bakge::Result PreRenderTest()
{
    Tex->Bind();
    Obj->Bind();
    It->Bind();

    return BGE_SUCCESS;
}


bakge::Result RenderTest()
{
    Obj->Draw();

    return BGE_SUCCESS;
}


bakge::Result PostRenderTest()
{
    It->Unbind();
    Obj->Unbind();
    Tex->Unbind();

    return BGE_SUCCESS;
}


bakge::Result ShutDownTest()
{
    if(Obj != NULL)
        delete Obj;

    if(Tex != NULL)
        delete Tex;

    if(It != NULL)
        delete It;

    delete[] Bitmap;

    return BGE_SUCCESS;
}


int main(int argc, char* argv[])
{
    bakge::Init(argc, argv);

    bakge::TestEngine* RectTest = new bakge::TestEngine;

    RectTest->SetInitializeCallback(InitTest);
    RectTest->SetPreRenderCallback(PreRenderTest);
    RectTest->SetRenderCallback(RenderTest);
    RectTest->SetPostRenderCallback(PostRenderTest);
    RectTest->SetShutDownCallback(ShutDownTest);

    RectTest->StartEngine();

    delete RectTest;

    bakge::Deinit();

    return 0;
}

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
#include <vector>

using std::vector;
using bakge::UIElement;

bakge::Camera2D* TestCam;
bakge::Texture* Tex;
bakge::Pawn* It;
GLint ShaderProgram;


class ElementContainer : public bakge::UIContainer
{

private:

    vector<UIElement*> container;


public:

    ElementContainer()
    {
    }


    ~ElementContainer()
    {
    }


    void AddElement(UIElement* Element)
    {
        container.push_back(Element);
    }


    void RemoveElement(int At)
    {
        container.erase(container.begin() + At);
    }


    bakge::Result Bind() const
    {
        for(unsigned int i = 0; i < container.size(); ++i) {
            container[i]->Bind();
        }

        return BGE_SUCCESS;
    }

    bakge::Result Unbind()
    {
        for(int i = container.size() - 1; i >= 0; --i) {
            container[i]->Unbind();
        }

        return BGE_SUCCESS;
    }


    UIElement* BGE_NCP operator[](int At) const
    {
        return container[At];
    }


    bakge::Result DrawElements()
    {
        for(unsigned int i = 0; i < container.size(); i++)
        {
            container[i]->Draw();
        }

        return BGE_SUCCESS;
    }

} MyContainer; /* Element Container */


bakge::Result InitTest()
{

    glEnable(GL_DEPTH_TEST);

    GLubyte* Bitmap = new GLubyte[512 * 512 * 3];

    memset((void*)Bitmap, 255, sizeof(Bitmap[0]) * 512 * 512 * 3);

    It = bakge::Pawn::Create();
    It->SetPosition(0, 0, 0);

    Tex = bakge::Texture::Create(512, 512, GL_RGB, GL_UNSIGNED_BYTE,
                                                (void*)Bitmap);

    UIElement* E = bakge::UIElement::Create(0.8f, 0.5f);

    MyContainer.AddElement(E);

    TestCam = new bakge::Camera2D;

    TestCam->SetPosition(0, 0, 3);
    TestCam->Bind();

    delete[] Bitmap;

    return BGE_SUCCESS;
}


bakge::Result PreRenderTest()
{
    Tex->Bind();
    MyContainer.Bind();
    It->Bind();

    return BGE_SUCCESS;
}


bakge::Result RenderTest()
{
    MyContainer.DrawElements();
    return BGE_SUCCESS;
}


bakge::Result PostRenderTest()
{
    It->Unbind();
    MyContainer.Unbind();
    Tex->Unbind();
    return BGE_SUCCESS;
}


bakge::Result ShutDownTest()
{

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

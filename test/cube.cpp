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

int main(int argc, char* argv[])
{
    bakge::Window* Win;
    bakge::Cube* Obj;
    bakge::ShaderProgram* PlainShader;
    bakge::Texture* Tex;

    printf("Initializing Bakge\n");
    bakge::Init(argc, argv);

    GLubyte* Bitmap = new GLubyte[512 * 512 * 3];

    PlainShader = bakge::ShaderProgram::Create(NULL, NULL);

    Win = bakge::Window::Create(600, 400);
    if(Win == NULL) {
        printf("Error creating window\n");
        return bakge::Deinit();
    }

    glClearColor(1, 0, 1, 1);

    /* Make it easy to see our points */
    glEnable(GL_DEPTH_TEST);

    memset((void*)Bitmap, 0, sizeof(Bitmap[0]) * 512 * 512 * 3);

    /* Create simple texture */
    for(int i=0;i<256;++i) {
        for(int j=0;j<256;++j) {
            Bitmap[3*(i*512+j)] = 255;
            Bitmap[3*(i*512+j)+1] = 255;
            Bitmap[3*(i*512+j)+2] = 255;
        }
    }

    /* Create simple texture */
    for(int i=256;i<512;++i) {
        for(int j=256;j<512;++j) {
            Bitmap[3*(i*512+j)] = 255;
            Bitmap[3*(i*512+j)+1] = 255;
            Bitmap[3*(i*512+j)+2] = 255;
        }
    }

    memset((void*)Bitmap, 0, sizeof(Bitmap[0]) * 3);

    Tex = bakge::Texture::Create(512, 512, GL_RGB, GL_UNSIGNED_BYTE,
                                                    (void*)Bitmap);


    Obj = bakge::Cube::Create(0.4f, 0.4f, 0.4f);

    Obj->SetDrawStyle(bakge::BGE_SHAPE_STYLE_SOLID);

    PlainShader->Bind();

    bakge::Matrix Perspective;
    bakge::Matrix View;

    GLint ShaderProgram, Location;
    Perspective.SetPerspective(80.0f, 1.5f, 0.1f, 500.0f);
    View.SetLookAt(
        bakge::Point(0, 0, 3),
        bakge::Point(0, 0, 0),
        bakge::UnitVector(0, 1, 0)
    );
    glGetIntegerv(GL_CURRENT_PROGRAM, &ShaderProgram);
    Location = glGetUniformLocation(ShaderProgram, "bge_Perspective");
    glUniformMatrix4fv(Location, 1, GL_FALSE, &Perspective[0]);
    Location = glGetUniformLocation(ShaderProgram, "bge_View");
    glUniformMatrix4fv(Location, 1, GL_FALSE, &View[0]);

    float Rot = 0;
    bakge::Microseconds NowTime;
    bakge::Microseconds LastTime = bakge::GetRunningTime();

    while(1) {
        /* Poll events for all windows */
        bakge::Window::PollEvents();

        /* Don't draw if the window has closed */
        if(Win->IsOpen() == false)
            break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        NowTime = bakge::GetRunningTime();
        float DeltaTime = (float)(NowTime - LastTime) / 1000000;
        LastTime = NowTime;

        Rot += 1.0f * DeltaTime;
        View.SetLookAt(
            bakge::Point(cosf(Rot) * 0.9f, 0.5f, sinf(Rot) * 0.9f),
            bakge::Point(0.0f, 0, 0.0f),
            bakge::UnitVector(0, 1, 0)
        );
        glGetIntegerv(GL_CURRENT_PROGRAM, &ShaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "bge_View"), 1, GL_FALSE, &View[0]);

        Tex->Bind();
        Obj->Bind();
        Obj->Draw(); /* No renderer for now */
        Obj->Unbind();
        Tex->Unbind();

        Win->SwapBuffers();
    }

    if(Win != NULL)
        delete Win;

    if(Obj != NULL)
        delete Obj;

    if(PlainShader != NULL)
        delete PlainShader;

    if(Tex != NULL)
        delete Tex;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    delete[] Bitmap;

    return 0;
}

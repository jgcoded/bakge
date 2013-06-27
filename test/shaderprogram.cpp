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
    bakge::Node* Point;
    bakge::ShaderProgram* Program;
    bakge::math::Matrix Perspective;

    printf("Initializing Bakge\n");
    if(bakge::Init(argc, argv) != BGE_SUCCESS) {
        printf("Error initializing Bakge\n");
        return 1;
    }

    Win = bakge::Window::Create(600, 400);
    if(Win == NULL) {
        printf("Error creating window\n");
        return bakge::Deinit();
    }

    Point = bakge::Node::Create(0, 0, 0);
    if(Point == NULL) {
        printf("Unable to create Node\n");
        return 1;
    }

    /* Default shaders */
    Program = bakge::ShaderProgram::Create(NULL, NULL);

    /* Do some GL configuration */
    glClearColor(0, 0, 1, 1);
    glViewport(0, 0, 600, 400);
    glPointSize(10); /* Make it easy to see our points */

    /* Test at a new position */
    Point->SetPosition(0.8f, 0, 0);

    /* Ghetto-set our shader's perspective matrix */
    GLint ShaderProgram, Location;
    Perspective.SetPerspective(80.0f, 1.5f, 0.1f, 500.0f);
    glGetIntegerv(GL_CURRENT_PROGRAM, &ShaderProgram);
    Location = glGetUniformLocation(ShaderProgram, "bge_Perspective");
    glUniformMatrix4fv(Location, 1, GL_FALSE, &Perspective[0]);

    while(1) {
        /* Poll events for all windows */
        bakge::Window::PollEvents();

        /* Don't draw if the window has closed */
        if(Win->IsOpen() == false)
            break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1, 1, 1);
        Point->Bind();
        Point->Draw(); /* No renderer for now */
        Point->Unbind();
        Win->SwapBuffers();
    }

    Program->Unbind();
    if(Program != NULL)
        delete Program;

    if(Win != NULL)
        delete Win;

    if(Point != NULL)
        delete Point;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}

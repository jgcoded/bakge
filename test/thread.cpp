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

int ThreadFunc(void* Data)
{
    bakge::Window* Win;

    Win = (bakge::Window*)Data;
    /* While window is open, print dots from this thread */
    while(Win->IsOpen()) {
        bakge::Delay(100000);
        printf(".");
        fflush(0);
    }
    printf("\n");

    return 0;
}


int main(int argc, char* argv[])
{
    printf("Initializing Bakge\n");
    bakge::Init(argc, argv);

    bakge::Window* Win;
    bakge::Thread* Thr;

    Win = bakge::Window::Create(600, 400);
    Thr = bakge::Thread::Create(ThreadFunc, (void*)Win);

    if(Win == NULL || Thr == NULL) {
        printf("Error initializing window and thread\n");
        goto CLEANUP;
    }

    glClearColor(1, 0, 0, 1);
    glViewport(0, 0, 600, 400);

    while(1) {
        /* Poll events for all windows */
        bakge::Window::PollEvents();

        /* Don't draw if the window has closed */
        if(Win->IsOpen() == false)
            break;

        Win->Bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Win->SwapBuffers();
        Win->Unbind();
    }


CLEANUP:

    if(Thr != NULL)
        delete Thr;

    if(Win != NULL)
        delete Win;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}

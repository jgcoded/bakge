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

#define ARR_SIZE 7
#define NUM_THREADS 3

int TestArray[ARR_SIZE] = { 5, 3, 52, 25, 3, 2, 5};
bakge::Mutex* Mut;

int ThreadFunc(void* Data)
{
    bakge::Window* Win;

    Win = (bakge::Window*)Data;

    while(Win->IsOpen()) {
        bakge::Delay(100000);
        printf("First value of the array is: ");
        printf("%d\n\n", TestArray[0]);

        Mut->Lock();
        for(int i = 0; i < ARR_SIZE; ++i) {
            TestArray[i]+= 1;
        }
        Mut->Unlock();

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

    Mut = bakge::Mutex::Create();
    Win = bakge::Window::Create(600, 400);

    bakge::Thread* TestThreads[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; ++i) {
        TestThreads[i] = bakge::Thread::Create(ThreadFunc, (void*)Win);
    }

    if(Win == NULL) {
        printf("Error initializing window\n");
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

    if(TestThreads != NULL)
        delete[] TestThreads;

    if(Win != NULL)
        delete Win;

    if(Mut != NULL)
        delete Mut;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}

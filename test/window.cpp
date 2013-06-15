
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main(int argc, char* argv[])
{
    bakge::Window* Win;

    printf("Initializing Bakge\n");
    bakge::Init(argc, argv);
    printf("Done initializing\n");

    printf("Creating window\n");
    Win = bakge::Window::Create(600, 400);

    bakge::Event Ev;

    printf("Beginning GL calls\n");

    glClearColor(1, 0, 0, 1);

    printf("Entering main loop\n");

    while(1) {
        while(Win->PollEvent(&Ev) == BGE_SUCCESS) {
            if(Ev.Type == -1)
                Win->Close();
        }

        /* Don't draw if the window has closed */
        if(Win->IsOpen() == false)
            break;

        Win->Bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Win->SwapBuffers();
        Win->Unbind();
    }

    printf("Main loop terminated\n");

    if(Win != NULL)
        delete Win;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}

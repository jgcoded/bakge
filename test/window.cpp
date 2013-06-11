
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main(int argc, char* argv[])
{
    bakge::Window* Win;

    printf("Initializing Bakge\n");
    bakge::Init(argc, argv);

    Win = bakge::Window::Create(64, 64);

    bakge::Event Ev;

    while(Win->IsOpen()) {
        while(Win->PollEvent(&Ev) == BGE_SUCCESS) {
            if(Ev.Type == -1)
                Win->Close();
        }
    }

    if(Win != NULL)
        delete Win;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}

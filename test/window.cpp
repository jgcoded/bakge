
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main(int argc, char* argv[])
{
    bakge::Window* Win;

    bakge::Init(argc, argv);

    Win = bakge::Window::Create(64, 64);

    /* *
     * Future window testing will go here.
     * */

    if(Win != NULL)
        delete Win;

    bakge::Deinit();

    return 0;
}

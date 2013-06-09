
/* *
 * Compile: g++ -o window window.cpp -I<path_to_bakge>/include
 *              -lm -L<path_to_bakge>/lib -lbakge
 * */

#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main()
{
    bakge::Window* Win;

    Win = bakge::Window::Create(64, 64);

    /* *
     * Future window testing will go here.
     * */

    if(Win != NULL)
        delete Win;

    return 0;
}

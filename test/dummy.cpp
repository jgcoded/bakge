
/* *
 * Compile: g++ -o dummy dummy.cpp -I<path_to_bakge>/include
 *              -lm -L<path_to_bakge>/lib -lbakge
 * */

#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main()
{
    bakge::Window W;
    W.Dummy();
    return 0;
}


/* *
 * Compile: g++ -o types types.cpp -I<path_to_bakge>/include
 *              -lm -L<path_to_bakge>/lib -lbakge
 *
 * Test various types in Bakge here.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main()
{

    /* Test bakge::Result */
    bakge::Result Res = BGE_FAILURE;
    if(Res == BGE_SUCCESS) {
        printf("Operation successful!\n");
    } else {
        printf("Operation failed!\n");
    }

    return 0;
}

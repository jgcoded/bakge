
/* *
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

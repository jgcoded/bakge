
/* *
 * Test out GLFW from Bakge
 * */

#include <stdio.h>
#include <stdlib.h>

/* Bakge includes GLFW */
#include <bakge/Bakge.h>


int main()
{
    if(!glfwInit()) {
        printf("GLFW Initialization failed\n");
    }

    printf("GLFW stuff!\n");

    printf("GLFW Termination\n");
    glfwTerminate();

    return 0;
}

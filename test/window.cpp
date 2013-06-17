
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>

void glfwErrorCallback(int Code, const char* Description)
{
    printf("GLFW error %d: %s\n", Code, Description);
}

int main(int argc, char* argv[])
{
    bakge::Window* Win;

    glfwSetErrorCallback(glfwErrorCallback);

    printf("Initializing Bakge\n");
    if(bakge::Init(argc, argv) != BGE_SUCCESS) {
        printf("Error initializing Bakge\n");
        return 1;
    }

    Win = bakge::Window::Create(600, 400);
    if(Win == NULL) {
        printf("Error creating Bakge window\n");
        return bakge::Deinit();
    }

    bakge::Event Ev;

    glClearColor(1, 0, 0, 1);
    glViewport(0, 0, 600, 400);

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

    if(Win != NULL)
        delete Win;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}

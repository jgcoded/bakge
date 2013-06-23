
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>

#define CHECK_EXT(EXT) \
    if(glewIsSupported(EXT)) { \
        printf("%s supported\n", EXT); \
    } else { \
        printf("%s not supported\n", EXT); \
    }

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

    printf("========================================\n");
    printf("OpenGL %s\n", glGetString(GL_VERSION));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("%s\n", glGetString(GL_VENDOR));
    CHECK_EXT("GL_ARB_vertex_array_object")
    CHECK_EXT("GL_EXT_bindable_uniform")
    CHECK_EXT("GL_EXT_geometry_shader4")
    printf("========================================\n");

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

    if(Win != NULL)
        delete Win;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main(int argc, char* argv[])
{
    bakge::Window* Win;
    bakge::Node* Point;
    bakge::ShaderProgram* Program;

    printf("Initializing Bakge\n");
    if(bakge::Init(argc, argv) != BGE_SUCCESS) {
        printf("Error initializing Bakge\n");
        return 1;
    }

    Win = bakge::Window::Create(600, 400);
    if(Win == NULL) {
        printf("Error creating window\n");
        return bakge::Deinit();
    }

    Point = bakge::Node::Create(0, 0, 0);
    if(Point == NULL) {
        printf("Unable to create Node\n");
        return 1;
    }

    /* Default shaders */
    printf("Creating default shader program\n");
    Program = bakge::ShaderProgram::Create(NULL, NULL);

    glClearColor(0, 0, 1, 1);
    glViewport(0, 0, 600, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, 1.5, 0.1, 500.0);

    /* Make it easy to see our points */
    glEnable(GL_POINT_SMOOTH);
    glPointSize(10);
    glHint(GL_POINT_SMOOTH, GL_NICEST);

    /* *
     * Test out node position setting/getting uses OpenGL buffers
     * */
    Point->Bind();
    /* Test this node's position */
    bakge::math::Vector4 Pos = Point->GetPosition();
    printf("%02.2lf %02.2lf %02.2lf\n", Pos[0], Pos[1], Pos[2]);

    /* Test at a new position */
    Point->SetPosition(3, 3, 1);
    Pos = Point->GetPosition();
    printf("%02.2lf %02.2lf %02.2lf\n", Pos[0], Pos[1], Pos[2]);
    Point->Unbind();

    while(1) {
        /* Poll events for all windows */
        bakge::Window::PollEvents();

        /* Don't draw if the window has closed */
        if(Win->IsOpen() == false)
            break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);
        glColor3f(1, 1, 1);
        Point->Bind();
        Point->Draw(); /* No renderer for now */
        Point->Unbind();
        glMatrixMode(GL_PROJECTION);
        Win->SwapBuffers();
    }

    Program->Unbind();
    if(Program != NULL)
        delete Program;

    if(Win != NULL)
        delete Win;

    if(Point != NULL)
        delete Point;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}

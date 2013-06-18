
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main(int argc, char* argv[])
{
    bakge::Window* Win;
    bakge::Node Point;

    printf("Initializing Bakge\n");
    bakge::Init(argc, argv);

    Win = bakge::Window::Create(600, 400);

    bakge::Event Ev;

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

    while(1) {
        while(Win->PollEvent(&Ev) == BGE_SUCCESS) {
            if(Ev.Type == -1)
                Win->Close();
        }

        /* Don't draw if the window has closed */
        if(Win->IsOpen() == false)
            break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);
        glColor3f(1, 1, 1);
        Point.Bind();
        Point.Draw(); /* No renderer for now */
        Point.Unbind();
        glMatrixMode(GL_PROJECTION);
        Win->SwapBuffers();
    }

    if(Win != NULL)
        delete Win;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}

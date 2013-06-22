
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>

void PrintMatrix(bakge::math::Scalar M[16])
{
    printf("[ %03.2f %03.2f %03.2f %03.2f ]\n", M[0], M[4], M[8], M[12]);
    printf("[ %03.2f %03.2f %03.2f %03.2f ]\n", M[1], M[5], M[9], M[13]);
    printf("[ %03.2f %03.2f %03.2f %03.2f ]\n", M[2], M[6], M[10], M[14]);
    printf("[ %03.2f %03.2f %03.2f %03.2f ]\n", M[3], M[7], M[11], M[15]);
}

int main(int argc, char* argv[])
{
    bakge::Window* Win;
    bakge::Node* Point;
    bakge::ShaderProgram* Program;
    bakge::math::Matrix Perspective;

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
    Program = bakge::ShaderProgram::Create(NULL, NULL);
    Program->Bind();

    glClearColor(0, 0, 1, 1);
    glViewport(0, 0, 600, 400);

    gluPerspective(50.0f, 1.5f, 0.1f, 500.0f);
    Perspective.SetPerspective(80.0f, 1.5f, 0.1f, 500.0f);

    /* Compare OpenGL and our perspective matrix */
    bakge::math::Scalar MatrixArray[16];

    glGetFloatv(GL_PROJECTION_MATRIX, MatrixArray);

    printf("OpenGL matrix\n");
    printf("=============\n");
    PrintMatrix(MatrixArray);

    printf("Our matrix\n");
    printf("==========\n");
    PrintMatrix(&Perspective[0]);

    /* Make it easy to see our points */
    glPointSize(10);

    /* Test at a new position */
    Point->SetPosition(0.8f, 0, 0);

    GLint ShaderProgram, Location;
    glGetIntegerv(GL_CURRENT_PROGRAM, &ShaderProgram);
    Location = glGetUniformLocation(ShaderProgram, "bge_Perspective");
    glUniformMatrix4fv(Location, 1, GL_FALSE, &Perspective[0]);

    while(1) {
        /* Poll events for all windows */
        bakge::Window::PollEvents();

        /* Don't draw if the window has closed */
        if(Win->IsOpen() == false)
            break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1, 1, 1);
        Point->Bind();
        Point->Draw(); /* No renderer for now */
        Point->Unbind();
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

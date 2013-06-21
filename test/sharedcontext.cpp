
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main(int argc, char* argv[])
{
    bakge::Texture* Tex;
    bakge::Byte* PictureInfo;
    bakge::Window* Win;
    bakge::Window* Win2;

    bakge::Init(argc, argv);

    PictureInfo = (bakge::Byte*)malloc(512 * 512 * 3);

    /* Create a random (really ugly) texture */
    for(int i=0;i<512;++i) {
        for(int j=0;j<512;++j) {
            PictureInfo[i*512*3+j] = (j - i) * 256 / 512;
            PictureInfo[i*512*3+j+1] = j * 256 / 512;
            PictureInfo[i*512*3+j+2] = i * 256 / 512;
        }
    }

    Win = bakge::Window::Create(64, 64);
    Win->Bind();

    /* Load texture on Win, then we'll use it on Win2 */
    Tex = bakge::Texture::Create(64, 64, GL_RGB, GL_UNSIGNED_BYTE,
                                                (void*)PictureInfo);

    delete Win;

    Win2 = bakge::Window::Create(600, 400);
    Win2->Bind();

    glClearColor(1, 0, 0, 1);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 600, 0, 400, -1, 1);

    while(1) {
        /* Poll events for all windows */
        bakge::Window::PollEvents();

        /* Don't draw if the window has closed */
        if(Win2->IsOpen() == false)
            break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        Tex->Bind();
        glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i(0, 0);
        glTexCoord2i(0, 1); glVertex2i(0, 400);
        glTexCoord2i(1, 1); glVertex2i(600, 400);
        glTexCoord2i(1, 0); glVertex2i(600, 0);
        glEnd();
        Tex->Unbind();

        glMatrixMode(GL_PROJECTION);
        Win2->SwapBuffers();
    }

    if(Win2 != NULL)
        delete Win2;

    if(Tex != NULL)
        delete Tex;

    free(PictureInfo);

    bakge::Deinit();

    return 0;
}

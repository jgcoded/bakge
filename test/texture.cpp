
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main(int argc, char* argv[])
{
    bakge::Texture* Tex;
    bakge::Byte* PictureInfo;
    bakge::Window* Win;

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

    Win = bakge::Window::Create(600, 400);
    Win->Bind();

    /* When testing the completed class, pass raw image data as last param */
    Tex = bakge::Texture::Create(64, 64, GL_RGB, GL_UNSIGNED_BYTE, (void*)PictureInfo);

    bakge::Event Ev;

    glClearColor(1, 0, 0, 1);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 600, 0, 400, -1, 1);

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

        Tex->Bind();
        glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i(0, 0);
        glTexCoord2i(0, 1); glVertex2i(0, 400);
        glTexCoord2i(1, 1); glVertex2i(600, 400);
        glTexCoord2i(1, 0); glVertex2i(600, 0);
        glEnd();
        Tex->Unbind();
        
        glMatrixMode(GL_PROJECTION);
        Win->SwapBuffers();
    }


    if(Win != NULL)
        delete Win;

    if(Tex != NULL)
        delete Tex;

    free(PictureInfo);

    bakge::Deinit();

    return 0;
}

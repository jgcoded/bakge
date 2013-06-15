
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main(int argc, char* argv[])
{
    bakge::Texture* Tex;
	bakge::Byte* pictureInfo;
	bakge::Window* win;

    bakge::Init(argc, argv);

	pictureInfo = bakge::LoadFileContents("C:\\Users\\Student\\Desktop\\texture.raw");

    /* When testing the completed class, pass raw image data as last param */
    Tex = bakge::Texture::Create(64, 64, GL_RGB, GL_UNSIGNED_BYTE, (void*)pictureInfo);

	win = bakge::Window::Create(600, 400);

    bakge::Event Ev;

    glClearColor(1, 0, 0, 1);


	    while(1) {
        while(win->PollEvent(&Ev) == BGE_SUCCESS) {
            if(Ev.Type == -1)
                win->Close();
        }

        /* Don't draw if the window has closed */
        if(win->IsOpen() == false)
            break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glLoadIdentity(); 
		//glEnable( GL_TEXTURE_2D );
		//gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		
		Tex->Draw();

        win->SwapBuffers();
    }

    



    /* *
     * Future texture testing will go here.
     * The texture will need to be drawn to fully test it, so a simple
     * window/engine class might be built for this test too
     * */



	if(win != NULL)
		delete win;

    if(Tex != NULL)
        delete Tex;

    bakge::Deinit();

    return 0;
}

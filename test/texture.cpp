
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main()
{
    bakge::Texture* Tex;

    /* When testing the completed class, pass raw image data as last param */
    Tex = bakge::Texture::Create(64, 64, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    /* *
     * Future texture testing will go here.
     * The texture will need to be drawn to fully test it, so a simple
     * window/engine class might be built for this test too
     * */

    if(Tex != NULL)
        delete Tex;

    return 0;
}

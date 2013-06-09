#ifndef BAKGE_CORE_TEXTURE_H
#define BAKGE_CORE_TEXTURE_H

#include <bakge/Bakge.h>

namespace bakge
{

class Texture : public Bindable
{

public:

    Texture();
    ~Texture();

    /* *
     * Accepts metadata and raw image data to create an OpenGL texture
     * Width, Height, Format and Type are metadata, while Data is the
     * raw image data.
     * */
    BGE_FACTORY Texture* Create(int Width, int Height, GLint Format,
                                            GLenum Type, void* Data);

}; /* Texture */

} /* bakge */

#endif /* BAKGE_CORE_TEXTURE_H */


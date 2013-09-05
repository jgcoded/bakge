/* *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Paul Holden et al. (See AUTHORS)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * */

#ifndef BAKGE_GRAPHICS_TEXTURE_H
#define BAKGE_GRAPHICS_TEXTURE_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief OpenGL texture wrapper class
 *
 * Textures are used to color meshes and other polygons drawn with OpenGL,
 * such as meshes or a GUI. They can also be used to hold framebuffers to
 * which OpenGL renders to.
 */
class BGE_API Texture : public Bindable
{
    int Width;
    int Height;

    GLenum Location;
    GLuint TextureID;


public:

    /*! @brief Default Texture constructor.
     *
     * Default Texture constructor.
     */
    Texture();

    /*! @brief Default Texture destructor.
     *
     * Default Texture destructor.
     */
    ~Texture();

    /*! @brief Create a texture instance and upload texture data to OpenGL.
     *
     * This factory method accepts texture data and metadata and creates
     * and uploads to a new OpenGL texture.
     *
     * @param[in] Width Width of the texture in pixels.
     * @param[in] Height Height of the texture in pixels.
     * @param[in] Format OpenGL format of the data to upload.
     * @param[in] Type Type of data being uploaded.
     * @param[in] Data The texture data to upload.
     *
     * @retval Pointer to newly created texture; NULL if any errors occurred.
     *
     * @see http://www.opengl.org/wiki/Texture
     */
    BGE_FACTORY Texture* Create(int Width, int Height, GLint Format,
                                            GLenum Type, void* Data);

    /*! @brief Bind the texture as active in its assigned location.
     *
     * Binding the texture sets it as the active texture for its assigned
     * location. Color information can be extracted from the texture using
     * the texture (or texture2D) call in your GLSL shader using the
     * appropriate uniform location and texture coordinates.
     *
     * @retval BGE_SUCCESS if the texture was successfully bound; BGE_FAILURE
     * if any errors occurred.
     */
    Result Bind() const;

    /*! @brief Unbind the texture from its assigned location.
     *
     * Unbinding a texture is important so future texture-related OpenGL
     * calls don't affect it.
     *
     * @retval BGE_SUCCESS if the texture was successfully unbound; BGE_FAILURE
     * if any errors occurred.
     */
    Result Unbind() const;

    /*! @brief Get the width of the texture in pixels.
     *
     * Get the width of the texture in pixels.
     *
     * @retval Width of the texture in pixels.
     */
    BGE_INL int GetWidth() const
    {
        return Width;
    }

    /*! @brief Get the height of the texture in pixels.
     *
     * Get the height of the texture in pixels.
     *
     * @retval Height of the texture in pixels.
     */
    BGE_INL int GetHeight() const
    {
        return Height;
    }

}; /* Texture */

} /* bakge */

#endif /* BAKGE_GRAPHICS_TEXTURE_H */

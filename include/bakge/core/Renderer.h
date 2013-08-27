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

/*!
 * @file Renderer.h
 * @brief Renderer interface declaration.
 */

#ifndef BAKGE_CORE_RENDERER_H
#define BAKGE_CORE_RENDERER_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Renderers are objects which render scene objects.
 *
 * Some renderers may have subcomponents which internally manage OpenGL
 * state for their rendering. A simple renderer may simply render directly
 * to the screen or render to texture, such as a deferred renderer.
 */
class BGE_API Renderer : public Bindable
{

public:

    Renderer();
    virtual ~Renderer();

    /*! @brief Render a Drawable object
     */
    virtual Result Draw(Drawable* Obj) = 0;

}; /* Renderer */

} /* bakge */

#endif /* BAKGE_CORE_RENDERER_H */

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

#ifndef BAKGE_CORE_BINDABLE_H
#define BAKGE_CORE_BINDABLE_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Bindables must be bound before use, and unbound after use.
 *
 * Bindables are typically involved in graphics and rendering. Calling Bind
 * sets up the OpenGL state so that the object can be properly used
 * for rendering. Bindables range from objects such as Renderers, Pawns
 * or Meshes.
 *
 * Bindables come in many different forms, and each implementation of
 * Bind and Unbind has a specific purpose. See individual implementations
 * for details on when and why objects must be bound and unbound.
 */
class BGE_API Bindable
{

public:

    Bindable();
    virtual ~Bindable();

    /*! @brief Bind the object for use
     *
     * Bind returns BGE_SUCCESS if the object can safely be used as intended.
     * A BGE_FAILURE result means the object was not successfully bound,
     * and use results in undefined behavior.
     */
    virtual Result Bind() const = 0;

    /*! @brief Unbind the object after use
     *
     * Unbind will seldom return BGE_FAILURE. Unbind usually resets OpenGL
     * state to an arbitrary default. It is always a good idea to Unbind an
     * object after use, to prevent unintentionally modifying objects.
     */
    virtual Result Unbind() const = 0;

}; /* Bindable */

} /* bakge */

#endif /* BAKGE_CORE_BINDABLE_H */

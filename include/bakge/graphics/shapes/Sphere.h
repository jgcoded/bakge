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
 * @file Sphere.h
 * @brief Sphere class declaration.
 */

#ifndef BAKGE_GRAPHICS_SHAPES_SPHERE_H
#define BAKGE_GRAPHICS_SHAPES_SPHERE_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief A sphere centered about the origin.
 *
 * A sphere centered about the origin with radius 0.5. The number of slices
 * and stacks used to create the sphere determines the smoothness of the
 * sphere's surface, but results in higher vertex counts.
 */
class BGE_API Sphere : public Mesh
{

protected:

    /*! @brief Protected Sphere constructor.
     *
     * Protected Sphere constructor.
     */
    Sphere();


public:

    /*! @brief Sphere destructor.
     *
     * Sphere destructor.
     */
    ~Sphere();

    /*! @brief Create a new Sphere instance.
     *
     * Create a new Sphere instance.
     *
     * @return Pointer to allocated Sphere; NULL if any errors occurred.
     */
    BGE_FACTORY Sphere* Create();

}; // Sphere

} // bakge

#endif // BAKGE_GRAPHICS_SHAPES_SPHERE_H

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
 * @file Geometry.h
 * @brief Geometry class declaration.
 */

#ifndef BAKGE_GRAPHICS_GEOMETRY_H
#define BAKGE_GRAPHICS_GEOMETRY_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Geometries are unenclosed objects that are drawn as a set of line
 * segments.
 *
 * The distinction between the Shape and Geometry is in the way they are
 * drawn. Geometries are objects like lines, line strips or curves which
 * are unenclosed, and therefore have no volume.
 */
class BGE_API Geometry : public Drawable
{

protected:

    /*! @brief Default constructor.
     *
     * Default constructor.
     */
    Geometry();


public:

    /*! @brief Pure-virtual destructor.
     *
     * Pure-virtual destructor.
     */
    virtual ~Geometry();

    /*! @brief Render the Geometry.
     *
     * Render the Geometry. Geometries are typically rendered using lines
     * or line segments.
     *
     * @return BGE_SUCCESS if the Geometry was successfully drawn; BGE_FAILURE
     * otherwise.
     */
    virtual Result Draw() const;

}; // Geometry

} // bakge

#endif // BAKGE_GRAPHICS_GEOMETRY_H

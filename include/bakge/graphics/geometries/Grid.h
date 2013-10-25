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
 * @file Grid.h
 * @brief Grid class declaration.
 */

#ifndef BAKGE_GRAPHICS_GEOMETRY_GRID_H
#define BAKGE_GRAPHICS_GEOMETRY_GRID_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief A grid is a series of line segments drawn in the XZ plane.
 *
 * A grid is a series of line segments drawn in the XZ plane. Grids can be
 * rotated to be drawn aligned to any arbitrary plane, and rotated inside that
 * plane.
 */
class BGE_API Grid : public Geometry
{
    // These values * 2 are number of grid units. Rows = Z, Cols = X
    int HalfRows;
    int HalfCols;

    // Grid unit length along X axis
    Scalar UnitWidth;
    // Grid unit length along Z axis
    Scalar UnitLength;

    /*! @brief Default Grid constructor.
     *
     * Default Grid constructor.
     */
    Grid();


public:

    /*! @brief Grid destructor.
     *
     * Grid destructor.
     */
    ~Grid();

    /*! @brief Create a Grid with a given number of half-rows and half-columns
    * and a given grid unit size.
    *
    * Create a grid with a given number of half-rows and half-columns
    * and a given grid unit size.
    *
    * @param[in] HalfRows Number of half-rows
    * @param[in] HalfCols Number of half-columns
    * @param[in] Width Width of each grid unit.
    * @param[in] Length Length of each grid unit.
    *
    * @return Pointer to allocated Grid; NULL if any errors occurred.
    */
    BGE_FACTORY Grid* Create(int HalfRows, int HalfCols, Scalar Width,
                                                        Scalar Length);

}; // Grid

} // bakge

#endif // BAKGE_GRAPHICS_GEOMETRY_GRID_H

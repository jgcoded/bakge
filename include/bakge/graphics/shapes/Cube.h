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
 * @file Cube.h
 * @brief Cube class declaration.
 */

#ifndef BAKGE_GRAPHICS_SHAPES_CUBE_H
#define BAKGE_GRAPHICS_SHAPES_CUBE_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief The Cube is a 3D block shape centered at the origin.
 *
 * The Cube is a 3D block shape centered at the origin. Width, height and
 * length of the Cube are always 1. To draw non-uniformly scaled cube shapes,
 * scale the Pawn bound before drawing the Cube.
 */
class BGE_API Cube : public Mesh
{

protected:

    /*! @brief Protected Cube constructor.
     *
     * Protected Cube constructor.
     */
    Cube();


public:

    /*! @brief Cube destructor.
     *
     * Cube destructor.
     */
    ~Cube();

    /*! @brief Create a new Cube instance.
     *
     * Create a new Cube instance.
     *
     * @return Pointer to allocated Cube; NULL if any errors occurred.
     */
    BGE_FACTORY Cube* Create();

    /*! @brief Get the Cube's dimensions.
     *
     * @param[out] Width Size along the X axis.
     * @param[out] Height Size along the Y axis.
     * @param[out] Length Size along the Z axis.
     *
     * @return Volume of the Cube.
     */
    Scalar GetDimensions(Scalar* Width, Scalar* Height, Scalar* Length) const;

}; /* Cube */

} /* bakge */

#endif /* BAKGE_GRAPHICS_SHAPES_CUBE_H */

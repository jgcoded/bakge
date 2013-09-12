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

#ifndef BAKGE_GRAPHICS_SHAPE_H
#define BAKGE_GRAPHICS_SHAPE_H

#include <bakge/Bakge.h>

namespace bakge
{

enum BGE_SHAPE_STYLE
{
    BGE_SHAPE_STYLE_POINTS = 1,
    BGE_SHAPE_STYLE_WIREFRAME,
    BGE_SHAPE_STYLE_SOLID,
    BGE_SHAPE_STYLE_EDGE
};

/*! @brief Shapes are special mesh objects with configurable dimensions.
 *
 * Shapes' dimensions modifiable at run-time, unlike a typical Mesh whose
 * dimensions are stored in a file and loaded into memory. Shape is simply
 * a base class from which instantiable sub-classes such as Cube or Sphere
 * inherit. Each shape type implements unique interfaces for modifying or
 * accessing its data.
 *
 * @note Future versions may see the removal of the Shape class, as it
 * currently implements functionality which Mesh may implement.
 */
class BGE_API Shape : public Mesh
{

protected:

    GLenum DrawStyle;

    /*! @brief Default Shape constructor.
     *
     * Shape is not explicitly instantiable. Different types of shapes such as
     * cubes and spheres have different interfaces for setting, manipulating
     * and accessing dimension data. As such, only these sub-classes will be
     * able to create new instances through appropriate factory functions.
     */
    Shape();


public:

    /*! @brief Pure-virtual Shape destructor.
     *
     * Pure-virtual Shape destructor.
     */
    virtual ~Shape() = 0;

    /*! @brief Bind the Shape for use in drawing.
     *
     * Bind the Shape for use in drawing.
     *
     * @return BGE_SUCCESS if the shape is ready to be drawn, or BGE_FAILURE
     * if any errors occurred.
     */
    Result Bind() const;

    /*! @brief Unbind the shape.
     *
     * Unbind the shape.
     *
     * @return BGE_SUCCESS if the shape was successfully unbound, or
     * BGE_FAILURE if any errors occurred.
     */
    Result Unbind() const;

    /*! @brief Change the draw mode of the shape
     *
     * Shapes may be drawn in different styles: a point cloud, wireframe mesh
     * or solid mesh.
     *
     * @return BGE_SUCCESS if the shape's draw style was successfully changed,
     * or BGE_FAILURE if any errors occurred.
     */
    Result SetDrawStyle(BGE_SHAPE_STYLE Style);

    /*! @brief Draw the shape.
     *
     * @return BGE_SUCCESS if the shape was successfully drawn, or BGE_FAILURE
     * if any errors occurred.
     */
    virtual Result Draw() const;

}; /* Shape */

} /* bakge */

#endif /* BAKGE_GRAPHICS_SHAPE_H */

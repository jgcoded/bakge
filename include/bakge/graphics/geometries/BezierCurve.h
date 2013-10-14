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
 * @file BezierCurve.h
 * @brief BezierCurve class declaration.
 */

#ifndef BAKGE_GRAPHICS_GEOMETRY_BEZIERCURVE_H
#define BAKGE_GRAPHICS_GEOMETRY_BEZIERCURVE_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief A Bezier curve is rendered using control points.
 *
 * Bezier curves use control points to influence where the curve goes. Each
 * segment follows an arbitrary parabola.
 */
class BGE_API BezierCurve : public Geometry
{
    /*! @brief Default BezierCurve constructor.
     *
     * Default BezierCurve constructor.
     */
    BezierCurve();


public:

    /*! @brief BezierCurve destructor.
     *
     * BezierCurve destructor.
     */
    ~BezierCurve();

    BGE_FACTORY BezierCurve* Create(int NumPoints, Scalar* Points);

}; /* BezierCurve */

} /* bakge */

#endif // BAKGE_GRAPHICS_GEOMETRY_BEZIERCURVE_H

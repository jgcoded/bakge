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
 * segment has an order equal to the number of control points it has. First
 * order segments follow parabolic curves while higher order segments can
 * be much more intricate. The BezierCurve starts out as one large curve
 * segment. Both endpoints are anchors and cannot be converted to control
 * points unless an extra point is appended or prepended as appropriate to
 * take its place. An endpoint can never be a control point, and as such
 * inserting a single point at either end of the line is always an
 * anchor, and the old endpoint becomes a new control point for the segment
 * it was previously anchoring.
 *
 * Bezier curves currently will be used to build LineStrips from with
 * varying levels of accuracy. The more subdivisions used to generate
 * points along the curve, the more smooth and accurate the curve will
 * appear when rendered. This also requires more time to process and
 * create the array, which can take a noticeable length of time when dealing
 * with long curves with any of A) many segments, B) high-order segments,
 * C) high subdivision counts.
 */
class BGE_API BezierCurve : public Geometry
{
    // Highest order segment in the curve, also order of the whole
    int HighOrder;

    // Number of curve segments (section between two anchors)
    int NumSegments;

    // Dynamic array of all points (anchors and control points)
    Vector3* AllPoints;

    // Dynamic array of which points in array are anchors
    int* AnchorIndices;

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

    /*! @brief Create a LineStrip by subdividing along control points,
     * creating a smooth curve.
     *
     * Creates a LineStrip of the BezierCurve with a given number of
     * subdivisions per curve section. The more subdivisions are
     * performed, the smoother the curve and the higher number of
     * points.
     *
     * @param[in] NumSubdivisions Number of subdivisions between control
     *            points.
     *
     * @return Pointer to created LineStrip; NULL if any errors occurred.
     */
    BGE_WUNUSED LineStrip* Build(int NumSubdivisions);

    /*! @brief Combine all segments into one segment spanning the entire
     * curve.
     *
     * Combine all segments into one segment spanning the entire curve. All
     * points between the endpoints of the curve are converted into control
     * points. Calling Build on an amalgamated BezierCurve is unwise, as
     * this can lead to extremely long processing times, particularly when
     * called on curves with a high number of points and with a high number
     * of subdivisions. The suggested use of this is to "reset" the curve
     * and subsequently set certain points to anchors.
     *
     * @return BGE_SUCCESS if the curve was successfully amalgamated;
     * BGE_FAILURE if any errors occurred.
     */
    Result Amalgamate();

    /*! @brief Split up the curve into segments with a given minimum order.
     *
     * Split up the curve into segments with a given minimum order. After
     * separation, all of the curve's segments will be guaranteed to have
     * at minimum number of control points equal to a given value.
     *
     * @return -1 if there are not enough points to create any segments with
     * a minimum order of MinOrder; Otherwise returns the segment index which
     * contains the remaining points which could not made into their own
     * segment and thus were added on to the last created one.
     */
    int Separate(int MinOrder);

}; /* BezierCurve */

} /* bakge */

#endif // BAKGE_GRAPHICS_GEOMETRY_BEZIERCURVE_H

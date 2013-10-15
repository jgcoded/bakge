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

#include <bakge/Bakge.h>
#ifdef _DEBUG
#include <bakge/internal/Debug.h>
#endif // _DEBUG

// Log point/subdivision information when building LineStrip from BezierCurve
#define BGE_BEZIER_VERBOSE_BUILD 1

namespace bakge
{

BezierCurve::BezierCurve()
{
}


BezierCurve::~BezierCurve()
{
}


BezierCurve* BezierCurve::Create(int NumPoints, Scalar* Points)
{
    BezierCurve* B = new BezierCurve;
    if(B == NULL) {
        Log("ERROR: BezierCurve - Couldn't allocate memory.\n");
        return NULL;
    }

#ifdef _DEBUG
    while(glGetError() != GL_NO_ERROR)
        ;
#endif // _DEBUG

    glGenBuffers(1, &B->PointsBuffer);
    glGenBuffers(1, &B->IndicesBuffer);

#ifdef _DEBUG
    if(glGetError() != GL_NO_ERROR) {
        Log("ERROR: BezierCurve - Error allocating control point buffer.\n");
        delete B;
        return NULL;
    }
#endif // _DEBUG

    B->NumPoints = NumPoints;

    glBindBuffer(GL_ARRAY_BUFFER, B->PointsBuffer);
    glBufferData(GL_ARRAY_BUFFER, NumPoints * sizeof(Scalar) * 3, Points,
                                                        GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int* Indices = new int[NumPoints];
    for(int i=0;i<NumPoints;++i)
        Indices[i] = i;

    glBindBuffer(GL_ARRAY_BUFFER, B->IndicesBuffer);
    glBufferData(GL_ARRAY_BUFFER, NumPoints * sizeof(int), Indices,
                                                        GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    delete Indices;

    return B;
}


LineStrip* BezierCurve::Build(int NumSubdivisions)
{
    /* *
     * Each segment has 2 endpoints, but most segments share both points
     * with a neighboring segment. The number of segment "anchor" points
     * is NumSegments + 1.
     *
     * Each segment has one or more control points. NumSubdivisions is
     * equal to the number of points between each segment's anchor points.
     * */

    // So we need NumSubdivisions to be at least 1.
    if(NumSubdivisions < 1) {
        Log("ERROR: BezierCurve - Creating a LineStrip requires > 0 "
                                                    "subdivisions.\n");
        return NULL;
    }

    // TEMPORARY: For now we'll assume it's one segment.
    int NumSegments = 1;

    // Anchor points = NumSegments + 1
    int NumPoints = NumSegments + 1 + NumSubdivisions;

#if defined(_DEBUG) && BGE_BEZIER_VERBOSE_BUILD
    Log("\n");
    Log("BezierCurve: Building LineStrip\n");
    Log("===============================\n");
    Log("%d Subdivisions (Also points per segment).\n", NumSubdivisions);
    Log("%d Segments.\n", NumSegments);
    Log("%d Total points.\n", NumPoints);
    Log("\n");
#endif // defined(_DEBUG)

    // TODO: Fill the array with points

    return NULL;
}

} /* bakge */

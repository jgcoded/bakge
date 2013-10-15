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
    AllPoints = NULL;
    AnchorIndices = NULL;
}


BezierCurve::~BezierCurve()
{
    if(AllPoints != NULL)
        delete[] AllPoints;

    if(AnchorIndices != NULL)
        delete[] AnchorIndices;
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

#ifdef _DEBUG
    if(glGetError() != GL_NO_ERROR) {
        Log("ERROR: BezierCurve - Error allocating control point buffer.\n");
        delete B;
        return NULL;
    }

    while(glGetError() != GL_NO_ERROR)
        ;
#endif // _DEBUG

    glGenBuffers(1, &B->IndicesBuffer);

#ifdef _DEBUG
    if(glGetError() != GL_NO_ERROR) {
        Log("ERROR: BezierCurve - Error allocating indices buffer.\n");
        delete B;
        return NULL;
    }
#endif // _DEBUG

    B->NumPoints = NumPoints;
    // All BezierCurve objects start out amalgamated
    B->NumSegments = 1;
    // Amalgamated curves have 2 anchors; the rest are control points
    B->HighOrder = NumPoints - 2;

    glBindBuffer(GL_ARRAY_BUFFER, B->PointsBuffer);
    glBufferData(GL_ARRAY_BUFFER, NumPoints * sizeof(Scalar) * 3, Points,
                                                        GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Allocate points cache
    B->AllPoints = new Vector3[NumPoints];
    // Indices buffer, for setting GL data store
    int* Indices = new int[NumPoints];

    for(int i=0;i<NumPoints;++i) {
        Indices[i] = i;
        B->AllPoints[i][0] = Points[i * 3 + 0];
        B->AllPoints[i][1] = Points[i * 3 + 1];
        B->AllPoints[i][2] = Points[i * 3 + 2];
    }

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

    Vector3* CurvePoints = new Vector3[NumPoints];
    CurvePoints[0] = AllPoints[0];
    CurvePoints[NumPoints-1] = AllPoints[NumPoints-1];

    Scalar Advance = 1.0f / (NumSubdivisions + 1);

    for(int i=0;i<=NumSubdivisions;++i) {
        GetPointAt(2, &AllPoints[0], &CurvePoints[i+1], Advance * (i+1));
    }

    LineStrip* L = LineStrip::Create(NumPoints, &CurvePoints[0][0]);

    delete[] CurvePoints;

    return L;
}


Result BezierCurve::Amalgamate()
{
    return BGE_FAILURE;
}


int BezierCurve::Separate(int MinOrder)
{
    return -1;
}


void BezierCurve::GetPointAt(int NumControlPoints,
                        const Vector3* SegmentPoints,
                        Vector3* PointsBuffer, Scalar T)
{
#ifdef _DEBUG
    // Courtesy error-checking
    if(NumControlPoints < 1) {
        Log("ERROR: BezierCurve - Cannot generate P(T) with < 1 control "
                                                           "points.\n");
        return;
    }

    if(SegmentPoints == NULL) {
        Log("ERROR: BezierCurve - GetPointAt requires SegmentPoints "
                                                       "!= NULL.\n");
        return;
    }

    if(PointsBuffer == NULL) {
        Log("ERROR: BezierCurve - GetPointAt requires PointsBuffer "
                                                       "!= NULL.\n");
        return;
    }

    if(T < 0 || T > 1.0f) {
        Log("ERROR: BezierCurve - Cannot get point P(t) where t is < 0 "
                                                           "or > 1.\n");
        return;
    }
#endif // _DEBUG

    // Temporaries to store control points (we offset them)
    Vector3 L = SegmentPoints[0];
    Vector3 R = SegmentPoints[1];
    *PointsBuffer = L;

    // Travel T of the way between control points to get the point P(T)
    for(int i=0;i<NumControlPoints;++i) {
        (*PointsBuffer) += (R - L) * T;
        L = (*PointsBuffer);
        R += (SegmentPoints[i+2] - R) * T;
        (*PointsBuffer) += (R - L) * T;
        L = (*PointsBuffer);
    }

#if defined(_DEBUG) && BGE_BEZIER_VERBOSE_BUILD
    Log("BezierCurve: Built point P(%2.2f) = (%2.3f, %2.3f, %2.3f)\n", T,
                                                        (*PointsBuffer)[0],
                                                        (*PointsBuffer)[1],
                                                        (*PointsBuffer)[2]);
#endif // defined(_DEBUG)
}


bool BezierCurve::IsAnchor(int Index) const
{
    return false;
}


bool BezierCurve::IsControl(int Index) const
{
    return !IsAnchor(Index);
}


void BezierCurve::GetPointAt(Scalar T, Vector3* V)
{
}

} /* bakge */

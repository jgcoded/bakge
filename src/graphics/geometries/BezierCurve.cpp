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

namespace bakge
{

BezierCurve::BezierCurve()
{
    ControlPoints = 0;
    Indices = 0;
}


BezierCurve::~BezierCurve()
{
    if(ControlPoints != 0)
        glDeleteBuffers(1, &ControlPoints);

    if(Indices != 0)
        glDeleteBuffers(1, &Indices);
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

    glGenBuffers(1, &B->ControlPoints);
    glGenBuffers(1, &B->Indices);

#ifdef _DEBUG
    if(glGetError() != GL_NO_ERROR) {
        Log("ERROR: BezierCurve - Error allocating control point buffer.\n");
        delete B;
        return NULL;
    }
#endif // _DEBUG

    B->NumControlPoints = NumPoints;

    glBindBuffer(GL_ARRAY_BUFFER, B->ControlPoints);
    glBufferData(GL_ARRAY_BUFFER, NumPoints * sizeof(Scalar) * 3, Points,
                                                        GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int* IndicesBuffer = new int[NumPoints];
    for(int i=0;i<NumPoints;++i)
        IndicesBuffer[i] = i;

    glBindBuffer(GL_ARRAY_BUFFER, B->Indices);
    glBufferData(GL_ARRAY_BUFFER, NumPoints * sizeof(int), IndicesBuffer,
                                                        GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    delete IndicesBuffer;

    return B;
}


Result BezierCurve::Bind() const
{
    GLint Program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0) {
        return BGE_FAILURE;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Indices);

    /* Check each of our attributes' locations to ensure they exist */
    GLint Location = glGetAttribLocation(Program, BGE_VERTEX_ATTRIBUTE);
    if(Location >= 0) {
        glBindBuffer(GL_ARRAY_BUFFER, ControlPoints);
        glEnableVertexAttribArray(Location);
        glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);
#ifdef _DEBUG
    } else {
        WarnMissingAttribute(BGE_VERTEX_ATTRIBUTE);
#endif // _DEBUG
    }

    return BGE_SUCCESS;
}


Result BezierCurve::Unbind() const
{
    GLint Program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0) {
        return BGE_FAILURE;
    }

    GLint Location = glGetAttribLocation(Program, BGE_VERTEX_ATTRIBUTE);
    if(Location >= 0) {
        glDisableVertexAttribArray(Location);
#ifdef _DEBUG
    } else {
        WarnMissingAttribute(BGE_VERTEX_ATTRIBUTE);
#endif // _DEBUG
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result BezierCurve::Draw() const
{
    glDrawElements(GL_LINE_STRIP, NumControlPoints, GL_UNSIGNED_INT,
                                                            (void*)0);

    return BGE_SUCCESS;
}

} /* bakge */

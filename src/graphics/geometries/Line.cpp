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

Line::Line()
{
}


Line::~Line()
{
}


Line* Line::Create(Vector3 A, Vector3 B)
{
    static const GLuint Indices[] = {
        0, 1
    };

    Line* L = new Line;
    if(L == NULL) {
        Log("ERROR: Line - Couldn't allocate memory.\n");
        return NULL;
    }

#ifdef _DEBUG
    while(glGetError() != GL_NO_ERROR)
        ;
#endif // _DEBUG

    glGenBuffers(1, &L->PointsBuffer);

#ifdef _DEBUG
    GLenum Error = glGetError();
    if(Error != GL_NO_ERROR) {
        Log("ERROR: Line - Unexpected error %s while creating points "
                                   "buffer.\n", GetGLErrorName(Error));
        delete L;
        return NULL;
    }
#endif // _DEBUG

#ifdef _DEBUG
    while(glGetError() != GL_NO_ERROR)
        ;
#endif // _DEBUG

    glGenBuffers(1, &L->IndicesBuffer);

#ifdef _DEBUG
    Error = glGetError();
    if(Error != GL_NO_ERROR) {
        Log("ERROR: Line - Unexpected error %s while creating points "
                                   "buffer.\n", GetGLErrorName(Error));
        delete L;
        return NULL;
    }
#endif // _DEBUG

    // Create a temporary buffer
    Scalar* Positions = new Scalar[6];
    if(Positions == NULL) {
        Log("ERROR: Line - Unable to allocate temporary buffer.\n");
        delete L;
        return NULL;
	}

    Positions[0] = A[0];
    Positions[1] = A[1];
    Positions[2] = A[2];
    Positions[3] = B[0];
    Positions[4] = B[1];
    Positions[5] = B[2];

    glBindBuffer(GL_ARRAY_BUFFER, L->PointsBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Scalar) * 6, (GLvoid*)Positions,
                                                       GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, L->IndicesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * 2, (GLvoid*)Indices,
                                                       GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    L->NumPoints = 2;

    delete[] Positions;

    return L;
}

} /* bakge */

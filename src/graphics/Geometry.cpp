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

Geometry::Geometry()
{
    PointsBuffer = 0;
    IndicesBuffer = 0;
    NumPoints = 0;
}


Geometry::~Geometry()
{
    if(PointsBuffer != NULL)
        glDeleteBuffers(1, &PointsBuffer);

    if(IndicesBuffer != NULL)
        glDeleteBuffers(1, &IndicesBuffer);
}


Result Geometry::Draw() const
{
    glDrawElements(GL_LINE_STRIP, NumPoints, GL_UNSIGNED_INT, (void*)0);

    return BGE_FAILURE;
}


Result Geometry::Bind() const
{
    GLint Program;

    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0)
        return BGE_FAILURE;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesBuffer);

    // Set vertex attribute properties
    GLint Location = glGetAttribLocation(Program, BGE_VERTEX_ATTRIBUTE);
    if(Location >= 0) {
        glBindBuffer(GL_ARRAY_BUFFER, PointsBuffer);
        glEnableVertexAttribArray(Location);
        glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);
#ifdef _DEBUG
    } else {
        WarnMissingAttribute(BGE_VERTEX_ATTRIBUTE);
#endif // _DEBUG
    }

    return BGE_SUCCESS;
}


Result Geometry::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLint Program;

    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0)
        return BGE_FAILURE;

    // Disable the bge_Vertex pointer
    GLint Location = glGetAttribLocation(Program, BGE_VERTEX_ATTRIBUTE);
    if(Location >= 0) {
        glDisableVertexAttribArray(Location);
#ifdef _DEBUG
    } else {
        WarnMissingAttribute(BGE_VERTEX_ATTRIBUTE);
#endif // _DEBUG
    }

    return BGE_SUCCESS;
}

} // bakge

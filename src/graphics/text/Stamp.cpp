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

Stamp::Stamp()
{
    Start.X = 0;
    Start.Y = 0;
    Current.X = 0;
    Current.Y = 0;
    Offset.X = 0;
    Offset.Y = 0;
}


Stamp::~Stamp()
{
}


Stamp* Stamp::Create()
{
    static const uint32 Indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    Stamp* St = new Stamp;
    if(St == NULL) {
        Log("ERROR: Stamp - Couldn't allocate memory.\n");
        return NULL;
    }

    St->NumIndices = 6;

    St->SetDimensions(0, 0);

    glGenBuffers(NUM_SHAPE_BUFFERS, &St->ShapeBuffers[0]);

    glBindBuffer(GL_ARRAY_BUFFER, St->ShapeBuffers[SHAPE_BUFFER_INDICES]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uint32) * 6, (GLvoid*)Indices,
                                                        GL_STATIC_DRAW);

    return St;
}


Result Stamp::Pick(const Glyph* G)
{
    Offset.X = G->Offset.X;
    Offset.Y = G->Offset.Y;

    if(SetDimensions(G->Width, G->Height) == BGE_FAILURE) {
        Log("ERROR: Stamp::Pick - Couldn't resize to glyph dimensions.\n");
        return BGE_FAILURE;
    }

    return BGE_SUCCESS;
}


Result Stamp::Bind() const
{
    GLint Program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0) {
        return BGE_FAILURE;
    }

    /* Check each of our attributes' locations to ensure they exist */
    GLint Location = glGetAttribLocation(Program, BGE_VERTEX_ATTRIBUTE);
    if(Location >= 0) {
        glBindBuffer(GL_ARRAY_BUFFER, ShapeBuffers[SHAPE_BUFFER_POSITIONS]);
        glEnableVertexAttribArray(Location);
        glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);
#ifdef _DEBUG
    } else {
        BGE_WARN_MISSING_ATTRIBUTE(BGE_VERTEX_ATTRIBUTE);
#endif // _DEBUG
    }

    return BGE_SUCCESS;
}


Result Stamp::SetDimensions(Scalar Width, Scalar Height)
{
    Scalar X = Current.X + Offset.X;
    Scalar Y = Current.Y + Offset.Y;

    Scalar Positions[] = {
        X, Y, 0,
        X, Y + Height, 0,
        X + Width, Y +Height, 0,
        X + Width, Y, 0,
    };

    this->Width = Width;
    this->Height = Height;

    glBindBuffer(GL_ARRAY_BUFFER, ShapeBuffers[SHAPE_BUFFER_POSITIONS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Scalar) * 12, (GLvoid*)Positions,
                                                            GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}

} // bakge

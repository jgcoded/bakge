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

namespace bakge
{

Rectangle::Rectangle()
{
}


Rectangle::~Rectangle()
{
}


Rectangle* Rectangle::Create(Scalar Width, Scalar Height)
{
    static const Scalar Normals[] = {
        0, 0, +1.0f,
        0, 0, +1.0f,
        0, 0, +1.0f,
        0, 0, +1.0f
    };

    static const unsigned int Indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    static const Scalar TexCoords[] = {
        0, 0,
        0, 1,
        1, 1,
        1, 0
    };

    Rectangle* R = new Rectangle;

    R->NumIndices = 6;
    R->NumFaces = 1;
    R->NumVertices = 4;

    if(R->CreateBuffers() != BGE_SUCCESS) {
        delete R;
        return NULL;
    }

    /* *
     * Allocate buffer space here so SetDimensions doesn't attempt to
     * modify it while unallocated
     * */
    glBindBuffer(GL_ARRAY_BUFFER, R->MeshBuffers[MESH_BUFFER_POSITIONS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Scalar) * 3 * 4, NULL,
                                                GL_DYNAMIC_DRAW);

    R->SetDimensions(Width, Height);

    glBindBuffer(GL_ARRAY_BUFFER, R->MeshBuffers[MESH_BUFFER_NORMALS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * 3 * 4, Normals,
                                                        GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, R->MeshBuffers[MESH_BUFFER_TEXCOORDS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * 8, TexCoords,
                                                        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, R->MeshBuffers[MESH_BUFFER_INDICES]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * 6, Indices,
                                                        GL_STATIC_DRAW);

    R->Unbind();

    R->SetPosition(0, 0, 0);

    return R;
}


Vector4 BGE_NCP Rectangle::SetDimensions(Scalar Width, Scalar Height)
{
    Dimensions[0] = Width;
    Dimensions[1] = Height;

    Scalar Vertices[12];

    Width /= 2;
    Height /= 2;

    Vertices[0] = -Width;
    Vertices[1] = -Height;
    Vertices[2] = 0;
    Vertices[3] = -Width;
    Vertices[4] = +Height;
    Vertices[5] = 0;
    Vertices[6] = +Width;
    Vertices[7] = +Height;
    Vertices[8] = 0;
    Vertices[9] = +Width;
    Vertices[10] = -Height;
    Vertices[11] = 0;

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_POSITIONS]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices[0]) * 12, Vertices);

    Unbind();

    return Dimensions;
}

} /* bakge */

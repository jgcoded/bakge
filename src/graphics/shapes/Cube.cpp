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

Cube::Cube()
{
    Dimensions[0] = 1.0f;
    Dimensions[1] = 1.0f;
    Dimensions[2] = 1.0f;
}


Cube::~Cube()
{
}


Cube* Cube::Create(Scalar Length, Scalar Width, Scalar Height)
{
    static const Scalar Normals[] = {
        0, 0, +1.0f, // A+Z
        0, -1.0f, 0, // A-Y
        -1.0f, 0, 0, // A-X
        0, 0, +1.0f, // B+Z
        0, -1.0f, 0, // B-Y
        +1.0f, 0, 0, // B+X
        0, 0, +1.0f, // C+Z
        0, +1.0f, 0, // C+Y
        +1.0f, 0, 0, // C+X
        0, 0, +1.0f, // D+Z
        0, +1.0f, 0, // D+Y
        -1.0f, 0, 0, // D-X
        0, 0, -1.0f, // E-Z
        0, -1.0f, 0, // E-Y
        -1.0f, 0, 0, // E-X
        0, 0, -1.0f, // F-Z
        0, -1.0f, 0, // F-Y
        +1.0f, 0, 0, // F+X
        0, 0, -1.0f, // G-Z
        0, +1.0f, 0, // G+Y
        +1.0f, 0, 0, // G+X
        0, 0, -1.0f, // H-Z
        0, +1.0f, 0, // H+Y
        -1.0f, 0, 0  // H-X
    };

    static const unsigned int Indices[] = {
        0, 9, 6, // +Z
        0, 3, 6,
        15, 18, 21, // -Z
        15, 12, 21,
        14, 23, 11, // +Y
        14, 2, 11,
        5, 8, 20, // -Y
        5, 17, 20,
        10, 22, 19, // +X
        10, 7, 19,
        1, 13, 16, // -X
        1, 4, 16
    };

    static const Scalar TexCoords[] = {
        0.995f, 0.005f, // A+Z
        0.005f, 0.995f, // A-Y
        0.995f, 0.005f, // A-X
        0.005f, 0.005f, // B+Z
        0.995f, 0.995f, // B-Y
        0.005f, 0.005f, // B+X
        0.005f, 0.995f, // C+Z
        0.995f, 0.005f, // C+Y
        0.005f, 0.995f, // C+X
        0.995f, 0.995f, // D+Z
        0.005f, 0.005f, // D+Y
        0.995f, 0.995f, // D-X
        0.005f, 0.005f, // E-Z
        0.005f, 0.005f, // E-Y
        0.005f, 0.005f, // E-X
        0.995f, 0.005f, // F-Z
        0.995f, 0.005f, // F-Y
        0.995f, 0.005f, // F+X
        0.995f, 0.995f, // G-Z
        0.995f, 0.995f, // G+Y
        0.995f, 0.995f, // G+X
        0.005f, 0.995f, // H-Z
        0.005f, 0.995f, // H+Y
        0.005f, 0.995f  // H-X
    };

    Cube* C = new Cube;

    if(C->CreateBuffers() != BGE_SUCCESS) {
        delete C;
        return NULL;
    }

    /* This sets the positions buffer */
    if(C->SetDimensions(Width, Height, Length) != BGE_SUCCESS) {
        delete C;
        return NULL;
    }

    glBindBuffer(GL_ARRAY_BUFFER, C->MeshBuffers[MESH_BUFFER_NORMALS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * 72, Normals,
                                                        GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, C->MeshBuffers[MESH_BUFFER_TEXCOORDS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * 48, TexCoords,
                                                        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, C->MeshBuffers[MESH_BUFFER_INDICES]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * 36,
                                            Indices, GL_STATIC_DRAW);

    C->Unbind();

    return C;
}


Result Cube::SetDimensions(Scalar X, Scalar Y, Scalar Z)
{
    /* Pass < 0 to leave dimension unchanged */
    if(X < 0)
        X = Dimensions[0];

    if(Y < 0)
        Y = Dimensions[1];

    if(Z < 0)
        Z = Dimensions[2];

    Dimensions = Vector4(X, Y, Z, 0);

    glDeleteBuffers(1, &MeshBuffers[MESH_BUFFER_POSITIONS]);
    glGenBuffers(1, &MeshBuffers[MESH_BUFFER_POSITIONS]);

    /* *
     * A cube has 6 faces, each composed of two triangles.
     * We only need 8 vertices (3 components for each vertex, 24 buffer size)
     * The indices buffer will create our triangles
     * */
    NumTriangles = 12;
    NumVertices = 4 * 6; /* 4 vertices per face */
    NumIndices = 36; /* 2 triangles per face, 3 vertices per triangle */
    Scalar Vertices[72];

    Scalar PosWidth = X / 2;
    Scalar PosHeight = Y / 2;
    Scalar PosLength = Z / 2;
    Scalar NegWidth = -PosWidth;
    Scalar NegHeight = -PosHeight;
    Scalar NegLength = -PosLength;

    /* *
     *       H__________G
     *      /|         /|
     *    D/_|_______C/ |         +Y HEIGHT
     *    |  |       |  |         |            MODEL COORDINATE
     *    |  |       |  |         |
     *    |  |E______|__|F        |_____ +X WIDTH
     *    | /        | /         /
     *    |/_________|/         /
     *    A          B         +Z LENGTH
     *
     * Each of A through H corresponds to 3 separate vertices.
     * They are separate so normals can be constant across each
     * of the cube's faces.
     *
     * e.g. A corresponds to vertices A+Z, A-Y and A-X
     *
     * Texcoords
     *
     * X face: When the face normal is pointing towards you and
     * the Y axis pointing up, texcoords are as follows
     *    BL 0, 0    BR 1, 0
     *    TL 0, 1    TR 1, 1
     *
     * Z face: Same as X face, but mirrored across the t axis
     *    BL 1, 0    BR 0, 0
     *    TL 1, 1    TR 0, 1
     *
     *
     * Y faces:
     *   +Y:
     *     D 0, 0
     *     C 1, 0
     *     H 0, 1
     *     G 1, 1
     *
     *   -Y:
     *     E 0, 0
     *     F 1, 0
     *     A 0, 1
     *     B 1, 1
     * */

    /* A+Z */
    Vertices[0] = NegWidth;
    Vertices[1] = NegHeight;
    Vertices[2] = PosLength;
    /* A-Y */
    Vertices[3] = NegWidth;
    Vertices[4] = NegHeight;
    Vertices[5] = PosLength;
    /* A-X */
    Vertices[6] = NegWidth;
    Vertices[7] = NegHeight;
    Vertices[8] = PosLength;

    /* B+Z */
    Vertices[9] = PosWidth;
    Vertices[10] = NegHeight;
    Vertices[11] = PosLength;
    /* B-Y */
    Vertices[12] = PosWidth;
    Vertices[13] = NegHeight;
    Vertices[14] = PosLength;
    /* B+X */
    Vertices[15] = PosWidth;
    Vertices[16] = NegHeight;
    Vertices[17] = PosLength;

    /* C+Z */
    Vertices[18] = PosWidth;
    Vertices[19] = PosHeight;
    Vertices[20] = PosLength;
    /* C+Y */
    Vertices[21] = PosWidth;
    Vertices[22] = PosHeight;
    Vertices[23] = PosLength;
    /* C+X */
    Vertices[24] = PosWidth;
    Vertices[25] = PosHeight;
    Vertices[26] = PosLength;

    /* D+Z */
    Vertices[27] = NegWidth;
    Vertices[28] = PosHeight;
    Vertices[29] = PosLength;
    /* D+Y */
    Vertices[30] = NegWidth;
    Vertices[31] = PosHeight;
    Vertices[32] = PosLength;
    /* D-X */
    Vertices[33] = NegWidth;
    Vertices[34] = PosHeight;
    Vertices[35] = PosLength;

    /* E-Z */
    Vertices[36] = NegWidth;
    Vertices[37] = NegHeight;
    Vertices[38] = NegLength;
    /* E-Y */
    Vertices[39] = NegWidth;
    Vertices[40] = NegHeight;
    Vertices[41] = NegLength;
    /* E-X */
    Vertices[42] = NegWidth;
    Vertices[43] = NegHeight;
    Vertices[44] = NegLength;

    /* F-Z */
    Vertices[45] = PosWidth;
    Vertices[46] = NegHeight;
    Vertices[47] = NegLength;
    /* F-Y */
    Vertices[48] = PosWidth;
    Vertices[49] = NegHeight;
    Vertices[50] = NegLength;
    /* F+X */
    Vertices[51] = PosWidth;
    Vertices[52] = NegHeight;
    Vertices[53] = NegLength;

    /* G-Z */
    Vertices[54] = PosWidth;
    Vertices[55] = PosHeight;
    Vertices[56] = NegLength;
    /* G+Y */
    Vertices[57] = PosWidth;
    Vertices[58] = PosHeight;
    Vertices[59] = NegLength;
    /* G+X */
    Vertices[60] = PosWidth;
    Vertices[61] = PosHeight;
    Vertices[62] = NegLength;

    /* H-Z */
    Vertices[63] = NegWidth;
    Vertices[64] = PosHeight;
    Vertices[65] = NegLength;
    /* H+Y */
    Vertices[66] = NegWidth;
    Vertices[67] = PosHeight;
    Vertices[68] = NegLength;
    /* H-X */
    Vertices[69] = NegWidth;
    Vertices[70] = PosHeight;
    Vertices[71] = NegLength;

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_POSITIONS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * 72, Vertices,
                                                        GL_STATIC_DRAW);

    Unbind();

    return BGE_SUCCESS;
}

} /* bakge */

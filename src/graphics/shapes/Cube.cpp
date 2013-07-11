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
    Cube* C = new Cube;

    if(C->CreateBuffers() != BGE_SUCCESS) {
        delete C;
        return NULL;
    }

    glBindVertexArray(C->MeshVAO);

    printf("MeshVAO at %d\n", C->MeshVAO);

    /* *
     * A cube has 6 faces, each composed of two triangles.
     * We only need 8 vertices (3 components for each vertex, 24 buffer size)
     * The indices buffer will create our triangles
     * */
    Scalar Vertices[24];
    unsigned int Indices[36];

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
     * Vertices array indices
     * 0 A: ( 0,  1,  2)
     * 1 B: ( 3,  4,  5)
     * 2 C: ( 6,  7,  8)
     * 3 D: ( 9, 10, 11)
     * 4 E: (12, 13, 14)
     * 5 F: (15, 16, 17)
     * 6 G: (18, 19, 20)
     * 7 H: (21, 22, 23)
     *
     * Triangles
     * +Z FACE: ADC, ABC
     * -Z FACE: FGH, FEH
     * -X FACE: EHD, EAD
     * +X FACE: BCG, BFG
     * +Y FACE: DHG, DCG
     * -Y FACE: EAB, EFB
     * */

    /* *
     * Convenience. Dimensions are full edge measurements and the cube is
     * formed around the origin (0, 0, 0) anyways
     * */
    Width /= 2;
    Length /= 2;
    Height /= 2;

    /* +Z */
    Indices[0] = 0;
    Indices[1] = 3;
    Indices[2] = 2;
    Indices[3] = 0;
    Indices[4] = 1;
    Indices[5] = 2;

    /* -Z */
    Indices[6] = 5;
    Indices[7] = 6;
    Indices[8] = 7;
    Indices[9] = 5;
    Indices[10] = 4;
    Indices[11] = 7;

    /* -X */
    Indices[12] = 4;
    Indices[13] = 7;
    Indices[14] = 3;
    Indices[15] = 4;
    Indices[16] = 0;
    Indices[17] = 7;

    /* +X */
    Indices[18] = 1;
    Indices[19] = 2;
    Indices[20] = 6;
    Indices[21] = 1;
    Indices[22] = 5;
    Indices[23] = 6;

    /* +Y */
    Indices[24] = 3;
    Indices[25] = 7;
    Indices[26] = 6;
    Indices[27] = 3;
    Indices[28] = 2;
    Indices[29] = 6;

    /* -Y */
    Indices[30] = 4;
    Indices[31] = 0;
    Indices[32] = 1;
    Indices[33] = 4;
    Indices[34] = 5;
    Indices[35] = 1;

    /* A */
    Vertices[0] = -Width;
    Vertices[1] = -Height;
    Vertices[2] = +Length;

    /* B */
    Vertices[3] = +Width;
    Vertices[4] = -Height;
    Vertices[5] = +Length;

    /* C */
    Vertices[6] = +Width;
    Vertices[7] = +Height;
    Vertices[8] = +Length;

    /* D */
    Vertices[9] = -Width;
    Vertices[10] = +Height;
    Vertices[11] = +Length;

    /* E */
    Vertices[12] = -Width;
    Vertices[13] = -Height;
    Vertices[14] = -Length;

    /* F */
    Vertices[15] = +Width;
    Vertices[16] = -Height;
    Vertices[17] = -Length;

    /* G */
    Vertices[18] = +Width;
    Vertices[19] = +Height;
    Vertices[20] = -Length;

    /* H */
    Vertices[21] = -Width;
    Vertices[22] = +Height;
    Vertices[23] = -Length;

    glBindBuffer(GL_ARRAY_BUFFER, C->MeshBuffers[MESH_BUFFER_POSITIONS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * 24, Vertices,
                                                        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, C->MeshBuffers[MESH_BUFFER_INDICES]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * 36,
                                            Indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    return C;
}


Result Cube::Draw() const
{
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);

    return BGE_SUCCESS;
}

} /* bakge */

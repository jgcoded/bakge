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

Mesh::Mesh()
{
    MeshVAO = 0;
    MeshBuffers[0] = 0;
}


Mesh::~Mesh()
{
}


Result Mesh::Bind() const
{
    GLint Program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);

    GLint PositionsAttrib = glGetAttribLocation(Program, BGE_VERTEX_ATTRIBUTE);
    GLint NormalsAttrib = glGetAttribLocation(Program, BGE_NORMAL_ATTRIBUTE);
    GLint TexCoordsAttrib = glGetAttribLocation(Program, BGE_TEXCOORD_ATTRIBUTE);
    if(TexCoordsAttrib < 0)
        printf("Attribute %s not found!\n", BGE_TEXCOORD_ATTRIBUTE);

    glBindVertexArray(MeshVAO);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_POSITIONS]);
    glEnableVertexAttribArray(PositionsAttrib);
    glVertexAttribPointer(PositionsAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_TEXCOORDS]);
    glEnableVertexAttribArray(TexCoordsAttrib);
    glVertexAttribPointer(TexCoordsAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_NORMALS]);
    glEnableVertexAttribArray(NormalsAttrib);
    glVertexAttribPointer(NormalsAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    return BGE_SUCCESS;
}


Result Mesh::Unbind() const
{
    glBindVertexArray(0);

    return BGE_SUCCESS;
}


Result Mesh::CreateBuffers()
{
    /* If data already exists clear it */
    if(MeshVAO != 0) {
        ClearBuffers();
    }

    glGenVertexArrays(1, &MeshVAO);
    glBindVertexArray(MeshVAO);
    glGenBuffers(NUM_MESH_BUFFERS, MeshBuffers);

    return BGE_SUCCESS;
}


Result Mesh::ClearBuffers()
{
    glDeleteVertexArrays(1, &MeshVAO);
    MeshVAO = 0;

    glDeleteBuffers(NUM_MESH_BUFFERS, MeshBuffers);
    MeshBuffers[0] = 0;

    return BGE_SUCCESS;
}

} /* bakge */

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
    NumVertices = 0;
    NumTriangles = 0;
    NumIndices = 0;
    memset((void*)MeshBuffers, 0, sizeof(GLuint) * NUM_MESH_BUFFERS);
}


Mesh::~Mesh()
{
    ClearBuffers();
}


Result Mesh::Bind() const
{
    Result Errors = BGE_SUCCESS;

    if(BindBuffers() == BGE_FAILURE)
        Errors = BGE_FAILURE;

    return Errors;
}


Result Mesh::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Mesh::BindBuffers() const
{
    GLint Program = -1;
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);

#ifdef DEBUG
    if(Program < 0) {
        printf("Unable to find current shader\n");
        return BGE_FAILURE;
    }
#endif /* _DEBUG */

    GLint PositionsAttrib = glGetAttribLocation(Program, BGE_VERTEX_ATTRIBUTE);
    GLint NormalsAttrib = glGetAttribLocation(Program, BGE_NORMAL_ATTRIBUTE);
    GLint TexCoordsAttrib = glGetAttribLocation(Program, BGE_TEXCOORD_ATTRIBUTE);

#ifdef _DEBUG
    /* Check each of our attributes' locations to ensure they exist */
    if(PositionsAttrib < 0) {
        printf("Unable to locate attribute %s in current shader\n",
                                                BGE_VERTEX_ATTRIBUTE);
        return BGE_FAILURE;
    }
    if(NormalsAttrib < 0) {
        printf("Unable to locate attribute %s in current shader\n",
                                                BGE_NORMAL_ATTRIBUTE);
        return BGE_FAILURE;
    }
    if(TexCoordsAttrib < 0) {
        printf("Unable to locate attribute %s in current shader\n",
                                                BGE_TEXCOORD_ATTRIBUTE);
        return BGE_FAILURE;
    }
#endif /* _DEBUG */

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_POSITIONS]);
    glEnableVertexAttribArray(PositionsAttrib);
    glVertexAttribPointer(PositionsAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_TEXCOORDS]);
    glEnableVertexAttribArray(TexCoordsAttrib);
    glVertexAttribPointer(TexCoordsAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_NORMALS]);
    glEnableVertexAttribArray(NormalsAttrib);
    glVertexAttribPointer(NormalsAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_INDICES]);

    return BGE_SUCCESS;
}


Result Mesh::CreateBuffers()
{
    /* If data already exists clear it */
    ClearBuffers();

    glGenBuffers(NUM_MESH_BUFFERS, MeshBuffers);

#ifdef _DEBUG
    /* Check to make sure each of our mesh's buffers was created properly */
    if(MeshBuffers[MESH_BUFFER_POSITIONS] == 0) {
        printf("Error creating positions buffer\n");
        return BGE_FAILURE;
    }

    if(MeshBuffers[MESH_BUFFER_NORMALS] == 0) {
        printf("Error creating normals buffer\n");
        return BGE_FAILURE;
    }

    if(MeshBuffers[MESH_BUFFER_TEXCOORDS] == 0) {
        printf("Error creating texture coordinates buffer\n");
        return BGE_FAILURE;
    }

    if(MeshBuffers[MESH_BUFFER_INDICES] == 0) {
        printf("Error creating triangle indices buffer\n");
        return BGE_FAILURE;
    }
#endif /* _DEBUG */

    return BGE_SUCCESS;
}


Result Mesh::ClearBuffers()
{
    if(MeshBuffers[0] != 0) {
        glDeleteBuffers(NUM_MESH_BUFFERS, MeshBuffers);
        memset((void*)MeshBuffers, 0, sizeof(GLuint) * NUM_MESH_BUFFERS);
    }

    return BGE_SUCCESS;
}


Result Mesh::DrawInstanced(int Count) const
{
    glDrawElementsInstancedBaseVertex(GL_TRIANGLES, NumIndices,
                            GL_UNSIGNED_INT, (void*)0, Count, 0);

    return BGE_SUCCESS;
}


Result Mesh::PositionData(int NumPositions, Scalar* Data)
{
    if(MeshBuffers[MESH_BUFFER_POSITIONS] == 0)
        return BGE_FAILURE;

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_POSITIONS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Scalar) * NumPositions * 3,
                                            (const GLvoid*)Data,
                                                GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Mesh::NormalData(int NumNormals, Scalar* Data)
{
    if(MeshBuffers[MESH_BUFFER_NORMALS] == 0)
        return BGE_FAILURE;

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_NORMALS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Scalar) * NumNormals * 3,
                                            (const GLvoid*)Data,
                                                GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Mesh::IndexData(int NumIndices, int* Data)
{
    if(MeshBuffers[MESH_BUFFER_INDICES] == 0)
        return BGE_FAILURE;

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_INDICES]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * NumIndices * 3,
                                            (const GLvoid*)Data,
                                                GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Mesh::TexCoordData(int NumTexCoords, Scalar* Data)
{
    if(MeshBuffers[MESH_BUFFER_TEXCOORDS] == 0)
        return BGE_FAILURE;

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_TEXCOORDS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Scalar) * NumTexCoords * 2,
                                                (const GLvoid*)Data,
                                                    GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}

} /* bakge */

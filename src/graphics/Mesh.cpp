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

Mesh::Mesh()
{
    NumVertices = 0;
    NumTriangles = 0;
    memset((void*)MeshBuffers, 0, sizeof(GLuint) * NUM_MESH_BUFFERS);

    Positions = NULL;
    Normals = NULL;
    TexCoords = NULL;
    Indices = NULL;
}


Mesh::~Mesh()
{
    ClearBuffers();

    if(Positions != NULL)
        free(Positions);

    if(Normals != NULL)
        free(Normals);

    if(TexCoords != NULL)
        free(TexCoords);

    if(Indices != NULL)
        free(Indices);
}


Result Mesh::Bind() const
{
    GLint Program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0) {
        return BGE_FAILURE;
    }

    /* Check each of our attributes' locations to ensure they exist */
    GLint Location = glGetAttribLocation(Program, BGE_VERTEX_ATTRIBUTE);
    if(Location >= 0) {
        glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_POSITIONS]);
        glEnableVertexAttribArray(Location);
        glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    } else {
        WarnMissingAttribute(BGE_VERTEX_ATTRIBUTE);
    }

    Location = glGetAttribLocation(Program, BGE_NORMAL_ATTRIBUTE);
    if(Location >= 0) {
        glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_NORMALS]);
        glEnableVertexAttribArray(Location);
        glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    } else {
        WarnMissingAttribute(BGE_NORMAL_ATTRIBUTE);
    }

    Location = glGetAttribLocation(Program, BGE_TEXCOORD_ATTRIBUTE);
    if(Location >= 0) {
        glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_TEXCOORDS]);
        glEnableVertexAttribArray(Location);
        glVertexAttribPointer(Location, 2, GL_FLOAT, GL_FALSE, 0, 0);
    } else {
        WarnMissingAttribute(BGE_TEXCOORD_ATTRIBUTE);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_INDICES]);

    return BGE_SUCCESS;
}


Result Mesh::Unbind() const
{
    GLint Program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0) {
        return BGE_FAILURE;
    }

    GLint Location = glGetAttribLocation(Program, BGE_VERTEX_ATTRIBUTE);
    if(Location < 0) {
        WarnMissingAttribute(BGE_VERTEX_ATTRIBUTE);
    } else {
        glDisableVertexAttribArray(Location);
    }

    Location = glGetAttribLocation(Program, BGE_NORMAL_ATTRIBUTE);
    if(Location < 0) {
        WarnMissingAttribute(BGE_NORMAL_ATTRIBUTE);
    } else {
        glDisableVertexAttribArray(Location);
    }

    Location = glGetAttribLocation(Program, BGE_TEXCOORD_ATTRIBUTE);
    if(Location < 0) {
        WarnMissingAttribute(BGE_TEXCOORD_ATTRIBUTE);
    } else {
        glDisableVertexAttribArray(Location);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
        Log("ERROR: Mesh - Couldn't create positions buffer\n");
        return BGE_FAILURE;
    }

    if(MeshBuffers[MESH_BUFFER_NORMALS] == 0) {
        Log("ERROR: Mesh - Couldn't create normals buffer\n");
        return BGE_FAILURE;
    }

    if(MeshBuffers[MESH_BUFFER_TEXCOORDS] == 0) {
        Log("ERROR: Mesh - Couldn't create texture coordinates buffer\n");
        return BGE_FAILURE;
    }

    if(MeshBuffers[MESH_BUFFER_INDICES] == 0) {
        Log("ERROR: Mesh - Couldn't create indices buffer\n");
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
    glDrawElementsInstancedBaseVertex(GL_TRIANGLES, NumTriangles * 3,
                            GL_UNSIGNED_INT, (void*)0, Count, 0);

    return BGE_SUCCESS;
}


Result Mesh::SetPositionData(int NumPositions, const Scalar* Data)
{
    if(MeshBuffers[MESH_BUFFER_POSITIONS] == 0)
        return BGE_FAILURE;

    NumVertices = NumPositions;

    if(Positions != NULL)
        free(Positions);

    size_t Size = sizeof(Scalar) * 3 * NumVertices;

    Positions = (Scalar*)malloc(Size);
    memcpy((void*)Positions, (const void*)Data, Size);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_POSITIONS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Scalar) * NumPositions * 3,
                                            (const GLvoid*)Data,
                                                GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Mesh::SetNormalData(int NumNormals, const Scalar* Data)
{
    if(MeshBuffers[MESH_BUFFER_NORMALS] == 0)
        return BGE_FAILURE;

    if(Normals != NULL)
        free(Normals);

    size_t Size = sizeof(Scalar) * 3 * NumVertices;

    Normals = (Scalar*)malloc(Size);
    memcpy((void*)Normals, (const void*)Data, Size);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_NORMALS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Scalar) * NumNormals * 3,
                                            (const GLvoid*)Data,
                                                GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Mesh::SetIndexData(int NumTriangles, const int* Data)
{
    if(MeshBuffers[MESH_BUFFER_INDICES] == 0)
        return BGE_FAILURE;

    if(Indices != NULL)
        free(Indices);

    this->NumTriangles = NumTriangles;

    size_t Size = sizeof(int) * 3 * NumVertices;

    Indices = (int*)malloc(Size);
    memcpy((void*)Indices, (const void*)Data, Size);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_INDICES]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * NumTriangles * 3,
                                            (const GLvoid*)Data,
                                                GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Mesh::SetTexCoordData(int NumTexCoords, const Scalar* Data)
{
    if(MeshBuffers[MESH_BUFFER_TEXCOORDS] == 0)
        return BGE_FAILURE;

    if(TexCoords != NULL)
        free(TexCoords);

    size_t Size = sizeof(Scalar) * 2 * NumVertices;

    TexCoords = (Scalar*)malloc(Size);
    memcpy((void*)TexCoords, (const void*)Data, Size);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_TEXCOORDS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Scalar) * NumTexCoords * 2,
                                                (const GLvoid*)Data,
                                                    GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Mesh::SetDrawStyle(MESH_DRAW_STYLE Style)
{
    switch(Style) {

    case MESH_DRAW_STYLE_SOLID:
        DrawStyle = GL_TRIANGLES;
        break;

    case MESH_DRAW_STYLE_WIREFRAME:
        DrawStyle = GL_LINE_LOOP;
        break;

    case MESH_DRAW_STYLE_POINTS:
        DrawStyle = GL_POINTS;
        break;

    default:
        return BGE_FAILURE;
    }

    return BGE_SUCCESS;
}


Result Mesh::Draw() const
{
    glDrawElements(DrawStyle, NumTriangles * 3, GL_UNSIGNED_INT, (GLvoid*)0);

    return BGE_SUCCESS;
}

} /* bakge */

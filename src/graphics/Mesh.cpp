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
#include <bakge/internal/Format.h>
#ifdef _DEBUG
#include <bakge/internal/Debug.h>
#endif // _DEBUG

namespace bakge
{

Mesh::Mesh()
{
    NumVertices = 0;
    NumIndices = 0;
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


Result Mesh::Encode100(const char* Path)
{
    BeginLogBlock();

    PHYSFS_file* F = PHYSFS_openWrite(Path);
    if(F == NULL) {
        Log("ERROR: Mesh::Encode100() - Unable to open \"%s\" for writing.\n",
                                                                        Path);
        EndLogBlock();
        return BGE_FAILURE;
    }

    bmf::layout100::Header H;
    strcpy((char*)(&H.FormatName), BGE_BMF_NAME);
    H.Type = 0;
    H.Major = 1;
    H.Minor = 0;
    H.Revision = 0;

    if(PHYSFS_write(F, (void*)&H, sizeof(H), 1) < 1) {
        Log("ERROR: Mesh::Encode100() - Error writing file header.\n");
        PHYSFS_close(F);
        EndLogBlock();
        return BGE_FAILURE;
    }

    int Num = GetNumVertices();

    if(PHYSFS_write(F, (void*)&Num, sizeof(Num), 1) < 1) {
        Log("ERROR: Mesh::Encode100() - Error writing vertex metadatum.\n");
        PHYSFS_close(F);
        EndLogBlock();
        return BGE_FAILURE;
    }

    if(PHYSFS_write(F, (void*)GetPositionData(), sizeof(Scalar) * 3, Num) < Num) {
        Log("ERROR: Mesh::Encode100() - Error writing vertex position data "
                                                                "segment.\n");
        PHYSFS_close(F);
        EndLogBlock();
        return BGE_FAILURE;
    }

    if(PHYSFS_write(F, (void*)GetNormalData(), sizeof(Scalar) * 3, Num) < Num) {
        Log("ERROR: Mesh::Encode100() - Error writing vertex normals data "
                                                                "segment.\n");
        PHYSFS_close(F);
        EndLogBlock();
        return BGE_FAILURE;
    }

    if(PHYSFS_write(F, (void*)GetTexCoordData(), sizeof(Scalar) * 2, Num) < Num) {
        Log("ERROR: Mesh::Encode100() - Error writing vertex texcoords data "
                                                                "segment.\n");
        PHYSFS_close(F);
        EndLogBlock();
        return BGE_FAILURE;
    }

    Num = GetNumIndices();

    if(PHYSFS_write(F, (void*)&Num, sizeof(Num), 1) < 1) {
        Log("ERROR: Mesh::Encode100() - Error writing triangles metadatum.\n");
        PHYSFS_close(F);
        EndLogBlock();
        return BGE_FAILURE;
    }

    if(PHYSFS_write(F, (void*)GetIndexData(), sizeof(int), Num) < Num) {
        Log("ERROR: Mesh::Encode100() - Error writing triangle indices data "
                                                                "segment.\n");
        PHYSFS_close(F);
        EndLogBlock();
        return BGE_FAILURE;
    }

    PHYSFS_close(F);

    EndLogBlock();

    return BGE_SUCCESS;
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
#ifdef _DEBUG
    } else {
        BGE_WARN_MISSING_ATTRIBUTE(BGE_VERTEX_ATTRIBUTE);
#endif // _DEBUG
    }

    Location = glGetAttribLocation(Program, BGE_NORMAL_ATTRIBUTE);
    if(Location >= 0) {
        glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_NORMALS]);
        glEnableVertexAttribArray(Location);
        glVertexAttribPointer(Location, 3, GL_FLOAT, GL_FALSE, 0, 0);
#ifdef _DEBUG
    } else {
        BGE_WARN_MISSING_ATTRIBUTE(BGE_NORMAL_ATTRIBUTE);
#endif // _DEBUG
    }

    Location = glGetAttribLocation(Program, BGE_TEXCOORD_ATTRIBUTE);
    if(Location >= 0) {
        glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_TEXCOORDS]);
        glEnableVertexAttribArray(Location);
        glVertexAttribPointer(Location, 2, GL_FLOAT, GL_FALSE, 0, 0);
#ifdef _DEBUG
    } else {
        BGE_WARN_MISSING_ATTRIBUTE(BGE_TEXCOORD_ATTRIBUTE);
#endif // _DEBUG
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
    if(Location >= 0) {
        glDisableVertexAttribArray(Location);
#ifdef _DEBUG
    } else {
        BGE_WARN_MISSING_ATTRIBUTE(BGE_VERTEX_ATTRIBUTE);
#endif // _DEBUG
    }

    Location = glGetAttribLocation(Program, BGE_NORMAL_ATTRIBUTE);
    if(Location >= 0) {
        glDisableVertexAttribArray(Location);
#ifdef _DEBUG
    } else {
        BGE_WARN_MISSING_ATTRIBUTE(BGE_VERTEX_ATTRIBUTE);
#endif // _DEBUG
    }

    Location = glGetAttribLocation(Program, BGE_TEXCOORD_ATTRIBUTE);
    if(Location >= 0) {
        glDisableVertexAttribArray(Location);
#ifdef _DEBUG
    } else {
        BGE_WARN_MISSING_ATTRIBUTE(BGE_VERTEX_ATTRIBUTE);
#endif // _DEBUG
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
    glDrawElementsInstancedBaseVertex(GL_TRIANGLES, NumIndices,
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


Result Mesh::SetIndexData(int NumIndices, const int* Data)
{
    if(MeshBuffers[MESH_BUFFER_INDICES] == 0)
        return BGE_FAILURE;

    if(Indices != NULL)
        free(Indices);

    this->NumIndices = NumIndices;

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
    glDrawElements(DrawStyle, NumIndices, GL_UNSIGNED_INT, (GLvoid*)0);

    return BGE_SUCCESS;
}

} /* bakge */

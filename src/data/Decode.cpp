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

namespace bakge
{

namespace bmf
{

struct v100
{
    PHYSFS_file* F;
    // Cache number of vertices and triangles in the mesh
    uint32 NumVertices;
    uint32 NumTriangles;
    // File offsets of various vertex data
    uint64 PositionsOffset;
    uint64 NormalsOffset;
    uint64 TexCoordsOffset;
    uint64 TrianglesOffset;
};

} // bmf

Result DecodeImageFile(const char* FilePath, Byte** Data)
{
    return BGE_FAILURE;
}


bmf::v100* OpenMeshFile100(const char* Path)
{
    BeginLogBlock();

    Log("OpenMeshFile100() - Verifying file \"%s\"...\n", Path);

    if(PHYSFS_exists(Path) == 0) {
        Log("ERROR: OpenMeshFile100() - File \"%s\" does not exist.\n",
                                                                Path);
        EndLogBlock();
        return NULL;
    }

    if(PHYSFS_isDirectory(Path) != 0) {
        Log("ERROR: OpenMeshFile100() - \"%s\" is a directory.\n", Path);
        EndLogBlock();
        return NULL;
    }

    Log("OpenMeshFile100() - Verified \"%s\"; opening to read.\n", Path);

    PHYSFS_file* MeshFile = PHYSFS_openRead(Path);
    if(MeshFile == NULL) {
        Log("ERROR: OpenMeshFile100() - Error while opening file \"%s\".\n",
                                                                      Path);
        EndLogBlock();
        return NULL;
    }

    bmf::v100* Handle = new bmf::v100;
    if(Handle == NULL) {
        Log("ERROR: OpenMeshFile100() - Couldn't allocate memory.\n");
        PHYSFS_close(MeshFile);
        EndLogBlock();
        return NULL;
    }

    Log("OpenMeshFile100() - Opened \"%s\"; verifying format and version...",
                                                                     Path);

    bmf::layout100::Header H;

    if(PHYSFS_read(MeshFile, (void*)&H, sizeof(H), 1) < 1) {
        Log("ERROR: OpenMeshFile100() - Error scanning file header.\n");
        PHYSFS_close(MeshFile);
        EndLogBlock();
        return NULL;
    }

    // Make sure name string is correct
    if(strncmp(BGE_BMF_NAME, H.FormatName, 32) != 0) {
        Log("ERROR: OpenMeshFile100() - \"%s\" is not a valid Bakge Mesh "
                                                          "File.\n", Path);
        PHYSFS_close(MeshFile);
        EndLogBlock();
        return NULL;
    }

    Log("OpenMeshFile100() - Verified Bakge Mesh File v%d.%d.%d \"%s\"",
                                                      H.Major, H.Minor,
                                                      H.Revision, Path);

    PHYSFS_uint64 Offset = sizeof(bmf::layout100::Header);

    PHYSFS_sint64 ReadObj = PHYSFS_read(MeshFile,
                    (void*)(&Handle->NumVertices),
                               sizeof(uint32), 1);
    if(ReadObj < 1) {
        Log("ERROR: OpenMeshFile100() - Error reading vertex metadatum.\n");
        PHYSFS_close(MeshFile);
        delete Handle;
        EndLogBlock();
        return NULL;
    }

    Log("OpenMeshFile100() - Found vertex metadatum at offset 0x%x\n",
                                                                Offset);

    // Reading advances file offset
    Offset += sizeof(uint32);

    Log("OpenMeshFile100() - Setting vertex data segment offsets...\n");

    Handle->PositionsOffset = Offset;
    Log("  - Vertex positions at offset  0x%0x\n", Offset);
    // Advance past positions
    Offset += sizeof(Scalar) * 3 * Handle->NumVertices;

    Handle->NormalsOffset = Offset;
    Log("  - Vertex normals at offset    0x%0x\n", Offset);
    // Advance past normals
    Offset += sizeof(Scalar) * 3 * Handle->NumVertices;

    Handle->TexCoordsOffset = Offset;
    Log("  - Vertex texcoords at offset  0x%0x\n", Offset);
    // Advance past texcoords
    Offset += sizeof(Scalar) * 2 * Handle->NumVertices;

    if(PHYSFS_seek(MeshFile, Offset) == 0) {
        Log("ERROR: OpenMeshFile100() - Error seeking triangle metadatum.\n");
        PHYSFS_close(MeshFile);
        delete Handle;
        EndLogBlock();
        return NULL;
    }

    ReadObj = PHYSFS_read(MeshFile, (void*)(&Handle->NumTriangles),
                                                sizeof(uint32), 1);
    if(ReadObj < 1) {
        Log("ERROR: OpenMeshFile100() - Error reading triangle metadatum.\n");
        PHYSFS_close(MeshFile);
        delete Handle;
        EndLogBlock();
        return NULL;
    }

    Log("OpenMeshFile100() - Found triangle metadatum at offset 0x%x\n",
                                                                Offset);

    Offset += sizeof(uint32);

    Log("OpenMeshFile100() - Setting triangle data segment offset...\n");

    Handle->TrianglesOffset = Offset;
    Log("  - Triangle indices at offset  0x%0x\n", Offset);

    Log("OpenMeshFile100() - Successfully opened and scanned mesh file "
                                                        "\"%s\".", Path);

    EndLogBlock();

    return Handle;
}


Result CloseMeshFile100(bmf::v100* Handle)
{
    if(PHYSFS_close(Handle->F) == 0) {
        Log("ERROR: CloseMeshFile100() - Error closing mesh file handle.\n");
        return BGE_FAILURE;
    }

    return BGE_SUCCESS;
}


Result GetNumVertices(bmf::v100* Handle, uint32* Num)
{
#ifdef _DEBUG
    if(Handle == NULL) {
        Log("ERROR: GetNumVertices() - Passed NULL bmf::v100*\n");
        return BGE_FAILURE;
    }

    if(Num == NULL) {
        Log("ERROR: GetNumVertices() - Passed NULL uint32*\n");
        return BGE_FAILURE;
    }
#endif // _DEBUG

    *Num = Handle->NumVertices;

    return BGE_SUCCESS;
}


Result GetNumTriangles(bmf::v100* Handle, uint32* Num)
{
#ifdef _DEBUG
    if(Handle == NULL) {
        Log("ERROR: GetNumTriangles() - Passed NULL bmf::v100*\n");
        return BGE_FAILURE;
    }

    if(Num == NULL) {
        Log("ERROR: GetNumTriangles() - Passed NULL uint32*\n");
        return BGE_FAILURE;
    }
#endif // _DEBUG

    *Num = Handle->NumTriangles;

    return BGE_SUCCESS;
}

} /* bakge */

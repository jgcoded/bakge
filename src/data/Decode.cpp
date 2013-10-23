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
    bmf::v100* Handle = new bmf::v100;
    if(Handle == NULL) {
        Log("ERROR: OpenMeshFile100() - Couldn't allocate memory.\n");
        return NULL;
    }

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


int GetNumVertices(bmf::v100* Handle, uint32* Num)
{
    return 0;
}


int GetNumTriangles(bmf::v100* Handle, uint32* Num)
{
    return 0;
}

} /* bakge */

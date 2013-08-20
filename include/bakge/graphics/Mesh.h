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

#ifndef BAKGE_GRAPHICS_MESH_H
#define BAKGE_GRAPHICS_MESH_H

#include <bakge/Bakge.h>

namespace bakge
{

enum MESH_BUFFERS
{
    MESH_BUFFER_POSITIONS = 0,
    MESH_BUFFER_NORMALS,
    MESH_BUFFER_TEXCOORDS,
    MESH_BUFFER_INDICES,
    NUM_MESH_BUFFERS
};

class BGE_API Mesh : public Drawable
{

protected:

    int NumVertices;
    int NumTriangles;
    int NumIndices;

    GLuint MeshBuffers[NUM_MESH_BUFFERS];

    /* Bind the mesh data buffers */
    Result BindBuffers() const;

    Mesh();


public:

    virtual ~Mesh();

    virtual Result Bind() const;
    virtual Result Unbind() const;

    virtual Result DrawInstanced(int Count) const;


protected:

    Result CreateBuffers();
    Result ClearBuffers();

}; /* Mesh */

} /* bakge */

#endif /* BAKGE_GRAPHICS_MESH_H */

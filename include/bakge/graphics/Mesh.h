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

/*!
 * @file Mesh.h
 * @brief Mesh class declaration.
 */

#ifndef BAKGE_GRAPHICS_MESH_H
#define BAKGE_GRAPHICS_MESH_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Mesh buffer enumeration.
 *
 * Meshes contain several OpenGL buffers used for storing various data such
 * as vertex positions and texture coordinates. For convenience and clarity
 * the indices of the buffers are enumerated here.
 */
enum MESH_BUFFERS
{
    /*! @brief Vertex positions buffer index.
     *
     * Stores vertex positions in 3D Cartesian space.
     */
    MESH_BUFFER_POSITIONS = 0,

    /*! @brief Vertex normal vectors buffer index.
     *
     * Stores vertex normals as unit vectors in 3D Cartesian space.
     */
    MESH_BUFFER_NORMALS,

    /*! @brief Vertex texture coordinates buffer index.
     *
     * Stores a vertex's texture coordinates in 2D Cartesian space.
     */
    MESH_BUFFER_TEXCOORDS,

    /*! @brief Triangle indices buffer index.
     *
     * Stores triangles' vertex indices. A Mesh is drawn as a series of
     * triangles, using every 3 indices in this buffer as one triangle.
     */
    MESH_BUFFER_INDICES,

    /*! @brief Total number of mesh buffers for any given Mesh.
     *
     * This value can be used to iterate through all Mesh buffers.
     */
    NUM_MESH_BUFFERS
};

/*! @brief A collection of vertex data describing an arbitrary object
 *
 * Meshes data and their associated metadata are used to describe objects
 * to be drawn in 3D Cartesian space. These data include vertex positions,
 * triangle indices, vertex normals and vertex texture coordinates.
 *
 * While these data and metadata are typically stored in various file formats,
 * the Mesh class does not support loading or processing files. Instead it
 * accepts raw vertex data and metadata through its various methods.
 */
class BGE_API Mesh : public Drawable
{

protected:

    int NumVertices;
    int NumTriangles;
    int NumIndices;

    GLuint MeshBuffers[NUM_MESH_BUFFERS];

    /*! @brief Default Mesh constructor.
     *
     * Default Mesh constructor.
     */
    Mesh();


public:

    /*! @brief Virtual Mesh destructor.
     *
     * Virtual Mesh destructor.
     */
    virtual ~Mesh();

    /*! @brief Bind the mesh for drawing use.
     *
     * To draw a mesh it must first be bound. This sets OpenGL state so its
     * vertex data is used in draw calls.
     *
     * @return BGE_SUCCESS if the Mesh was successfully bound; BGE_FAILURE
     * if any errors occurred.
     */
    virtual Result Bind() const;

    /*! @brief Unbind the mesh after drawing use.
     *
     * Unbind sets associated OpenGL state to arbitrary defaults so the
     * Mesh's vertex buffers or data remains safe from undesired modification.
     *
     * @return BGE_SUCCESS if the Mesh was successfully unbound; BGE_FAILURE
     * if any errors occurred.
     */
    virtual Result Unbind() const;

    /*! @brief Instanced drawing used for rendering Crowds.
     *
     * This method is used to render a number of instances of a mesh in a
     * single draw call. A Crowd must be bound before this call, otherwise
     * behavior is undefined.
     *
     * @param[in] Count Number of instances in the Crowd to render.
     *
     * @return BGE_SUCCESS if rendering was successful; BGE_FAILURE if any
     * errors occurred.
     *
     * @see bakge::Crowd
     */
    virtual Result DrawInstanced(int Count) const;


protected:

    Result CreateBuffers();
    Result ClearBuffers();

    Result PositionData(int NumPositions, const Scalar* Data);
    Result NormalData(int NumNormals, const Scalar* Data);
    Result IndexData(int NumIndices, const int* Data);
    Result TexCoordData(int NumTexCoords, const Scalar* Data);

}; /* Mesh */

} /* bakge */

#endif /* BAKGE_GRAPHICS_MESH_H */

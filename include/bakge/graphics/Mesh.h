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
class BGE_API Mesh : public Shape
{

protected:

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

    /*! @brief Create an empty mesh.
     *
     * Create an empty mesh. Use Set*Data methods to set the mesh data before
     * binding or drawing it.
     *
     * @return Pointer to allocated Mesh; NULL if any errors occurred.
     */
    BGE_FACTORY Mesh* Create();

    /*! @brief Write the Mesh data to a Bakge Mesh File v1.0.0.
     *
     * Write the Mesh data to a Bakge Mesh File v1.0.0. The file contents are
     * cleared and the mesh data is written according to the v1.0.0
     * Bakge Mesh File specifications.
     *
     * @param[in] Path String path of the file to write to.
     *
     * @return BGE_SUCCESS if Mesh encoding succeeded; BGE_FAILURE if any
     * errors occurred.
     */
    Result Encode100(const char* Path);

    /*! @brief Open a Bakge Mesh File v1.0.0 and create a Mesh from its data.
     *
     * Open a Bakge Mesh File v1.0.0 and create a Mesh from its data. The
     * file must be of the 1.0.0 format specification for Bakge Mesh File.
     *
     * @param[in] Path String path of the mesh file to open.
     *
     * @return Pointer to allocated Mesh; NULL if any errors occurred.
     */
    BGE_FACTORY Mesh* Decode100(const char* Path);

    /*! @brief Create the OpenGL vertex buffers that store Mesh data.
     *
     * Create the OpenGL vertex buffers that store Mesh data. Calls
     * ClearBuffers and reallocates the buffers.
     *
     * @return BGE_SUCCESS if vertex buffers were successfully allocated;
     * BGE_FAILURE if any errors occurred.
     */
    Result CreateBuffers();

    /*! @brief Deallocate the OpenGL vertex buffers that store Mesh data.
    *
    * Deallocate the OpenGL vertex buffers that store Mesh data.
    *
    * @return BGE_SUCCESS if vertex buffers were successfully deallocated;
    * BGE_FAILURE if any errors occurred.
    */
    Result ClearBuffers();

    /*! @brief Set the contents of the Mesh's vertex position data store.
     *
     * Set the mesh's vertex position data. Data must be fed as an array of
     * structs.
     *
     * @param[in] NumPositions Number of vertices in the Mesh.
     * @param[in] Data Pointer to buffer holding vertex x, y and z positions.
     *
     * @return BGE_SUCCESS if the vertex positions data store was successfully
     * filled; BGE_FAILURE if any errors occurred.
     */
    Result SetPositionData(int NumPositions, const Scalar* Data);

    /*! @brief Set the contents of the Mesh's vertex normal data store.
     *
     * Set the contents of the Mesh's vertex normal data store. Data must be
     * fed as an array of structs.
     *
     * @param[in] NumNormals Number of vertex normals in the Mesh.
     * @param[in] Data Pointer to buffer holding normal x, y and z components.
     *
     * @return BGE_SUCCESS if the vertex normal data store was successfully
     * filled; BGE_FAILURE if any errors occurred.
     */
    Result SetNormalData(int NumNormals, const Scalar* Data);

    /*! @brief Set the contents of the Mesh's triangle indices data store.
     *
     * Set the contents of the Mesh's triangle indices data store. Every three
     * indices form a triangle combination (order does not matter).
     *
     * @param[in] NumIndices Number of triangles (3 indices per triangle).
     * @param[in] Data Buffer containing triangle indices.
     *
     * @return BGE_SUCCESS if the triangle indices data store was successfully
     * filled; BGE_FAILURE if any errors occurred.
     */
    Result SetIndexData(int NumIndices, const int* Data);

    /*! @brief Set the contents of the Mesh's texture coordinates data store.
     *
     * Set the contents of the Mesh's texture coordinates data store. Data
     * must be fed as an array of structs.
     *
     * @param[in] NumTexCoords Number of texture coordinates.
     * @param[in] Data Buffer containing texture coordinate x and y components.
     *
     * @return BGE_SUCCESS if the vertex texture coordinates data store was
     * successfully filled; BGE_FAILURE if any errors occurred.
     */
    Result SetTexCoordData(int NumTexCoords, const Scalar* Data);

    /*! @brief Get the Mesh's vertex position data.
     *
     * Get the Mesh's vertex position data. These positions are relative to
     * the origin.
     *
     * @return Pointer to position data. Do not free this pointer.
     */
    BGE_INL const Scalar* GetPositionData() const
    {
        return Positions;
    }

    /*! @brief Get the Mesh's vertex normal data.
     *
     * Get the Mesh's vertex normal data. Vertex normals are unit vectors
     * which designate the facing of its triangles.
     *
     * @return Pointer to normal data. Do not free this pointer.
     */
    BGE_INL const Scalar* GetNormalData() const
    {
        return Normals;
    }

    /*! @brief Get the Mesh's texcoord data.
     *
     * Get the Mesh's texcoord data. Each vertex has a texture coordinate
     * ranging from 0.0 to 1.0.
     *
     * @return Pointer to texcoord data. Do not free this pointer.
     */
    BGE_INL const Scalar* GetTexCoordData() const
    {
        return TexCoords;
    }

    /*! @brief Get the Mesh's index data.
     *
     * Get the Mesh's index data. Each three indices forms a triangle which
     * is drawn. These triangles together form the complete mesh.
     *
     * @return Pointer to index data. Do not free this pointer.
     */
    BGE_INL const int* GetIndexData() const
    {
        return Indices;
    }

}; /* Mesh */

} /* bakge */

#endif /* BAKGE_GRAPHICS_MESH_H */

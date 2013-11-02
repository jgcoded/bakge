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
 * @file Decode.h
 * API for decoding images or audio streams.
 */

#ifndef BAKGE_DATA_DECODE_H
#define BAKGE_DATA_DECODE_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Decode an image file of any supported format.
 *
 * Decode an image file of any supported format. A buffer is allocated and
 * filled with the raw image data and *Data is set to its address.
 *
 * @param[in] FilePath Null-terminated string of the file in on disk.
 * @param[in] Data Pointee set to address of allocated buffer on success. On
 *                 failure, the pointee is set to NULL.
 * @param[in] W Pointee set to the width of the image decoded.
 * @param[in] H Pointee set to the height of the image decoded.
 * @param[in] N Pointee set to the number of bytes per pixel in the image.
 *
 * @return BGE_SUCCESS if the image data was successfully decoded; BGE_FAILURE
 * if the file does not exist or is not a valid and supported image format.
 */
BGE_FUNC Result DecodeImageFile(const char* FilePath, Byte** Data, int* W,
                                                            int* H, int* N);

/* @brief Open a v1.0.0 Bakge Mesh File and return its handle.
 *
 * Open a v1.0.0 Bakge Mesh File and return its handle. This struct should
 * be considered transparent and never have its contents modified or directly
 * accessed. To extract information about the mesh, use the appropriate
 * decoding API.
 *
 * @param[in] Path String path of the file to open.
 *
 * @return Pointer to mesh file struct; NULL if any errors occurred.
 */
BGE_FUNC bmf::v100* OpenMeshFile100(const char* Path);

/*! @brief Close a v1.0.0 Bakge Mesh File handle.
 *
 * Close a v1.0.0 Bakge Mesh File handle. This transparent struct should
 * never be deleted or freed directly, as there may be open file handles
 * associated with this struct that must be closed.
 *
 * @param[in] Handle Bakge Mesh File struct, v1.0.0
 *
 * @return BGE_SUCCESS if the handle was successfully closed; BGE_FAILURE
 * if any errors occurred.
 */
BGE_FUNC Result CloseMeshFile100(bmf::v100* Handle);

/*! @brief Get the number of vertices in a mesh file.
 * 
 * Get the number of vertices in a mesh from its file handle. Use this value
 * when setting Mesh positions data. The value of *Num is not changed if any
 * errors occur (indicated by a return value of BGE_FAILURE).
 *
 * @param[in] Handle Bakge Mesh File struct, v1.0.0
 * @param[out] Num Pointee set to number of vertices in the mesh file. Not
 *                 changed in occurrence of any error.
 *
 * @return BGE_SUCCESS if number of vertices successfully extracted;
 * BGE_FAILURE if any errors occurred.
 */
BGE_FUNC Result GetNumVertices(bmf::v100* Handle, uint32* Num);

/*! @brief Get the number of indices in a mesh file.
 *
 * Get the number of indices in a mesh file from its handle. Use this value
 * when setting Mesh indices data. The value of *Num is not changed if any
 * errors occurred (indicated by a return value of BGE_FAILURE).
 *
 * @param[in] Handle Bakge Mesh File struct, v1.0.0
 * @param[out] Num Pointee set to number of indices in the mesh file. The
 *                 number of triangles associated with the mesh is *Num / 3.
 *
 * @return BGE_SUCCESS if number of indices successfully extracted;
 * BGE_FAILURE if any errors occurred.
 */
BGE_FUNC Result GetNumIndices(bmf::v100* Handle, uint32* Num);

/*! @brief Get the vertex positions from a mesh file.
 *
 * Get the vertex positions from a mesh file. The supplied buffer must be
 * large enough to hold the data.
 *
 * @param[in] Handle Bakge Mesh File struct, v1.0.0
 * @param[in] Buffer Pointer to buffer to fill. Must be large enough to hold
 *                   3 * sizeof(Scalar) * GetNumVertices(Handle) bytes.
 */
BGE_FUNC void GetVertexPositions(bmf::v100* Handle, Scalar* Buffer);

/*! @brief Get the vertex normals from a mesh file.
 *
 * Get the vertex normals from a mesh file. The supplied buffer must be large
 * enough to hold the data.
 *
 * @param[in] Handle Bakge Mesh File, v1.0.0
 * @param[in] Buffer Pointer to the buffer to fill. Must be large enough to
 *                   hold 3 * sizeof(Scalar) * GetNumVertices(Handle) bytes.
 */
BGE_FUNC void GetVertexNormals(bmf::v100* Handle, Scalar* Buffer);

/*! @brief Get the vertex texture coordinates from a mesh file.
 *
 * Get the vertex texture coordinates from a mesh file. The supplied buffer
 * must be large enough to hold the data.
 *
 * @param[in] Handle Bakge Mesh File, v1.0.0
 * @param[in] Buffer Pointer to the buffer to fill. Must be large enough to
 *                   hold 2 * sizeof(Scalar) * GetNumVertices(Handle) bytes.
 */
BGE_FUNC void GetVertexTexCoords(bmf::v100* Handle, Scalar* Buffer);

/*! @brief Get the triangle indices from a mesh file.
 *
 * Get the triangle indices from a mesh file. The supplier buffer must be
 * large enough to hold the data.
 *
 * @param[in] Handle Bakge Mesh File, v1.0.0
 * @param[in] Buffer Pointer to the buffer to fill. Must be large enough to
 *                   hold 3 * sizeof(uint32) * GetNumTriangles(Handle) bytes.
 */
BGE_FUNC void GetTriangleIndices(bmf::v100* Handle, uint32* Buffer);

} /* bakge */

#endif // BAKGE_DATA_DECODE_H

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
 *
 * @return BGE_SUCCESS if the image data was successfully decoded; BGE_FAILURE
 * if the file does not exist or is not a valid and supported image format.
 */
BGE_FUNC Result DecodeImageFile(const char* FilePath, Byte** Data);

/*! @brief Get the number of vertices in a mesh file.
 * 
 * Get the number of vertices in a mesh from its file handle. Use this value
 * when setting Mesh positions data. The value of *Num is not changed if any
 * errors occur (indicated by a return value of 0 or -1).
 *
 * @param[in] Handle Bakge Mesh File struct, v1.0.0
 * @param[out] Num Pointee set to number of vertices in the mesh file. Not
 *                 changed in occurrence of any error.
 *
 * @return 1 if no errors occurred; -1 if some error occurred; 0 if invalid
 * format or format version.
 */
BGE_FUNC int GetNumVertices(bmf::v100 Handle, uint32* Num);

} /* bakge */

#endif // BAKGE_DATA_DECODE_H

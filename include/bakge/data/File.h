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
 * @file File.h
 * File class declaration.
 */

#ifndef BAKGE_DATA_FILE_H
#define BAKGE_DATA_FILE_H

#include <bakge/Bakge.h>

namespace bakge
{

enum FILE_MODE
{
    FILE_MODE_NONE = 0,
    FILE_MODE_READ,
    FILE_MODE_WRITE,
    FILE_MODE_APPEND,
    NUM_FILE_MODES
};

/*! @brief PHYSFS_file wrapper class.
 *
 * Bakge uses PhysicsFS internally for all filesystem-related functionality.
 */
class BGE_API File
{
    PHYSFS_File* Handle;
    char* Path;

    int Mode;

    /*! @brief Default File constructor.
     *
     * Default File constructor.
     */
    File();


public:

    /*! @brief File destructor.
     *
     * File destructor.
     */
    ~File();

    BGE_FACTORY File* Open(const char* Path);

    /*! @brief Write a string to file at the current offset.
     *
     * Write a string to file at the current offset. The number of bytes
     * is added to the current file offset.
     *
     * @param[in] Str Pointer to string to write.
     *
     * @return Number of bytes written; -1 if any errors occurred.
     */
    int Write(const char* Str);

    /*! @brief Read a given number of bytes from the file at the current
     * offset.
     *
     * Read a given number of bytes from the file at the current offset. The
     * current offset is incremented by the number of bytes read. If any error
     * occurs, the provided buffer is not modified.
     *
     * @param[in] NumBytes Number of bytes to read.
     * @param[in] Buffer Pointer to buffer to write to. Must be sufficiently
     *            large to write the given number of bytes.
     *
     * @return Number of bytes read; -1 if any errors occurred.
     */
    int Read(int NumBytes, char* Buffer);

    Result Close();

}; /* File */

} /* bakge */

#endif /* BAKGE_DATA_FILE_H */

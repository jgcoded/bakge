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

namespace bakge
{

File::File()
{
    Handle = NULL;
    Path = NULL;
    Mode = FILE_MODE_NONE;
    Offset = 0;
}


File::~File()
{
    Close();

    free(Path);
}


File* File::Open(const char* Path)
{
    // Check if the file exists within the search path.
    if(PHYSFS_exists(Path) == 0) {
        Log("ERROR: File - Could not find file \"%s\"\n.", Path);
        return NULL;
    }

    if(PHYSFS_isDirectory(Path)) {
        Log("ERROR: File - \"%s\" is a directory.\n", Path);
        return NULL;
    }

    int Len = strlen(Path);
    if(Len < 1) {
        Log("ERROR: File - Invalid path string.\n");
        return NULL;
    }

    File* F = new File;
    if(F == NULL) {
        Log("ERROR: File - Couldn't allocate memory.\n");
        return NULL;
    }

    F->Path = (char*)malloc(Len + 1);
    if(F->Path == NULL) {
        Log("ERROR: File - Error allocating name string buffer.\n");
        delete F;
        return NULL;
    }

    memcpy((void*)F->Path, (const void*)Path, Len);
    F->Path[Len] = '\0';

    return F;
}


Result File::Close()
{
    /* File isn't opened */
    if(Handle == NULL) {
        return BGE_FAILURE;
    }

    /* Error occurred while closing file */
    if(PHYSFS_close(Handle) == 0) {
        return BGE_FAILURE;
    } else {
        Handle = NULL;
    }

    return BGE_SUCCESS;
}


int File::Write(const char* Str)
{
    return -1;
}


int File::Read(int NumBytes, char* Buffer)
{
    return -1;
}

} /* bakge */

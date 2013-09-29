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

Source::Source()
{
}


Source::~Source()
{
}


Source* Source::Create()
{
    Source* S = new Source;
    if(S == NULL) {
        printf("Error allocating source\n");
        return NULL;
    }

    alGetError();
    alGenSources(1, &S->SourceHandle);
    if(alGetError() != AL_NO_ERROR) {
        printf("Error creating source\n");
        delete S;
        return NULL;
    }

    return S;
}


Result Source::Bind() const
{
    return BGE_FAILURE;
}


Result Source::Unbind() const
{
    return BGE_FAILURE;
}


Result Source::Play() const
{
    alSourcePlay(SourceHandle);

    return BGE_FAILURE;
}


Result Source::Attach(Stream* Str)
{
    return BGE_FAILURE;
}

} /* bakge */

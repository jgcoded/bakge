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

#ifndef BAKGE_AUDIO_STREAM_H
#define BAKGE_AUDIO_STREAM_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Audio stream wrapper.
 *
 * Audio stream wrapper for sound data.
 */
class BGE_API Stream
{
    friend Result Source::Attach(Stream* Str);

    ALuint StreamBuffer;
    stb_vorbis_alloc Allocation;
    stb_vorbis_info Info;
    stb_vorbis* Vorbis;

    Stream();


public:

    ~Stream();

    BGE_FACTORY Stream* Create(int Len, Byte* Data);

    BGE_INL int GetSize() const
    {
        return Allocation.alloc_buffer_length_in_bytes;
    }

    BGE_INL int GetFrequency() const
    {
        return Info.sample_rate;
    }

    BGE_INL int GetNumChannels() const
    {
        return Info.channels;
    }

}; /* Stream */

} /* bakge */

#endif /* BAKGE_AUDIO_STREAM_H */

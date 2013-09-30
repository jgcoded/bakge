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
 * @file Stream.h
 * @brief Stream class declaration.
 */

#ifndef BAKGE_AUDIO_STREAM_H
#define BAKGE_AUDIO_STREAM_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Wrapper class for decoded Ogg Vorbis audio stream data.
 *
 * Wrapper class for decoded Ogg Vorbis audio stream data. To play an
 * audio Stream, you must first attach it to a Source and
 * \link Source::Play Play\endlink it.
 *
 * @see Source, Source::Play
 */
class BGE_API Stream
{
    friend Result Source::Attach(Stream* Str);

    ALuint StreamBuffer;
    stb_vorbis_info Info;
    stb_vorbis* Vorbis;

    /*! @brief Default Stream constructor.
     *
     * Default Stream constructor.
     */
    Stream();


public:

    /*! @brief Default Stream destructor.
     *
     * Default Stream destructor.
     */
    ~Stream();

    /*! @brief Create a new Stream from a complete, encoded Ogg Vorbis stream.
     *
     * This factory function decodes a complete Ogg Vorbis stream and returns
     * a Stream object that you can attach to a Source to play audio with.
     * A Stream is not an audio stream in the traditional sense; the entire
     * encoded audio file must be passed so it can be correctly decoded and
     * turned into audio.
     *
     * @return Pointer to allcoated Stream; NULL if any errors occurred or
     * decoding failed.
     */
    BGE_FACTORY Stream* Create(int Len, Byte* Data);

    /*! @brief Get the frequency (sample rate) of the stream in hertz (Hz).
     *
     * Get the frequency (sample rate) of the stream in hertz (Hz).
     *
     * @return Frequency of audio stream in Hz.
     */
    BGE_INL int GetFrequency() const
    {
        return Info.sample_rate;
    }

    /*! @brief Get the number of channels in the audio stream.
     *
     * Get the number of channels in the audio stream.
     *
     * @return Number of channels in the audio stream.
     */
    BGE_INL int GetNumChannels() const
    {
        return Info.channels;
    }

}; /* Stream */

} /* bakge */

#endif /* BAKGE_AUDIO_STREAM_H */

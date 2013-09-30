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
 * @file Environment.h
 * Environment class declaration.
 */

#ifndef BAKGE_AUDIO_ENVIRONMENT_H
#define BAKGE_AUDIO_ENVIRONMENT_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief An audio Environment through which sounds are played.
 *
 * An audio Environment consists of an OpenAL context and its associated
 * listener. The listener, as well as any Source objects, are placed in
 * 3D Cartesian space, and OpenAL handles the positional audio.
 */
class BGE_API Environment : public Bindable
{
    ALCdevice* Device;
    ALCcontext* Context;


protected:

    /*! @brief Default Environment constructor.
     *
     * Default Environment constructor.
     */
    Environment();


public:

    /*! @brief Default Virtual destructor.
     *
     * Virtual Environment destructor.
     */
    virtual ~Environment();

    /*! @brief Create a new audio Environment.
     *
     * Create a new audio Environment. Typically your application will only
     * need one. OpenAL contexts are different from OpenGL contexts in that
     * one context may only be current on a per-process basis, not a
     * per-thread basis. As a result you should only use one context to
     * create and manage your sounds.
     *
     * Each Environment consists of a listener, which is where the audio is
     * heard from by the user. This listener can be moved around in space
     * to manipulate how the audio is heard.
     *
     * @return Pointer to allocated Environment; NULL if any errors occurred.
     */
    BGE_FACTORY Environment* Create();

    /*! @brief Bind the Environment as the active context in the process.
     *
     * Bind the Environment as the active context in the process.
     *
     * @return BGE_SUCCESS if the Environment context was successfully made
     * current; BGE_FAILURE if any errors occurred.
     */
    Result Bind() const;

    /*! @brief Unbind the Environment as the active context in the process.
     *
     * Unbind the Environment as the active context in the process.
     *
     * @return BGE_SUCCESS if the Environment was successfully unbound;
     * BGE_FAILURE if any errors occurred.
     */
    Result Unbind() const;

}; /* Environment */

} /* bakge */

#endif /* BAKGE_AUDIO_ENVIRONMENT_H */

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
 * @file Mutex.h
 * @brief Mutex API class declaration.
 */

#ifndef BAKGE_API_MUTEX_H
#define BAKGE_API_MUTEX_H

namespace bakge
{
namespace api
{

/*! @brief Used to protect sections of code from being run by more than one
 * thread at a time.
 *
 * The Mutex class is a wrapper for platform-specific implementations of
 * a mutex. Mutexes are used to protect sections of code from being run
 * by more than one thread at a time. They are also called binary semaphores.
 */
class BGE_API Mutex
{

protected:

    /*! @brief Default Mutex constructor.
     *
     * Default Mutex constructor.
     */
    Mutex();


public:

    /*! @brief Virtual Mutex constructor.
     *
     * Virtual Mutex constructor.
     */
    virtual ~Mutex();

    /*! @brief Immediately lock a mutex, preventing from other threads from
     * locking it until it is released.
     *
     * Immediately lock a mutex, preventing from other threads from locking
     * it until it is released.
     *
     * @return BGE_SUCCESS if the Mutex was successfully locked; BGE_FAILURE
     * if it is already locked.
     */
    virtual Result Lock() = 0;

    /*! @brief Unlock a mutex, allowing other threads to lock it.
     *
     * Unlock a mutex, allowing other threads to lock it.
     *
     * @return BGE_SUCCESS if the Mutex was successfully unlocked;
     * BGE_FAILURE if any errors occurred.
     */
    virtual Result Unlock() = 0;

}; /* Mutex */

} /* api */
} /* bakge */

#endif /* BAKGE_API_MUTEX_H */

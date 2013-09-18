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
 * @file Thread.h
 * @brief Thread class declaration.
 */

#ifndef BAKGE_API_THREAD_H
#define BAKGE_API_THREAD_H

namespace bakge
{
namespace api
{

/*! @brief Wrapper class for thread object implementations.
 *
 * Threads (also called lightweight processes) are used to run code
 * simultaneously. Threads within a process share heap, text and data
 * segments, etc with the exception that each thread has its own
 * run-time stack.
 *
 * It is recommended that you do not return a negative value from your
 * thread's entry function, since a negative value distinguishes threads
 * that are still running from those that have terminated.
 */
class BGE_API Thread
{

protected:

    /*! @brief Default Thread constructor.
     *
     * Default Thread constructor.
     */
    Thread();


public:

    /*! @brief Virtual Thread destructor.
     *
     * Virtual Thread destructor.
     */
    virtual ~Thread();

    /*! @brief Terminate the thread gracelessly.
     *
     * Terminate the thread gracelessly.
     *
     * @return BGE_SUCCESS if the Thread was successfully killed; BGE_FAILURE
     * if any errors occurred.
     *
     * @warn It is recommended you do NOT do this unless absolutely necessary.
     */
    virtual Result Kill() = 0;

    /*! @brief Wait for the Thread to terminate gracefully.
     *
     * Wait for the Thread to terminate gracefully.
     *
     * @return Exit code from the thread.
     */
    virtual int Wait() = 0;

    /*! @brief Get the exit code from the Thread after it has terminated.
     *
     * Get the exit code from the Thread after it has terminated.
     *
     * @return Exit code from the Thread; -1 if it is still running.
     */
    virtual int GetExitCode() = 0;

}; /* Thread */

} /* api */
} /* bakge */

#endif /* BAKGE_API_THREAD_H */

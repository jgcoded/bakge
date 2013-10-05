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
 * @file Utility.h
 * @brief Utility functions and macros declarations.
 */
#ifndef BAKGE_CORE_UTILITY_H
#define BAKGE_CORE_UTILITY_H

#include <bakge/Bakge.h>

#ifdef _DEBUG
/*! @brief Simple assert macro.
 *
 * If predicate PRED evaluates to false, an error message is sent to
 * stderr with the file and line location of the failed assertion, and the
 * program exits.
 */
#define BGE_ASSERT(PRED) \
    if(!(PRED)) { \
        fprintf(stderr, "Assertion failed at line %d in file %s\n" \
                        " - Predicate %s\n", \
        __LINE__, __FILE__, #PRED); \
        exit(-1); \
    }

/*! @brief Extended assert macro.
 *
 * If predicate PRED evaluates to false, the message MSG is sent to
 * stderr with the file and line location of the failed assertion, and the
 * program exits.
 */
#define BGE_ASSERT_EX(PRED, MSG) \
    if(!(PRED)) { \
        fprintf(stderr, "%s: at line %d in file %s\n" \
                        " - Predicate %s\n", \
        MSG, __LINE__, __FILE__, #PRED); \
        exit(-1); \
    }
#else
#define BGE_ASSERT(PRED)
#define BGE_ASSERT_EX(PRED, MSG)
#endif

namespace bakge
{

/*! @brief Initialize Bakge and all its components.
 *
 * Init must be called before any Bakge class or method can safely be used.
 * Calling Init twice or failing to match it with a corresponding Deinit call
 * before your program exits can cause crashes or memory leaks.
 *
 * @param[in] argc Number of command-line arguments.
 * @param[in] argv Array of command-line arguments.
 *
 * @return BGE_SUCCESS if initialization was successful; BGE_FAILURE if any
 * errors occurred.
 */
BGE_FUNC Result Init(int argc, char* argv[]);

/*! @brief Deinitialize Bakge and clean up any resources allocated by Init.
 *
 * Deinit must be called before your program exits. This function cleans up
 * internal resources that were allocated when Init was called. Calling
 * Deinit when not preceded by an Init call may result in crashes or memory
 * leaks.
 *
 * @return BGE_SUCCESS if deinitialization was successful; BGE_FAILURE if any
 * errors occurred.
 */
BGE_FUNC Result Deinit();

/*! @brief Print computer system and OpenGL version info to stdout.
 *
 * Print computer system and OpenGL version info to stdout.
 */
BGE_FUNC void SystemInfo();

BGE_WUNUSED BGE_FUNC Byte* LoadFileContents(const char* Path);

/*! @brief Write a time-stamped log message to bakge.log.
 *
 * The log file is cleared and opened when bakge::Init is called, and is
 * saved to disk and closed whne bakge::Deinit is called. Is a wrapper around
 * the standard library printf function.
 *
 * @todo Time-stamp, print to file instead of stdout.
 */
BGE_FUNC int Log(const char* Format, ...);

} /* bakge */

#endif /* BAKGE_CORE_UTILITY_H */

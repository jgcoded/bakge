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

#ifndef BAKGE_ENGINE_SCRIPTEDENGINE_H
#define BAKGE_ENGINE_SCRIPTEDENGINE_H

#include <bakge/Bakge.h>

namespace bakge
{

class ScriptedEngine : public Engine
{

public:

    ScriptedEngine();
    ~ScriptedEngine();

    /* *
     * This function signature will change
     * Runs if an error occurs in script. Should report details
     * of the error and gracefully terminate the script state
     * */
    virtual void Error() = 0;

    /* Run a script from file */
    virtual Result RunFile(const char* ScriptPath) = 0;

    /* Run a script from a string */
    virtual Result RunString(const char* Source) = 0;


protected:

    lua_State* L;

}; /* ScriptedEngine */

} /* bakge */

#endif /* BAKGE_ENGINE_SCRIPTEDENGINE_H */

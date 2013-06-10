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

#ifndef BAKGE_BAKGE_H
#define BAKGE_BAKGE_H

/* Include standard library dependencies */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* GCC-only attributes */
#ifdef __GNUC__
/* Send compiler warning if function return result is not used */
#define BGE_WUNUSED __attribute__((warn_unused_result))
/* Mark a variable as possibly unused in its function  */
#define BGE_UNUSED __attribute__((unused))
/* Factory functions are static class methods that return allocated memory  */
#else /* Define them anyways to avoid compilation errors  */
#define BGE_WUNUSED
#define BGE_UNUSED
#endif /* __GNUC__  */

/* MSVC pragmas */
#ifdef _MSC_VER
/* Prevent library conflict warning */
#pragma comment(linker, "/NODEFAULTLIB:MSVCRT")
#endif /* _MSC_VER */

/* Common definitions */
#define BGE_FUNC extern
#define BGE_FACTORY static BGE_WUNUSED

/* External library dependencies */
#include <GL/glfw.h>

/* Include Bakge */
#include <bakge/core/Type.h>
#include <bakge/core/Bindable.h>
#include <bakge/core/Drawable.h>
#include <bakge/core/Renderer.h>
#include <bakge/core/Window.h>
#include <bakge/core/Texture.h>
#include <bakge/core/EventHandler.h>
#include <bakge/core/Engine.h>

#include <bakge/renderer/FrontRenderer.h>

#endif /* BAKGE_BAKGE_H */


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
 * @file ShaderLibrary.h
 * @brief Bakge Shader API function documentation.
 */

#ifndef BAKGE_GRAPHICS_SHADERLIBRARY_H
#define BAKGE_GRAPHICS_SHADERLIBRARY_H

/*! @defgroup VertexLib
 *
 * @brief Bakge vertex shader library.
 *
 * Contains shader uniforms and attributes needed by Bakge to properly render
 * objects in the world.
 *
 * @{
 */

/*! @brief Model transformation of vertices.
 *
 * Divisor is always 1, so this attribute does not change until the entire mesh
 * instance has been drawn.
 */
attribute mat4x4 bge_Model;

/*! @brief Current viewing matrix.
 *
 * Set when a Camera class is bound.
 */
uniform mat4x4 bge_View;

/*! @brief Current projection matrix.
 *
 * Set when a Camera class is bound.
 */
uniform mat4x4 bge_Projection;

/*! @brief Position of vertices being drawn in 3D Cartesian space.
 *
 * Even when drawing to 2D space the vertices are drawn in 3D space. Using a
 * depth buffer and a Z value allows you to change the order of windows without
 * having to use the painter's algorithm (draw objects back to front).
 */
attribute vec4 bge_Vertex;

/*! @brief Normals of vertices in 3D Cartesian space.
 *
 * To get the transformed normals in eye space, multiply the normal by the
 * 3x3 upper-left portion of the model-view matrix.
 */
attribute vec4 bge_Normal;

/*! // End group VertexLib
 * @}
 */

#endif /* BAKGE_GRAPHICS_SHADERLIBRARY_H */

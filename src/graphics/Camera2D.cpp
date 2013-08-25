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

Camera2D::Camera2D()
{
}


Camera2D::~Camera2D()
{
}


void Camera2D::SetDimensions(Scalar W, Scalar H)
{
    Ortho.SetOrthographic(W, H, -1.0f, 1.0f);
}


Result Camera2D::Bind() const
{
    GLint Location, Program = 0;

    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0)
        return BGE_FAILURE;

    /* First we'll set the perspective */
    Location = glGetUniformLocation(Program, "bge_Perspective");
    if(Location < 0)
        return BGE_FAILURE;

    glUniformMatrix4fv(Location, 1, GL_FALSE, &Ortho[0]);

    /* Now the view transform */
    Location = glGetUniformLocation(Program, "bge_View");
    if(Location < 0)
        return BGE_FAILURE;

    glUniformMatrix4fv(Location, 1, GL_FALSE, &Matrix::Identity[0]);

    return BGE_SUCCESS;
}


Result Camera2D::Unbind() const
{
    GLint Location, Program = 0;

    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0)
        return BGE_FAILURE;

    /* First we'll set the perspective */
    Location = glGetUniformLocation(Program, "bge_Perspective");
    if(Location < 0)
        return BGE_FAILURE;

    glUniformMatrix4fv(Location, 1, GL_FALSE, &Matrix::Identity[0]);

    /* Now the view transform */
    Location = glGetUniformLocation(Program, "bge_View");
    if(Location < 0)
        return BGE_FAILURE;

    glUniformMatrix4fv(Location, 1, GL_FALSE, &Matrix::Identity[0]);

    return BGE_SUCCESS;
}

} /* bakge */

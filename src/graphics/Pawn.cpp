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

Pawn::Pawn()
{
    Scale = Vector4(1, 1, 1, 0);
}


Pawn::~Pawn()
{
}


Result Pawn::SetScale(Scalar X, Scalar Y, Scalar Z)
{
    Scale[0] = X;
    Scale[1] = Y;
    Scale[2] = Z;

    return BGE_SUCCESS;
}


Vector4 BGE_NCP Pawn::GetScale() const
{
    return Scale;
}


Result Pawn::Bind() const
{
    Result Errors = BGE_SUCCESS;
    GLint Program, Location;

    /* Retrieve current shader program */
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0)
        Errors = BGE_FAILURE;

    /* Get location of bge_Rotation uniform */
    Location = glGetAttribLocation(Program, BGE_ROTATION_ATTRIBUTE);
    if(Location < 0)
        Errors = BGE_FAILURE;

    /* Get location of bge_Scale uniform */
    Location = glGetAttribLocation(Program, BGE_SCALE_ATTRIBUTE);
    if(Location < 0)
        Errors = BGE_FAILURE;

    if(Node::Bind() != BGE_SUCCESS)
        Errors = BGE_FAILURE;

    return Errors;
}


Result Pawn::Unbind() const
{
    GLint Program, Location;

    /* Retrieve current shader program */
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0)
        return BGE_FAILURE;

    /* Get location of bge_Rotation uniform */
    Location = glGetAttribLocation(Program, BGE_ROTATION_ATTRIBUTE);
    if(Location < 0)
        return BGE_FAILURE;

    return Node::Unbind();
}


Result Pawn::Draw() const
{
    Node::Draw();

    /* No Pawn::Draw implementation yet */

    return BGE_SUCCESS;
}

} /* bakge */

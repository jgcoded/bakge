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


Pawn* Pawn::Create()
{
    Pawn* P = new Pawn;

    glGenBuffers(1, &P->ModelMatrixBuffer);
    if(P->ModelMatrixBuffer == 0) {
        printf("Error creating model matrix buffer\n");
        delete P;
        return NULL;
    }

    return P;
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
    Location = glGetAttribLocation(Program, BGE_MODEL_ATTRIBUTE);
    if(Location < 0)
        Errors = BGE_FAILURE;

    Matrix Transformation;
    Transformation *= Facing.ToMatrix();
    Transformation.Translate(Position[0], Position[1], Position[2]);

    glBindBuffer(GL_ARRAY_BUFFER, ModelMatrixBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Transformation[0]) * 16,
                            &Transformation[0], GL_DYNAMIC_DRAW);

    /* *
     * Each attribute pointer has a stride of 4. Since mat4x4 are composed
     * of 4 vec4 components, set each of these individually
     * */
    for(int i=0;i<4;++i) {
        glEnableVertexAttribArray(Location + i);
        glVertexAttribPointer(Location + i, 4, GL_FLOAT, GL_FALSE, 0,
                            (const GLvoid*)(sizeof(Scalar) * 4 * i));
        /* So the attribute is updated per instance, not per vertex */
        glVertexAttribDivisor(Location + i, 1);
    }

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
    Location = glGetAttribLocation(Program, BGE_MODEL_ATTRIBUTE);
    if(Location < 0)
        return BGE_FAILURE;

    return Node::Unbind();
}


Quaternion BGE_NCP Pawn::SetRotation(Quaternion Rotation)
{
    Facing = Rotation;

    return Facing;
}


Quaternion BGE_NCP Pawn::GetRotation() const
{
    return Facing;
}

} /* bakge */

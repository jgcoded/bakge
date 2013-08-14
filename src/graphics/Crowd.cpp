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

Crowd::Crowd()
{
    Population = 0;
    Capacity = 0;
    Members = NULL;
}


Crowd::~Crowd()
{
    Clear();
}


Crowd* Crowd::Create(int ReserveMembers)
{
    Crowd* C = new Crowd;

    glGenBuffers(1, &C->ModelMatrixBuffer);
    if(C->ModelMatrixBuffer == 0) {
        printf("Error creating model matrix buffer\n");
        delete C;
        return NULL;
    }

    C->Reserve(ReserveMembers);

    return C;
}


Result Crowd::Bind() const
{
    GLint Program, Location;

    /* Retrieve current shader program */
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program < 0)
        return BGE_FAILURE;

    /* Retrieve location of the bge_Translation vec4 */
    Location = glGetAttribLocation(Program, BGE_MODEL_ATTRIBUTE);
    if(Location < 0)
        return BGE_FAILURE;

    glBindBuffer(GL_ARRAY_BUFFER, CrowdBuffer);

    /* *
     * Each attribute pointer has a stride of 4. Since mat4x4 are composed
     * of 4 vec4 components, set each of these individually
     * */
    for(int i=0;i<4;++i) {
        glEnableVertexAttribArray(Location);
        glVertexAttribPointer(Location, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix),
                                    (const GLvoid*)(sizeof(Scalar) * 4 * i));
        /* So the attribute is updated per instance, not per vertex */
        glVertexAttribDivisor(Location, 1);
        ++Location;
    }

    Location = glGetUniformLocation(Program, BGE_CROWD_UNIFORM);
    if(Location < 0)
        return BGE_FAILURE;

    Matrix CrowdTransform;
    CrowdTransform *= Facing.ToMatrix();
    CrowdTransform.Translate(Position[0], Position[1], Position[2]);

    glUniformMatrix4fv(Location, 1, GL_FALSE, &CrowdTransform[0]);

    return BGE_SUCCESS;
}


Result Crowd::Unbind() const
{
    GLint Program, Location;

    /* Retrieve current shader program */
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program < 0)
        return BGE_FAILURE;

    Location = glGetUniformLocation(Program, BGE_CROWD_UNIFORM);
    if(Location < 0)
        return BGE_FAILURE;

    glUniformMatrix4fv(Location, 1, GL_FALSE, &Matrix::Identity[0]);

    return BGE_SUCCESS;
}


Result Crowd::Clear()
{
    if(Members == NULL)
        return BGE_FAILURE;

    delete[] Members;
    Members = NULL;

    return BGE_SUCCESS;
}


Result Crowd::Reserve(int NumMembers)
{
    Clear();

    Capacity = NumMembers;
    Population = NumMembers;
    Members = new Matrix[NumMembers];

    glBindBuffer(GL_ARRAY_BUFFER, CrowdBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Scalar) * 16 * NumMembers, Members,
                                                            GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Crowd::TranslateMember(int MemberIndex, Scalar X, Scalar Y, Scalar Z)
{
    /* Prevent out-of-bounds transformations */
    if(MemberIndex < 0 || MemberIndex >= Capacity)
        return BGE_FAILURE;

    Members[MemberIndex].Translate(X, Y, Z);

    GLint Stride = sizeof(Scalar) * 16;

    glBindBuffer(GL_ARRAY_BUFFER, CrowdBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, Stride * MemberIndex, Stride,
                            (const GLvoid*)&Members[MemberIndex][0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Crowd::RotateMember(int MemberIndex, Quaternion Rotation)
{
    /* Prevent out-of-bounds transformations */
    if(MemberIndex < 0 || MemberIndex >= Capacity)
        return BGE_FAILURE;

    /* First figure out the translation */
    Vector4 Translated(Members[MemberIndex][12], Members[MemberIndex][13],
                                                Members[MemberIndex][14], 0);

    /* Now translate back to the origin first */
    Members[MemberIndex].Translate(-Translated[0], -Translated[1],
                                                    -Translated[2]);

    /* Apply rotation */
    Members[MemberIndex] *= Rotation.ToMatrix();

    /* Translate back to original position */
    Members[MemberIndex].Translate(Translated[0], Translated[1],
                                                    Translated[2]);

    GLint Stride = sizeof(Scalar) * 16;

    glBindBuffer(GL_ARRAY_BUFFER, CrowdBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, Stride * MemberIndex, Stride,
                            (const GLvoid*)&Members[MemberIndex][0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


Result Crowd::ScaleMember(int MemberIndex, Scalar X, Scalar Y, Scalar Z)
{
    /* Prevent out-of-bounds transformations */
    if(MemberIndex < 0 || MemberIndex >= Capacity)
        return BGE_FAILURE;

    /* First figure out the translation */
    Vector4 Translated(Members[MemberIndex][12], Members[MemberIndex][13],
                                                Members[MemberIndex][14], 0);

    /* Translate back to the origin first */
    Members[MemberIndex].Translate(-Translated[0], -Translated[1],
                                                    -Translated[2]);

    /* Apply scale transformation */
    Members[MemberIndex].Scale(X, Y, Z);

    /* Translate back to original position */
    Members[MemberIndex].Translate(Translated[0], Translated[1],
                                                    Translated[2]);

    GLint Stride = sizeof(Scalar) * 16;

    glBindBuffer(GL_ARRAY_BUFFER, CrowdBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, Stride * MemberIndex, Stride,
                            (const GLvoid*)&Members[MemberIndex][0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}

} /* bakge */

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
#ifdef _DEBUG
#include <bakge/internal/Debug.h>
#endif // _DEBUG

namespace bakge
{

Node::Node()
{
    ModelMatrixBuffer = 0;
}


Node::~Node()
{
    if(ModelMatrixBuffer != 0)
        glDeleteBuffers(1, &ModelMatrixBuffer);
}


Result Node::Bind() const
{
    GLint Program, Location;

    /* Retrieve current shader program */
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0)
        return BGE_FAILURE;

    /* Retrieve location of the bge_Translation vec4 */
    Location = glGetAttribLocation(Program, BGE_MODEL_ATTRIBUTE);
    if(Location < 0) {
#ifdef _DEBUG
        WarnMissingAttribute(BGE_MODEL_ATTRIBUTE);
#endif // _DEBUG
        return BGE_FAILURE;
    }

    Matrix Translation = Matrix::Translation(Position[0], Position[1],
                                                        Position[2]);

    /* Update the buffer with the new position */
    glBindBuffer(GL_ARRAY_BUFFER, ModelMatrixBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Translation[0]) * 16, &Translation[0],
                                                            GL_DYNAMIC_DRAW);

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

    return BGE_SUCCESS;
}


Result Node::Unbind() const
{
    GLint Program, Location;

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Retrieve current shader program */
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0)
        return BGE_FAILURE;

    Location = glGetAttribLocation(Program, BGE_MODEL_ATTRIBUTE);
    if(Location < 0) {
#ifdef _DEBUG
        WarnMissingAttribute(BGE_MODEL_ATTRIBUTE);
#endif // _DEBUG
        return BGE_FAILURE;
    }

    for(int i=0;i<4;++i)
        glDisableVertexAttribArray(Location + i);

    return BGE_SUCCESS;
}


Vector4 BGE_NCP Node::SetPosition(Scalar X, Scalar Y, Scalar Z)
{
    Position[0] = X;
    Position[1] = Y;
    Position[2] = Z;

    return Position;
}


Vector4 BGE_NCP Node::GetPosition() const
{
    return Position;
}


Node* Node::Create(Scalar X, Scalar Y, Scalar Z)
{
    GLuint Store;
    glGenBuffers(1, &Store);
    if(Store == 0) {
        Log("ERROR: Node - Couldn't create model matrix buffer\n");
        return NULL;
    }

    Node* N = new Node;
    if(N == NULL) {
        Log("ERROR: Node - Couldn't allocate memory\n");
        return NULL;
    }

    N->ModelMatrixBuffer = Store;
    N->SetPosition(X, Y, Z);

    return N;
}


Vector4 BGE_NCP Node::Translate(Scalar X, Scalar Y, Scalar Z)
{
    Position[0] += X;
    Position[1] += Y;
    Position[2] += Z;

    return Position;
}

} /* bakge */

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

Node::Node()
{
    glGenBuffers(1, &PositionBuffer);
}


Node::~Node()
{
    glDeleteBuffers(1, &PositionBuffer);
}


Node* Node::Create(math::Scalar X, math::Scalar Y, math::Scalar Z)
{
    Node* N;

    N = new Node;
    if(N == NULL) {
        printf("Error allocating new node\n");
        return NULL;
    }

    /* *
     * Set buffer data. Nodes are drawn at 0, 0, 0 because the shader
     * library will translate them in the vertex shader
     * */
    glBindBuffer(GL_ARRAY_BUFFER, N->PositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(N->Position[0]) * 4, &N->Position[0],
                                                            GL_DYNAMIC_DRAW);

    N->SetPosition(X, Y, Z);

    return N;
}


Result Node::Bind() const
{
    GLint Program, Location;

    /* Retrieve current shader program */
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program < 0)
        return BGE_FAILURE;

    /* Retrieve location of the bge_Position vec4 */
    Location = glGetUniformLocation(Program, BGE_POSITION_UNIFORM);
    if(Location < 0)
        return BGE_FAILURE;

    /* Assign this node's position as bge_Position */
    glUniform4fv(Location, 1, &Position[0]);

    return BGE_SUCCESS;
}


Result Node::Unbind() const
{
    static const math::Vector4 Origin;
    GLint Program, Location;

    /* Retrieve current shader program */
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program < 0)
        return BGE_FAILURE;

    /* Retrieve location of the bge_Position vec4 */
    Location = glGetUniformLocation(Program, BGE_POSITION_UNIFORM);
    if(Location < 0)
        return BGE_FAILURE;

    /* Assign origin position as bge_Position */
    glUniform4fv(Location, 1, &Origin[0]);

    return BGE_SUCCESS;
}


Result Node::Draw() const
{
    unsigned int Indices[] = { 1 };

    glBindBuffer(GL_ARRAY_BUFFER, PositionBuffer);
    glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, (void*)Indices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return BGE_SUCCESS;
}


void Node::SetPosition(math::Scalar X, math::Scalar Y, math::Scalar Z)
{
    Position[0] = X;
    Position[1] = Y;
    Position[2] = Z;
}


math::Vector4 BGE_NCP Node::GetPosition() const
{
    return Position;
}

} /* bakge */


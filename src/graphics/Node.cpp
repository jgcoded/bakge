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
    glGenBuffers(1, &Position);
}


Node::~Node()
{
    glDeleteBuffers(1, &Position);
}


Node* Node::Create(math::Scalar X, math::Scalar Y, math::Scalar Z)
{
    Node* N;

    N = new Node;
    if(N == NULL) {
        printf("Error allocating new node\n");
        return NULL;
    }

    N->SetPosition(X, Y, Z);

    return N;
}


Result Node::Bind() const
{
    GLint Program, Location;
    math::Vector4 Pos;

    /* Retrieve current shader program */
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0)
        return BGE_FAILURE;

    /* Retrieve location of the bge_Position vec4 */
    Location = glGetUniformLocation(Program, "bge_Position");
    if(Location < 0)
        return BGE_FAILURE;

    Pos = GetPosition();

    /* Assign this node's position as bge_Position */
    glUniform4dv(Location, 1, &Pos[0]);

    return BGE_SUCCESS;
}


Result Node::Unbind() const
{
    static const math::Vector4 Origin;
    GLint Program, Location;

    /* Retrieve current shader program */
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);
    if(Program == 0)
        return BGE_FAILURE;

    /* Retrieve location of the bge_Position vec4 */
    Location = glGetUniformLocation(Program, "bge_Position");
    if(Location < 0)
        return BGE_FAILURE;

    /* Assign origin position as bge_Position */
    glUniform4dv(Location, 1, &Origin[0]);

    return BGE_SUCCESS;
}


Result Node::Draw() const
{
    return BGE_SUCCESS;
}


void Node::SetPosition(math::Scalar X, math::Scalar Y, math::Scalar Z)
{
    math::Vector4 Point(X, Y, Z, 1);

    glBindBuffer(GL_ARRAY_BUFFER, Position);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Point[0]) * 4, &Point[0],
                                                    GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_DOUBLE, GL_FALSE, 0, 0);
}


math::Vector4 Node::GetPosition() const
{
    math::Vector4 Pos;
    math::Scalar* Data;

    glBindBuffer(GL_ARRAY_BUFFER, Position);
    Data = (math::Scalar*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    Pos[0] = Data[0];
    Pos[1] = Data[1];
    Pos[2] = Data[2];
    Pos[3] = Data[3];
    glUnmapBuffer(GL_ARRAY_BUFFER);

    return Pos;
}

} /* bakge */


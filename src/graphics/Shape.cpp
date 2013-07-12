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

Shape::Shape()
{
    Quadric = gluNewQuadric();
}


Shape::~Shape()
{
    if(Quadric != NULL)
        gluDeleteQuadric(Quadric);
}


Result Shape::DrawStyle(BGE_SHAPE_STYLE Style)
{
    switch(Style) {

    case BGE_SHAPE_STYLE_EDGE:
        gluQuadricDrawStyle(Quadric, GLU_SILHOUETTE);
        break;

    case BGE_SHAPE_STYLE_SOLID:
        gluQuadricDrawStyle(Quadric, GLU_FILL);
        break;

    case BGE_SHAPE_STYLE_WIREFRAME:
        gluQuadricDrawStyle(Quadric, GLU_LINE);
        break;

    case BGE_SHAPE_STYLE_POINTS:
        gluQuadricDrawStyle(Quadric, GLU_POINT);
        break;
    }

    return BGE_SUCCESS;
}


Result Shape::Bind() const
{
    GLint Program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &Program);

    GLint PositionsAttrib = glGetAttribLocation(Program, "bge_VertexArray");
    GLint NormalsAttrib = glGetAttribLocation(Program, "bge_NormalArray");

    glBindVertexArray(MeshVAO);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_POSITIONS]);
    glEnableVertexAttribArray(PositionsAttrib);
    glVertexAttribPointer(PositionsAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_NORMALS]);
    glEnableVertexAttribArray(NormalsAttrib);
    glVertexAttribPointer(NormalsAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    return Pawn::Bind();
}


Result Shape::Unbind() const
{
    glBindVertexArray(0);

    return Pawn::Unbind();
}

} /* bakge */

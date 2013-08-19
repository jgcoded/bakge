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

    Rectangle::Rectangle()
    {
    }

    Rectangle::~Rectangle()
    {
    }

    Rectangle* Rectangle::Create(Scalar Width, Scalar Height)
    {

        Rectangle* R = new Rectangle;

        if(R->CreateBuffers() != BGE_SUCCESS) {
            delete R;
            return NULL;
        }

        if(R->SetDimensions(Width, Height) != BGE_SUCCESS) {
            delete R;
            return NULL;
        }

    }

    Result Rectangle::SetDimensions(Scalar X, Scalar Y)
    {

        glDeleteBuffers(1, &MeshBuffers[MESH_BUFFER_POSITIONS]);
        glGenBuffers(1, &MeshBuffers[MESH_BUFFER_POSITIONS]);
        
        Scalar* Vertices[] = new Vertices[4 * 3];
    
        Vertices[0] = -Width / 2.0f;
        Vertices[1] = -Height / 2.0f;
        Vertices[2] = 0;
        Vertices[3] = -Width / 2.0f;
        Vertices[4] = +Height / 2.0f;
        Vertices[5] = 0;
        Vertices[6] = +Width / 2.0f;
        Vertices[7] = +Height / 2.0f;
        Vertices[8] = 0;
        Vertices[9] = +Width / 2.0;
        Vertices[10] = -Height / 2.0f;
        Vertices[11] = 0;

        glBindBuffer(GL_ARRAY_BUFFER, MeshBuffers[MESH_BUFFER_POSITIONS]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * 12, Vertices,
                                                            GL_STATIC_DRAW);
    
        Unbind()

        return BGE_SUCCESS;
    }

 } /* bakge */
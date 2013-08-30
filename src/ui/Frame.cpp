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

Frame::Frame()
{
}


Frame::~Frame()
{
}


Frame* Frame::Create(Scalar Width, Scalar Height)
{

    Frame* U = new Frame;

    U->NumIndices = 6;

    if(U->CreateBuffers() != BGE_SUCCESS) {
        delete U;
        return NULL;
    }

    if(U->SetDimensions(Width, Height) != BGE_SUCCESS) {
        delete U;
        return NULL;
    }

    U->AllocateGLBuffers();

    U->Unbind();

    U->SetPosition(0, 0, 0);

    return U;
}


Result Frame::Bind() const
{
    Node::Bind();
    Rectangle::Bind();

    return BGE_SUCCESS;
}


Result Frame::Unbind() const
{
    Node::Unbind();
    Rectangle::Unbind();

    return BGE_SUCCESS;
}

} /* bakge */

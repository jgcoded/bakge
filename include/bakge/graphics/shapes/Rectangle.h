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

#ifndef BAKGE_GRAPHICS_SHAPES_RECTANGLE_H
#define BAKGE_GRAPHICS_SHAPES_RECTANGLE_H

#include <bakge/Bakge.h>

namespace bakge
{

class BGE_API Rectangle : public Shape
{
	Vector4 Dimensions;

protected:
	Rectangle();

public:
	~Rectangle();

	BGE_FACTORY Rectangle* Create(Scalar Length, Scalar Width);

	Result SetDimensions(Scalar X, Scalar Y);

	BGE_INL Vector4 BGE_NCP GetDimensions() const
	{
		return Dimensions;
	}

}; /* Rectangle */ 

} /* bakge */
#endif
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
namespace math
{

Vector4::Vector4()
{
}


Vector4::Vector4(Scalar X, Scalar Y, Scalar Z, Scalar W)
{
    Val[0] = X;
    Val[1] = Y;
    Val[2] = Z;
    Val[3] = W;
}


Vector4::Vector4(Vector4 BGE_NCP Other)
{
	Val[0] = Other[0];
	Val[1] = Other[1];
	Val[2] = Other[2];
	Val[3] = Other[3];

}


Vector4::~Vector4()
{
}


Vector4 Point(Scalar X, Scalar Y, Scalar Z)
{
    return Vector4(X, Y, Z, 1);
}


Vector4 Vector(Scalar X, Scalar Y, Scalar Z)
{
    return Vector4(X, Y, Z, 0);
}


Vector4 UnitVector(Scalar X, Scalar Y, Scalar Z)
{
    Scalar Len = sqrt(X * X + Y * Y + Z * Z);
    return Vector4(X / Len, Y / Len, Z / Len, 0);
}


Scalar& Vector4::operator[](int BGE_NCP At)
{
    return Val[At];
}


Scalar BGE_NCP Vector4::operator[](int BGE_NCP At) const
{
    return Val[At];
}


Vector4 BGE_NCP Vector4::operator=(Vector4 BGE_NCP Other)
{
	Val[0] = Other[0];
	Val[1] = Other[1];
	Val[2] = Other[2];
	Val[3] = Other[3];

    return *this; /* Allow cascading assignment */
}


Vector4 BGE_NCP Vector4::operator+=(Vector4 BGE_NCP Other)
{
	/* A point plus a point is meaningless */
	if(Val[3] == 1 && Other[3] == 0 || Val[3] == 0 && Other[3] == 1 || Val[3] == 0 && Other[3] == 0)
	{
		Val[0] += Other[0];
		Val[1] += Other[1];
		Val[2] += Other[2];
	}

    return *this;
}


Vector4 BGE_NCP Vector4::operator-=(Vector4 BGE_NCP Other)
{
	/* A point plus a point is meaningless */
	if(Val[3] == 1 && Other[3] == 0 || Val[3] == 0 && Other[3] == 1 || Val[3] == 0 && Other[3] == 0)
	{
		Val[0] -= Other[0];
		Val[1] -= Other[1];
		Val[2] -= Other[2];
	}

    return *this;
}


Vector4 BGE_NCP Vector4::operator*=(Scalar BGE_NCP Value)
{
	if(Val[3] == 0) /* Multiplying a point is meaningless */
		Val[0] *= Value; /* Increase the magnitude */
	
	return *this;
}


Vector4 BGE_NCP Vector4::operator/=(Scalar BGE_NCP Value)
{
	if(Val[3] == 0) /* Dividing a point is meaningless */
		Val[0] /= Value; /* Decrease the magnitude */
		
    return *this;
}

bool BGE_NCP Vector4::operator==(Vector4 BGE_NCP Other)
{
	return (Val[0] == Other[0] && Val[1] == Other[1] && Val[2] == Other[2] && Val[3] == Other[3]);
}


void Vector4::Normalize()
{
	/* Gives a warning since there is a loss of data from converting Scalar(float) to int */
	Val[0] = GET_SIGN(Val[0]);
	Val[1] = GET_SIGN(Val[1]);
	Val[2] = GET_SIGN(Val[2]);

	/* Val[3] is what seperates this Vector4 from being a position */
}


Vector4 Vector4::Normalized() const
{
    return Vector4(*this);
}


Scalar Vector4::LengthSquared() const
{
    return Scalar(Val[0] * Val[0] + Val[1] * Val[1] + Val[2] * Val[2]);
}


Scalar Vector4::Length() const
{
    return sqrt(LengthSquared());
}


Vector4 operator+(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
	/* A point plus a point is meaningless */
	if(Left[3] == 1 && Right[3] == 0 || Left[3] == 0 && Right[3] == 1 || Left[3] == 0 && Right[3] == 0)
	{
		Vector4 newVector;
		newVector[0] = Left[0] + Right[0];
		newVector[1] = Left[1] + Right[1];
		newVector[2] = Left[2] + Right[2];
		newVector[3] = Left[3];
		return newVector;
	}

    return Vector4();
}


Vector4 operator-(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{

	/* A point minus a point is meaningless */
	if(Left[3] == 1 && Right[3] == 0 || Left[3] == 0 && Right[3] == 1 || Left[3] == 0 && Right[3] == 0)
	{
		Vector4 newVector;
		newVector[0] = Left[0] - Right[0];
		newVector[1] = Left[1] - Right[1];
		newVector[2] = Left[2] - Right[2];
		newVector[3] = 1;
		return newVector;
	}

    return Vector4();
}


Vector4 operator*(Vector4 BGE_NCP Left, Scalar BGE_NCP Right)
{
	Vector4 newVector;
	
	if(Left[3] == 0) /* Multiplying a point by a constant is meaningless */
	{
		newVector[0] = Left[0] * Right; /* Increase the magnitude */
		newVector[1] = Left[1];
		newVector[2] = Left[2];
		newVector[3] = Left[3];
	}

    return newVector;
}


Vector4 operator/(Vector4 BGE_NCP Left, Scalar BGE_NCP Right)
{
    Vector4 newVector;

	if(Left[3] == 0) /* Dividing a point by a constant is meaningless */
	{
		newVector[0] = Left[0] / Right; /* Decrease the Magnitude */
		newVector[1] = Left[1];
		newVector[2] = Left[2];
		newVector[3] = Left[3];
	}

    return newVector;
}

bool BGE_NCP operator==(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
	return (Left[0] == Right[0] && Left[1] == Right[1] && Left[2] == Right[2] && Left[3] == Right[3]);
}


Scalar Dot(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
   return ((((Left[0] * Right[0]) + (Left[1] * Right[1])) + (Left[2] * Right[2])) + (Left[3] * Right[3]));

}


Vector4 Cross(Vector4 BGE_NCP Left, Vector4 BGE_NCP Right)
{
    Vector4 Cross;

	Cross[0] = (Left[1] * Right[2]) - (Left[2] * Right[1]);
	Cross[1] = (Left[2] * Right[0]) - (Left[0] * Right[2]);
	Cross[2] = (Left[0] * Right[1]) - (Left[1] * Right[0]);
	Cross[3] = Left[3];

	return Cross;
}

} /* math */
} /* bakge */


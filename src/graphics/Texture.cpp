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

Texture::Texture()
{
}


Texture::~Texture()
{
	glDeleteTextures(1, &this->texture[0]);

}

Result Texture::Bind() const
{
	return 0;
}

Result Texture::Unbind() const
{
	return 0;
}

Texture* Texture::Create(int Width, int Height, GLint Format, GLenum Type,
                                                              void* Data)
{
	int error;
	Texture* newTexture = new Texture;
	
	newTexture->width = Width;
	newTexture->height = Height;
	
	glGenTextures(1, &newTexture->texture[0]); // generate an "ID" that we can reference

	if((error = glGetError()) != GL_NO_ERROR) // Check if Generate worked
		perror("GL Generate Texture Error");

	glBindTexture(GL_TEXTURE_2D, newTexture->texture[0]); // bind the texture as 2D, code below applies only to this texture

	if((error = glGetError()) != GL_NO_ERROR) // Check if the binding worked
		perror("GL Bind To Texture Error");


	/* TEXTURE PARAMETERS
	 */

	/* GL_MODULATE: blends the texture with whatever is underneath
	*  GL_DECAL: replaces whatever is underneath the texture
	*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 


	/* See: http://www.opengl.org/sdk/docs/man/xhtml/glTexParameter.xml
	 * For definitions of the parameters in glTexParamterf
	*/

	// Nearest filtered texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// GL_CLAMP_TO_EDGE can also be used instead of GL_REPEAT
	// but Visual Studio tells me that const doesn't exist

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	/* END TEXTURE PARAMETERS
	 */

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, Format, Type, Data);

	if((error = glGetError()) != GL_NO_ERROR) // Error making the texture
		perror("GL TexImage Error");

	free(Data);

    return newTexture;
}


void Texture::Draw()
{

	// Following the guide on the swiftless website mentioned in bakge/texture.h

	int error;

	glEnable(GL_TEXTURE_2D);

	if((error = glGetError()) != GL_NO_ERROR) // Error enabling 2d textures
		perror("GL Enable Texture 2D Error");

	glBindTexture(GL_TEXTURE_2D, this->texture[0]);

	if((error = glGetError()) != GL_NO_ERROR) // Error binding to the texture 
		perror("GL Draw Binding Error");
	
	glBegin(GL_QUADS);

	// Map the texture coordinates with the vertex coordinates

	
    glTexCoord2d(0.0,0.0); 
	glVertex2d(-.5,-.5); //with our vertices we have to assign a texcoord

    glTexCoord2d(1.0,0.0); 
	glVertex2d(+.5,-.5); //so that our texture has some points to draw to
    
	glTexCoord2d(1.0,1.0); 
	glVertex2d(+.5,+.5);

    glTexCoord2d(0.0,1.0); 
	glVertex2d(-.5,+.5);

    glEnd();

	


}


} /* bakge */


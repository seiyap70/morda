/* The MIT License:

Copyright (c) 2012 Ivan Gagis <igagis@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. */

// Home page: http://morda.googlecode.com

/**
 * @author Ivan Gagis <igagis@gmail.com>
 */

#pragma once

#include <GL/glew.h>

#include <ting/debug.hpp>

#include <tride/Vector3.hpp>

#include "Image.hpp"



namespace morda{



class GLTexture {
	//no copying
	GLTexture(const GLTexture& tex);

	//no assigning
	GLTexture& operator=(const GLTexture& tex);

	GLuint tex;

	tride::Vec2f dim;

public:
	inline GLTexture(const Image& image, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR){
		this->Init(image, minFilter, magFilter);
	}

	inline GLTexture() :
			tex(0)
	{}

	~GLTexture()throw(){
		this->Destroy();
	}

	void Init(const Image& image, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR);

	inline void Bind()const{
		ASSERT(glGetError() == GL_NO_ERROR)
		glBindTexture(GL_TEXTURE_2D, this->tex);
		ASSERT(glGetError() == GL_NO_ERROR)
	}
	
	inline void Bind(unsigned texUnitNum)const{
		ASSERT(glGetError() == GL_NO_ERROR)
		glActiveTexture(GL_TEXTURE0 + texUnitNum);
		ASSERT(glGetError() == GL_NO_ERROR)
		glBindTexture(GL_TEXTURE_2D, this->tex);
		ASSERT(glGetError() == GL_NO_ERROR)
	}

	inline tride::Vec2f Dim()const throw(){
		return this->dim;
	}

private:
	void Destroy()throw(){
		glDeleteTextures(1, &this->tex);
	}
};



}//~namespace
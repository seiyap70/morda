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

#include <string>

#include <stob/dom.hpp>

#include "../resman/Resource.hpp"

#include "../util/TexFont.hpp"



namespace morda{



class ResFont : public morda::Resource{
	friend class morda::ResourceManager;

	morda::TexFont font;

	ResFont(ting::fs::File& fi, const std::wstring& chars, unsigned size, unsigned outline) :
			font(fi, chars.c_str(), size, outline)
	{}

public:
	inline ~ResFont()throw(){}

	inline const morda::TexFont& Fnt()throw(){
		return this->font;
	}
	
private:
	static ting::Ref<ResFont> Load(const stob::Node* el, ting::fs::File &fi);
};



}//~namespace
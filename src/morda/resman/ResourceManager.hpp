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

#include <map>

#include <ting/Ref.hpp>
#include <ting/fs/File.hpp>

#include <stob/dom.hpp>

#include "../Exc.hpp"
#include "Resource.hpp"


namespace morda{



class ResourceManager{
    friend class Resource;

	typedef Resource::T_ResMap T_ResMap;
	
	ting::Ref<Resource::ResMapRC> resMap;

	class ResPackEntry{
	public:
		ting::Ptr<ting::fs::File> fi;
		ting::Ptr<const stob::Node> resScript;
	};

	typedef std::vector<ResPackEntry> T_ResPackList;

	//list of mounted resource packs
	T_ResPackList resPacks;


	class FindInScriptRet{
	public:
		FindInScriptRet(ResPackEntry* resPack, const stob::Node* element, const stob::Node* nameVal) :
				rp(resPack),
				e(element),
				nameVal(nameVal)
		{}

		ResPackEntry* rp;
		const stob::Node* e;
		const stob::Node* nameVal;
	};

	FindInScriptRet FindResourceInScript(const std::string& resName);

	template <class T> ting::Ref<T> FindResourceInResMap(const std::string& resName);

	//Add resource to resources map
	void AddResource(const ting::Ref<Resource>& res, const stob::Node* node);

	
public:
	class Exc : public morda::Exc{
	public:
		inline Exc(const std::string& message) :
				morda::Exc(message)
		{}
	};
	
	inline ResourceManager() :
			resMap(Resource::ResMapRC::New())
	{}

	virtual ~ResourceManager(){}

	void MountResPack(ting::Ptr<ting::fs::File> fi);

	template <class T> ting::Ref<T> Load(const std::string& resName);
};



template <class T> ting::Ref<T> ResourceManager::FindResourceInResMap(const std::string& resName){
	T_ResMap::iterator i = this->resMap->rm.find(&resName);
	if(i != this->resMap->rm.end()){
		ting::Ref<Resource> r((*i).second);
		ASSERT(r.DynamicCast<T>().IsValid())
		return r.StaticCast<T>();
	}
	return ting::Ref<T>();//no resource found with given name, return invalid reference
}



template <class T> ting::Ref<T> ResourceManager::Load(const std::string& resName){
//	TRACE(<< "ResMan::Load(): enter" << std::endl)
	if(ting::Ref<T> r = this->FindResourceInResMap<T>(resName)){
//		TRACE(<< "ResManHGE::Load(): resource found in map" << std::endl)
		return r;
	}

//	TRACE(<< "ResMan::Load(): searching for resource in script..." << std::endl)
	FindInScriptRet ret = this->FindResourceInScript(resName);
	ASSERT(ret.e)
	ASSERT(ret.nameVal)
	ASSERT(ret.rp)
	ASSERT(ret.rp->fi)

//	TRACE(<< "ResMan::Load(): resource found in script" << std::endl)

	ting::Ref<T> resource = T::Load(ret.e, *(ret.rp->fi));

	this->AddResource(resource, ret.nameVal);

//	TRACE(<< "ResMan::LoadTexture(): exit" << std::endl)
	return resource;
}



}//~namespace
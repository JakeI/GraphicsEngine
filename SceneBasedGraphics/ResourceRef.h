#pragma once

#include "StdAfx.h"
#include "Resource.h"
#include "ResourceManager.h"

// stores either a path to a resource that can be managed in the Resource Manager
// or a pointer to a resource this allows me Process all resources the same way, 
// (independent of wheather they are loaded from a file and through the resource 
//  Manager or if they are generated at runtime and managed by an idivitual scene)
class ResourceRef
{
private:

	

public:

	std::string path;
	Resource* ptr;

	inline bool usesPath() const { return ptr == nullptr && path != ""; }
	ResourceRef(const std::string & p) : path(p), ptr(nullptr) {}
	ResourceRef(Resource* p) : path(""), ptr(p) {}
	ResourceRef() : path(""), ptr(nullptr) {}
	inline bool wasInitialised() const { return ptr != nullptr || path != ""; }
	inline bool operator== (const ResourceRef & ref) const { return ptr == ref.ptr || path == ref.path; }
};


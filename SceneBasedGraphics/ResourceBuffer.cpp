#include "ResourceBuffer.h"

Resource* ResourceBuffer::prepareGet(ResourceRef* ref, bool afterInit) {
	if (ref->usesPath()) {
		prepared.push_back(ref->path);
		return manager->prepareGetResource(ref->path, afterInit);
	}
	else
		return ref->ptr;
}

Resource* ResourceBuffer::prepareGet(const std::string & path, bool afterInit) {
	prepared.push_back(path);
	return manager->prepareGetResource(path, afterInit);
}


void ResourceBuffer::releaseAll() {
	for (std::string & s : prepared) 
		manager->releaseResource(s);
}


ResourceBuffer::ResourceBuffer(ResourceManager* rm) :
	manager(rm)
{
}


ResourceBuffer::~ResourceBuffer()
{
}

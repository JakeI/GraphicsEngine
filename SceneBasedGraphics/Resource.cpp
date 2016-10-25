#include "Resource.h"

#include "Mesh.h"
#include "Model.h"
#include "Texture.h"
#include "Font.h"
#include "Atlas.h"
#include "Shader.h"

ResourceRegister* ResourceRegister::resourceRegister = new ResourceRegister();

ResourceRegister::ResourceRegister() : 
	idMap({}), 
	allocMap({}), 
	nextUnusedType(1) 
{
	maybeRegisterType("meshs", Mesh::alloc);
	maybeRegisterType("models", Model::alloc);
	maybeRegisterType("textures", Texture::alloc);
	maybeRegisterType("fonts", Font::alloc);
	maybeRegisterType("atlases", Atlas::alloc);
	maybeRegisterType("shaders", Shader::alloc);
}


void ResourceRegister::maybeRegisterType(const std::string & name, AllocationFunc allocationFunc) {
	if (idMap.find(name) == idMap.end()) { // if name is not in idMap
		idMap[name] = nextUnusedType;
		allocMap[nextUnusedType] = allocationFunc;
		nextUnusedType += 1;
	}
}

ResourceRegister::ResourceType  ResourceRegister::getResType(const std::string & path) {
	std::string p(path);
	replace(p.begin(), p.end(), '\\', '/');

	// expects resources to be in a folder called "res" and than
	// in folders coresponding to the resource types

	std::vector<std::string> folders;
	{
		std::stringstream ss(p);
		std::string f;
		while (getline(ss, f, '/'))
			folders.push_back(f);
	}

	if (folders.size() == 0)
		return 0;

	std::vector<std::string>::iterator it = std::find(folders.begin(), folders.end(), std::string("res"));

	bool correctlyFormatted = true;

	correctlyFormatted = correctlyFormatted && it != folders.end();
	if (correctlyFormatted) {
		it++;
		correctlyFormatted = correctlyFormatted && it != folders.end();
	}

	if (!correctlyFormatted)
		return 0;

	return getResTypeByKey(*it);
}

ResourceRegister::ResourceType  ResourceRegister::getResTypeByKey(const std::string & key) {
	auto itResType = idMap.find(key);
	if (itResType != idMap.end())
		return itResType->second;
	else
		return 0;
}

Resource*  ResourceRegister::loadResource(const std::string & path) {
	ResourceType resType = getResType(path);
	auto itAllocMap = allocMap.find(resType);
	if (itAllocMap != allocMap.end()) {
		return itAllocMap->second(path);
	}
	else {
		ilog->printError("coudn't load resource: '" + path + "' because it's type wasn't found in the list of registert types \n"
			"(error noticed in funciton Resource::loadResouce(const std::string & path) )");
		return nullptr;
	}
}

Resource::Resource(const std::string & path) :
	type(resReg->getResType(path)),
	wasInitialized(false)
{
}

Resource::Resource(ResourceRegister::ResourceType type) :
	type(type),
	wasInitialized(false)
{

}


Resource::~Resource()
{
}

bool Resource::init(const std::string & name) { 
	if (!wasInitialized) { 
		init_resource(name); 
		wasInitialized = true;
		return true;
	}
	else
		return false;
}
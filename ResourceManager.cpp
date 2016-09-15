#include "ResourceManager.h"

ResourceManager* ResourceManager::globalResourceManager = new ResourceManager;

ResourceManager::ResourceType ResourceManager::getResourceType(const std::string & path) {
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
		return RESOURCE_ERROR;

	std::vector<std::string>::iterator it = std::find(folders.begin(), folders.end(), std::string("res"));

	bool correctlyFormatted = true;

	correctlyFormatted = correctlyFormatted && it != folders.end();
	it++;
	correctlyFormatted = correctlyFormatted && it != folders.end();

	if (!correctlyFormatted)
		return RESOURCE_ERROR;


	if (*it == std::string("shaders"))
		return SHADER;
	else if (*it == std::string("textures"))
		return TEXTURE;
	else if (*it == std::string("meshs"))
		return MESH;
	else if (*it == std::string("models"))
		return MODEL;
	else if (*it == std::string("fonts"))
		return FONT;

	return RESOURCE_ERROR;
	
}

/*std::string & ResourceManager::replace(std::string & in, char c, char d) {
	for (int i = 0; i < in.length; i++) {
		if (in[i] == c)
			in[i] = d;
	}
	return 
}*/

void ResourceManager::LoadResource(const std::string & path, ResourceRecord* rr) {

	ResourceType rt = getResourceType(path);
	switch (rt) {
	case RESOURCE_ERROR:
		rr->type = RESOURCE_ERROR;
		ilog->printError("Couldn't load the resource '" + path + "' because it is formatted incorrectly");
		return;
	case SHADER:
		rr->set(SHADER, (void*) new Shader(path));
		return;
	case TEXTURE:
		rr->set(TEXTURE, new Texture(path));
		return;
	case MESH:
		rr->set(MODEL, (void*) Mesh::readMesh(path));
		return;
	case MODEL:
		rr->type = RESOURCE_ERROR;
		ilog->printError("Can't load resource: '" + path + "' because resources of type MODEL are not yet implemented");
		return;
	case FONT:
		rr->set(FONT, (void*) new Font(path));
		return;
	}

	
}

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

std::map<std::string, ResourceManager::ResourceRecord>::iterator 
ResourceManager::find(const std::string & path) {
	std::string p(path);
	replace(p.begin(), p.end(), '\\', '/');
	return resourceTable.find(p);
}

void ResourceManager::prepareResource(const std::string & path) {
	std::map<std::string, ResourceRecord>::iterator it = find(path);
	if (it == resourceTable.end()) { // Resource is not yet loaded
		ResourceRecord rr;
		LoadResource(path, &rr);
		rr.useCounter = 1;
		resourceTable[path] = rr;
	} else {
		it->second.useCounter++;
	}

}

void ResourceManager::prepareResources(const std::string * paths, int resourceCount)
{
	for (int i = 0; i < resourceCount; i++)
		prepareResource(paths[i]);
}

void* ResourceManager::getResource(const std::string & path, ResourceType *resourceType) {
	std::map<std::string, ResourceRecord>::iterator it = find(path);
	bool b = it != resourceTable.end();
	if (b) { //Was found
		if (resourceType != NULL)
			*resourceType = it->second.type;
		return it->second.res;
	}
	return NULL;
}

void ResourceManager::releaseResource(const std::string & path) {
	std::map<std::string, ResourceRecord>::iterator it = find(path);
	if (it != resourceTable.end()) { //Was found
		if (it->second.useCounter <= 1) {
			void* ptr = it->second.res;
			resourceTable.erase(it);
			delete ptr;
		} else {
			it->second.useCounter--;
		}
	} else {
		ilog->printError("Failed to release resource '" + path + "' because it could not be found in the list");
	}
}

void ResourceManager::releaseResources(const std::string * paths, int resourceCount)
{
	for (int i = 0; i < resourceCount; i++)
		releaseResource(paths[i]);
}

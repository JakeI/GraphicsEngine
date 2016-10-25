#include "ResourceManager.h"



ResourceManager* ResourceManager::globalResourceManager = new ResourceManager;

std::string ResourceManager::getLoadPath(const std::string & path) {
	std::string key = path.substr(0, path.find('/'));
	if (key == "res")
		return resPath + path;
	else if (key == "ass")
		return assPath + path;
	else
		ilog->printError("the path: '" + path +"' starts nighter in 'res' nor in 'ass'");
	return path;
}

void ResourceManager::LoadResource(const std::string & path, ResourceRecord* rr, bool afterInit) {

	std::string loadPath = getLoadPath(path);

	rr->set(resReg->loadResource(loadPath));	
	if (wasInitialized || afterInit)
		rr->res->init(loadPath);
}

ResourceManager::ResourceManager() :
	wasInitialized(false)
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

void ResourceManager::prepareResource(const std::string & path, bool afterInit) {
	std::map<std::string, ResourceRecord>::iterator it = find(path);
	if (it == resourceTable.end()) { // Resource is not yet loaded
		ResourceRecord rr;
		LoadResource(path, &rr, afterInit);
		rr.useCounter = 1;
		resourceTable[path] = rr;
	} else {
		it->second.useCounter++;
	}

}

void ResourceManager::prepareResources(const std::string * paths, int resourceCount, bool afterInit)
{
	for (int i = 0; i < resourceCount; i++)
		prepareResource(paths[i], afterInit);
}

Resource* ResourceManager::getResource(const std::string & path, ResourceRegister::ResourceType *resourceType) {
	auto it = find(path);
	if (it != resourceTable.end()) { //Was found
		if (resourceType != NULL)
			*resourceType = it->second.res->getType();
		return it->second.res;
	}
	return NULL;
}

Resource* ResourceManager::prepareGetResource(const std::string & path, bool afterInit, ResourceRegister::ResourceType* resourceType) {
	prepareResource(path, afterInit);
	return getResource(path, resourceType);
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

std::string ResourceManager::to_string() {
	std::stringstream ss;

	ss << " +++ Resource Manager Log +++" << std::endl
		<< "Number of resources loaded = " << resourceTable.size() << std::endl
		<< "Key | type | uses" << std::endl;

	for (auto it : resourceTable)
		ss << it.first << " | " << it.second.res->getType() << " | " << it.second.useCounter << std::endl;

	return ss.str();
}

void ResourceManager::init() {
	bool allInitialised = false;

	while (!allInitialised) {
		allInitialised = true;

		while (!wasInitialized) {
			wasInitialized = true;

			for (auto it : resourceTable)
				wasInitialized = !it.second.res->init(getLoadPath(it.first)) && wasInitialized;
		}

		for (auto it : resourceTable)
			allInitialised = !it.second.res->init(getLoadPath(it.first)) && allInitialised;
	}
}

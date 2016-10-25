#pragma once

#include "ResourceManager.h"
#include "ResourceRef.h"

// keepts a record of Resources got through the Resource Manager.
// All the stored resources can than be released as one bundel
class ResourceBuffer
{
private:

	std::list<std::string> prepared;
	ResourceManager* manager;

public:

	Resource* prepareGet(ResourceRef* ref, bool afterInit = false);
	Resource* prepareGet(const std::string & path, bool afterInit = false);

	void releaseAll();

	ResourceBuffer(ResourceManager* rm);
	~ResourceBuffer();
};


#pragma once

#include "StdAfx.h"
#include "InfoLog.h"
#include "Resource.h"


class ResourceManager //TODO: add a init method to this, resources that are prepared before the init method is called are than just stored as refrences (and allocated during the init methode)
{
private:

	struct ResourceRecord {
		int useCounter;
		Resource *res;
		ResourceRecord() {
			useCounter = 0;
			res = nullptr;
		}
		void set(Resource *res) {
			useCounter = 0;
			this->res = res;
		}
	};

	std::map<std::string, ResourceRecord> resourceTable;

	std::map<std::string, ResourceRecord>::iterator find(const std::string & path);

	void LoadResource(const std::string & path, ResourceRecord* rr, bool afterInit = false);
	std::string getLoadPath(const std::string & path); // resPath or assPath to the front of path

	bool wasInitialized; // remembers if the init function was called / if the elements have been initialized

public:

	ResourceManager();
	~ResourceManager();

	void prepareResource(const std::string & path, bool afterInit = false);
	void prepareResources(const std::string * paths, int resourceCount, bool afterInit = false);
	Resource* getResource(const std::string & path, ResourceRegister::ResourceType *resourceType = NULL);
	Resource* prepareGetResource(const std::string & path, bool afterInit = false, ResourceRegister::ResourceType *resourceType = NULL);
	void releaseResource(const std::string & path);
	void releaseResources(const std::string * paths, int resourceCount);

	std::string to_string();

	void init();

	std::string resPath; // path added to resource keys starting with res/
	std::string assPath; // path added to resources starting with ass/
	static ResourceManager* globalResourceManager;
};

#define resm (ResourceManager::globalResourceManager)

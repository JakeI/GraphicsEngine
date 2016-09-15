#pragma once

#include "StdAfx.h"
#include "InfoLog.h"
#include "Shader.h"
#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Font.h"


class ResourceManager
{
public:

	enum ResourceType { RESOURCE_ERROR, SHADER, TEXTURE, MESH, MODEL, FONT };

private:

	struct ResourceRecord {
		int useCounter;
		ResourceType type;
		void *res;
		ResourceRecord() {
			useCounter = 0;
			type = RESOURCE_ERROR;
			res = nullptr;
		}
		void set(ResourceType type, void *res) {
			useCounter = 0;
			this->type = type;
			this->res = res;
		}
	};

	std::map<std::string, ResourceRecord> resourceTable;

	std::map<std::string, ResourceRecord>::iterator find(const std::string & path);

	static ResourceType getResourceType(const std::string & path);
	static void LoadResource(const std::string & path, ResourceRecord* rr);

	//static std::string & replace(std::string & in, char c, char d); // replaces all chars c in in by char d

public:

	ResourceManager();
	~ResourceManager();

	void prepareResource(const std::string & path);
	void prepareResources(const std::string * paths, int resourceCount);
	void* getResource(const std::string & path, ResourceType *resourceType = NULL);
	void releaseResource(const std::string & path);
	void releaseResources(const std::string * paths, int resourceCount);

	static ResourceManager* globalResourceManager;
};

#define resm (ResourceManager::globalResourceManager)

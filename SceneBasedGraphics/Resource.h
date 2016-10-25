#pragma once

#include "StdAfx.h"
#include "InfoLog.h"

class Resource; // forward declaration

// Registers possible resource types and allows access to that data
class ResourceRegister {
public:

	typedef short ResourceType; // a identifier for a resource type 0 and negative means an error
	typedef Resource* (*AllocationFunc)(const std::string &); // static function that allocateds a spesific Resource before glewInit() was called

private:

	//		 res_identifier, key_of it 
	std::map<std::string, ResourceType> idMap;
	//		 key, function that allocates memory for the new element  
	std::map<ResourceType, AllocationFunc> allocMap;
	ResourceType nextUnusedType; // the next ResourceType avilable as an identifier

public:


	ResourceType getResType(const std::string & path); // reads XXX in the path = "res/XXX/YYY[.ZZZ]" and returnes the corresponding type
	ResourceType getResTypeByKey(const std::string & key); // key needs to be the key that was registerd and would be expected as XXX in the getResType functions

	void maybeRegisterType(const std::string & name, AllocationFunc allocationFunc); // checks if name already is a type, if not it registers the type
	Resource* loadResource(const std::string & path); // called by ResourceManager class to allocate a new object that fits to this path

	ResourceRegister();
	~ResourceRegister() {}

	static ResourceRegister* resourceRegister; // global instancce of the resource register
};

#define resReg	(ResourceRegister::resourceRegister)


// Stores a spesific type of Resource that can be managed in the resource tabel
// static parts allow the registration for types and their allocation functions
class Resource
{
private:

	ResourceRegister::ResourceType type; // the type of this resource
	
protected:
	
	bool wasInitialized;

public:

	ResourceRegister::ResourceType getType() { return type; }

	Resource(const std::string & path);
	Resource::Resource(ResourceRegister::ResourceType type);
	Resource() : type(0) {} // call this constructor if the Resource will not be loaded using the resource manager
	~Resource();

	virtual void init_resource(const std::string & name) {} // override this function and use it to upload data to graphics memory (will be called after glewInit)
	bool init(const std::string & name); // calles the init_resource functions if needed (returns true if the component was initialised, false if it already had been initialised)
};



#pragma once

#include "ResourceManager.h"

class ResourceGetter
{
protected:

	std::list<std::string> prepared;
	ResourceManager* manager;

public:

	class Ref {
	public:
		std::string path;
		void* ptr;
		inline bool usesPath() { return ptr == nullptr && path != ""; }
		Ref(std::string & p) : path(p), ptr(nullptr) {}
		Ref(void* p) : path(""), ptr(p) {}
		Ref() : path(""), ptr(nullptr) {}
		inline bool wasInitialised() { return ptr != nullptr || path != ""; }
		inline bool operator== (const Ref & ref) { return ptr == ref.ptr || path == ref.path; }
	};

	void* prepareGet(Ref* ref) {
		if (ref->usesPath()) {
			prepared.push_back(ref->path);
			manager->prepareResource(ref->path);
			return manager->getResource(ref->path);
		} else {
			return ref->ptr;
		}
	}

	void releaseAll() {
		for (std::string & s : prepared) {
			manager->releaseResource(s);
		}
	}

	void releaseLast() {
		manager->releaseResource(prepared.back());
		prepared.pop_back();
	}

	ResourceGetter(ResourceManager* rm) : manager(rm) {}
	~ResourceGetter() {}
};

#define ResourceRef ResourceGetter::Ref


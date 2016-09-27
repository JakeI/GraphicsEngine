#pragma once

#include "StdAfx.h"
#include "RenderMode.h"
#include "ResourceGetter.h"
#include "Strings.h"
#include "Mesh.h"
#include "Texture.h"

using namespace rem;

class Mdl {
private:

	void read(const std::string & path);

public:
	struct Atribute {
		int location;
		int start;
		int dim;
		Atribute() { location = -1; start = -1; dim = -1; }
		Atribute(int location, int start, int dim);
		void set(int location, int start, int dim);
		inline bool isUsed() { return location != -1 && start != -1 && dim != -1; }
	};

	struct MeshLayout {
		ResourceRef meshRef;
		std::list<Atribute> atributes;
		int stride;
		MeshLayout() : meshRef(), atributes(), stride(0) {}
		MeshLayout(ResourceRef mesh, int stride) : meshRef(mesh), atributes(), stride(stride) {}
		MeshLayout(std::string & line) { read(line); }
		void read(std::string & line);
		void setGLDataPtrs(Mesh* myMesh);
		void enableAtribArrays();
		void disableAtribArrays();
	};

	class Stage {
	private:

		template <typename T>
		void setValue(const std::map<std::string, T> & map, T* value, const std::string & line);

		const static std::map<std::string, RenderMode> renderModeMap;
		void readMode(std::string & line);
		const static std::map<std::string, GLenum> primativeTypeMap;
		void readPrimative(std::string & line);
		static std::string readRefrence(std::string & line);
		void readShader(std::string & line);
		void readTexture(std::string & line);
		void readRange(std::string & line);
		void readMesh(std::string & line);
	public:
		RenderMode mode;
		GLenum primative;
		ResourceRef shaderRef;
		ResourceRef textureRef;
		std::list<MeshLayout> meshLayouts;
		int begin, end;
		ResourceRef meshLenRef;
		Stage();
		Stage(RenderMode m, GLenum p, ResourceRef sr, ResourceRef tr, int b, int e) :
			mode(m), primative(p), shaderRef(sr), textureRef(tr), begin(b), end(e), meshLenRef() {}
		void readStage(std::ifstream & in);
		inline bool usesMeshLenRef() { return meshLenRef.wasInitialised() && end == -1; }
	};

	std::list<Stage> stages;

	Mdl(const std::string & path);
	Mdl() {}
	~Mdl() {}
};
#include "Model.h"
#include "Entity.h"

Model::~Model() {
	resGet.releaseAll();
}

void Model::render(RenderMode mode, Entity* componentBuffer, void* param) {
	std::list<Pair>::iterator it = Model::find(mode, renderMap);
	if (it != renderMap.end()) {
		it->second.shader->use();

		componentBuffer->uploadUniforms(it->second.shader, mode, param);

		glBindVertexArray(it->second.vao);

		if(it->second.texture != nullptr)
			it->second.texture->bind(GL_TEXTURE_2D);

		for (auto location : it->second.usedLocations) 
			glEnableVertexAttribArray(location);

		glDrawArrays(it->second.primative, it->second.begin, it->second.end);

		for (auto location : it->second.usedLocations) 
			glDisableVertexAttribArray(location);

		if(it->second.texture != nullptr)
			glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);
	}
}

void Model::setUp(const Mdl* mdl) {
	
	for (auto stage : mdl->stages) {

		ModeRenderParam mrp;

		mrp.begin = stage.begin;
		mrp.primative = stage.primative;
		mrp.shader = (Shader*)resGet.prepareGet(&stage.shaderRef);
		mrp.texture = (Texture*)resGet.prepareGet(&stage.textureRef);

		glGenVertexArrays(1, &mrp.vao);
		glBindVertexArray(mrp.vao);

		for (auto meshLayout : stage.meshLayouts) for (auto attribute : meshLayout.atributes)
			mrp.usedLocations.push_back(attribute.location);

		for (auto meshLayout : stage.meshLayouts) meshLayout.enableAtribArrays();
		for (auto meshLayout : stage.meshLayouts) meshLayout.setGLDataPtrs((Mesh*)resGet.prepareGet(&meshLayout.meshRef));
		for (auto meshLayout : stage.meshLayouts) meshLayout.disableAtribArrays();

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (stage.usesMeshLenRef()) {
			for (auto meshLayout : stage.meshLayouts)
				if (stage.meshLenRef == meshLayout.meshRef) {
					Mesh* mesh = (Mesh*)resGet.prepareGet(&meshLayout.meshRef);
					mrp.end = mesh->size / meshLayout.stride;
					if (meshLayout.meshRef.usesPath())
						resGet.releaseLast();
					break;
				}
		}
		else mrp.end = stage.end;

		Pair p;
		p.first = stage.mode;
		p.second = mrp;
		renderMap.push_back(p);
		//renderMap[stage.mode] = mrp;
	}

	glBindVertexArray(0);
}

Model::Model(const std::string & path) : resGet(resm) {
	Mdl mdl(path);
	setUp(&mdl);
}

Model::Model(const Mdl* mdl) : resGet(resm) {
	setUp(mdl);
}

Model::Model() : resGet(resm) {}

void Model::setTexturePtr(RenderMode mode, Texture* texture) {
	std::list<Pair>::iterator it = Model::find(mode, renderMap);
	if (it != renderMap.end())
		it->second.texture = texture;
}


void Model::setRange(RenderMode mode, int begin, int end) {
	std::list<Pair>::iterator it = Model::find(mode, renderMap);
	if (it != renderMap.end())
		it->second.setRange(begin, end);
}
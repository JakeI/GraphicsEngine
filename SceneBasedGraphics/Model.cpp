#include "Model.h"
#include "Entity.h"

void Model::init_resource(const std::string & path) {
	Mdl mdl(path);
	setUp(&mdl);
}

Model::~Model()
{
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
		mrp.shader = (Shader*)resBuffer.prepareGet(&stage.shaderRef, true);
		mrp.texture = (Texture*)resBuffer.prepareGet(&stage.textureRef, true);

		glGenVertexArrays(1, &mrp.vao);
		glBindVertexArray(mrp.vao);

		for (auto meshLayout : stage.meshLayouts) for (auto attribute : meshLayout.atributes)
			mrp.usedLocations.push_back(attribute.location);

		for (auto meshLayout : stage.meshLayouts) meshLayout.enableAtribArrays();
		for (auto meshLayout : stage.meshLayouts) meshLayout.setGLDataPtrs((Mesh*)resBuffer.prepareGet(&meshLayout.meshRef, true));
		for (auto meshLayout : stage.meshLayouts) meshLayout.disableAtribArrays();

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// load the range which will be renderd. if the range end is specified using the size of the mesh this assumes that the mesh will also be in the stage
		// if it is so, the resm->prepareGetResource call will not result in any memory allocations / file reads because the resource has already been prepared above
		if (stage.usesMeshLenRef()) {
			for (auto meshLayout : stage.meshLayouts)
				if (stage.meshLenRef == meshLayout.meshRef) {
					Mesh* mesh = (Mesh*)(meshLayout.meshRef.usesPath() ? 
						resm->prepareGetResource(meshLayout.meshRef.path, true) : meshLayout.meshRef.ptr);
					mrp.end = mesh->size / meshLayout.stride;
					if (meshLayout.meshRef.usesPath())
						resm->releaseResource(meshLayout.meshRef.path);
					break;
				}
		}
		else mrp.end = stage.end;

		Pair p;
		p.first = stage.mode;
		p.second = mrp;
		renderMap.push_back(p);
	}

	glBindVertexArray(0);
}

Model::Model(const std::string & path) : 
	Resource(path),
	resBuffer(resm)
{
	// call init(const std::string & path) to load this
}

Model::Model(const Mdl* mdl) :
	Resource(), // resource will not be usesd
	resBuffer(resm)
{
	setUp(mdl);
}

Model::Model() : resBuffer(resm) {}

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
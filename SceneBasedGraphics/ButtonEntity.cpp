#include "ButtonEntity.h"

ButtonEntity::ButtonModel::ButtonModel() {
	this->textureMesh = new Mesh();
}

ButtonEntity::ButtonModel::~ButtonModel() {
	delete textureMesh;
}

void ButtonEntity::ButtonModel::init() {
	
	Mdl mdl;

	std::string shader("res/shaders/textured"), mesh("res/meshs/quad.mesh");
	Mdl::Stage full(FULL, GL_QUADS, ResourceRef(shader), ResourceRef(), 0, 4);
	Mdl::MeshLayout positions(ResourceRef(mesh), 2 * sizeof(float));
	positions.atributes.push_back(Mdl::Atribute(0, 0, 2));
	full.meshLayouts.push_back(positions);
	Mdl::MeshLayout textureCoords(ResourceRef(textureMesh), 2 * sizeof(float));
	textureCoords.atributes.push_back(Mdl::Atribute(3, 0, 2));
	full.meshLayouts.push_back(textureCoords);

	mdl.stages.push_back(full);

	std::string uniShader("res/shaders/uniformColor");
	Mdl::Stage uniform(UNIFORM, GL_QUADS, ResourceRef(uniShader), ResourceRef(), 0, 4);
	uniform.meshLayouts.push_back(positions);

	mdl.stages.push_back(uniform);

	setUp(&mdl);
}

ButtonEntity::ButtonEntity(const std::string & atlasPath) : ModelEntity(new ButtonModel()) {
	atlas = (Atlas*)resBuffer.prepareGet(atlasPath);
}

ButtonEntity::ButtonEntity(Atlas* atlasPtr) : ModelEntity(new ButtonModel()) {
	atlas = atlasPtr;
}

ButtonEntity::~ButtonEntity()
{
}

void ButtonEntity::init() {
	ModelEntity::init();
	
	getButtonModel()->init();
	getButtonModel()->setTexturePtr(FULL, &atlas->texture);
	atlas->makeMesh(getButtonModel()->textureMesh, "Standard");
}


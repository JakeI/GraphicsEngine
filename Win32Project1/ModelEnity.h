#pragma once
#include "Entity.h"
#include "Model.h"
#include "ResourceManager.h"
#include "AnimatedComponent.h"

class ModelEntity : public Entity
{
protected:

	const static std::map<std::string, EntityComponent::Type> nameTypeMap;

	enum ModelPtrStage { GET_REF, REF, SHARED } ptrStage;
	std::string modelPath;
	Model* model;

	void uploadStdComponent(Shader* shader, const GLint location, const EntityComponent::Type type);
	bool getFromComponent(EntityComponent::Type t, void* buffer); // return true if the component was found false if it wasn't (in which case buffer is unchanged)
	void getFromComponent(EntityComponent::Type t, void* buffer, EntityComponent::DType dtype); // if the component isn't found this will set buffer to a default value

public:
	ModelEntity(const std::string & modelRefPath);
	ModelEntity(Model* modelPtr);
	~ModelEntity();

	void init() override;
	void render(Maths::ProjView *pv, RenderMode = FULL) override;
	void uploadUniforms(Shader* shader, RenderMode rm, void* param) override;
};




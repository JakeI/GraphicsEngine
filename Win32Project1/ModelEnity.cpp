#include "ModelEnity.h"


ModelEntity::ModelEntity(const std::string & modelRefPath) :
	Entity(),
	modelPath(modelRefPath),
	ptrStage(GET_REF)
{
	
}

ModelEntity::ModelEntity(Model* modelPtr) :
	Entity(),
	modelPath(""),
	model(modelPtr),
	ptrStage(SHARED)
{
}

ModelEntity::~ModelEntity()
{
	if (ptrStage == REF)
		resm->releaseResource(modelPath);
}

void ModelEntity::init() {
	
	Entity::init();

	if (ptrStage == GET_REF) {
		resm->prepareResource(modelPath);
		model = (Model*)resm->getResource(modelPath);
		ptrStage = REF;
	}
	
}

void ModelEntity::render(Maths::ProjView *pv, RenderMode rm) {
	model->render(rm, this, (void*)pv);
}


void ModelEntity::uploadStdComponent(Shader* shader, const GLint location, const EntityComponent::Type type) {
	EntityComponent::DType dtype = EntityComponent::getDType(type);
	switch (dtype) {
	case EntityComponent::DType::FLOAT:
		{
			float f;
			getFromComponent(type, &f, dtype);
			shader->uniform(location, f);
		}
		break;
	case EntityComponent::DType::VEC2:
		{
			glm::vec2 v;
			getFromComponent(type, &v, dtype);
			shader->uniform(location, v);
		}
		break;
	case EntityComponent::DType::VEC3:
		{
			glm::vec3 v;
			getFromComponent(type, &v, dtype);
			shader->uniform(location, v);
		}
		break;
	case EntityComponent::DType::VEC4:
		{
			glm::vec4 v;
			getFromComponent(type, &v, dtype);
			shader->uniform(location, v);
		}
		break;
	case EntityComponent::DType::TRANSFORM2_DT:
		{
			Maths::Transform2 t;
			getFromComponent(type, &t, dtype);
			shader->uniform(location, t.getMat());
		}
		break;
	case EntityComponent::DType::TRANSFORM3_DT:
		{
			Maths::Transform3 t;
			getFromComponent(type, &t, dtype);
			shader->uniform(location, t.getMat());
		}
		break;
	}
}

const std::map<std::string, EntityComponent::Type> ModelEntity::nameTypeMap = {
	{"c", EntityComponent::COLOR}, {"color", EntityComponent::COLOR},
	{"typeScalar", EntityComponent::TYPE_SCALAR},
	{"bodyColor", EntityComponent::BODY_COLOR},
	{"outlineColor", EntityComponent::OUTLINE_COLOR},
	{"distanceEdges", EntityComponent::DISTANCE_EDGES},
	{"shaddowColor", EntityComponent::SHADDOW_COLOR},
	{"shaddowParam", EntityComponent::BACKGROUND_COLOR}
};

void ModelEntity::getFromComponent(EntityComponent::Type t, void* buffer, EntityComponent::DType dtype) {
	
	if (getFromComponent(t, buffer)) return;

	switch (dtype) {
	case EntityComponent::DType::FLOAT:
		{
			float f = 0.0f;
			*((float*)buffer) = f;
		}
		break;
	case EntityComponent::DType::VEC2:
		{
			glm::vec2 v;
			*((glm::vec2*)buffer) = v;
		}
		break;
	case EntityComponent::DType::VEC3:
		{
			glm::vec3 v;
			*((glm::vec3*)buffer) = v;
		}
		break;
	case EntityComponent::DType::VEC4:
		{
			glm::vec4 v;
			*((glm::vec4*)buffer) = v;
		}
		break;
	case EntityComponent::DType::TRANSFORM2_DT:
		{
			Maths::Transform2 t;
			*((Maths::Transform2*)buffer) = t;
		}
		break;
	case EntityComponent::DType::TRANSFORM3_DT:
		{
			Maths::Transform3 t;
			*((Maths::Transform3*)buffer) = t;
		}
		break;
	}
}

bool ModelEntity::getFromComponent(EntityComponent::Type t, void* buffer) {
	std::map<EntityComponent::Type, EntityComponent*>::iterator it = components.find(t);
	if (it != components.end()) {
		it->second->get(buffer);
		return true;
	}
	else
		return false;
}

void ModelEntity::uploadUniforms(Shader* shader, RenderMode mode, void* param) {

	glm::mat4 model(1.0f);
	
	std::map<EntityComponent::Type, EntityComponent*>::iterator t2it = components.find(EntityComponent::Type::TRANSFORM2),
		t3it = components.find(EntityComponent::Type::TRANSFORM3);
	if (t2it != components.end()) {
		Maths::Transform2 transform2;
		getFromComponent(EntityComponent::Type::TRANSFORM2, &transform2, EntityComponent::DType::TRANSFORM2_DT);
		model = transform2.getMat();
	}
	else if (t2it != components.end()) {
		Maths::Transform3 transform3;
		getFromComponent(EntityComponent::Type::TRANSFORM3, &transform3, EntityComponent::DType::TRANSFORM3_DT);
		model = transform3.getMat();
	}

	glm::mat4 view = ((Maths::ProjView*)param)->view;
	glm::mat4 projection = ((Maths::ProjView*)param)->proj;
	glm::mat4 mvp = ((Maths::ProjView*)param)->projView * model;

	for (Shader::UniformMap::iterator it = shader->uniforms.begin();
	it != shader->uniforms.end(); ++it) {
		if (it->first == "mvp") shader->uniform(it->second, mvp);
		else if (it->first == "m" || it->first == "model") 
			shader->uniform(it->second, model);
		else if (it->first == "v" || it->first == "view") 
			shader->uniform(it->second, view);
		else if (it->first == "p" || it->first == "proj" || it->first == "projection") 
			shader->uniform(it->second, projection);
		else {
			std::map<std::string, EntityComponent::Type>::const_iterator id = nameTypeMap.find(it->first);
			if (id != nameTypeMap.end()) {
				uploadStdComponent(shader, it->second, id->second);
			}
		}
	}
}
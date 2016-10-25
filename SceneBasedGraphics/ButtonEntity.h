#pragma once

#include "StdAfx.h"
#include "ModelEntity.h"
#include "Atlas.h"

class ButtonEntity : public ModelEntity  // TODO: create a class Sprite and repalce ButtonEntity with it!!
{
private:

	Atlas* atlas;

public:
	ButtonEntity(const std::string & atlasPath);
	ButtonEntity(Atlas* atlasPtr);
	~ButtonEntity();

	void init() override;

	class ButtonModel : public Model {
	public:
		Mesh* textureMesh;
		ButtonModel();
		~ButtonModel();

		void init();
	};

private:

	ButtonModel* getButtonModel() { return (ButtonModel*)model; }
};




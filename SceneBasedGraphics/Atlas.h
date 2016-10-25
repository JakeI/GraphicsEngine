#pragma once

#include "StdAfx.h"
#include "Maths.h"
#include "TextureEx.h"
#include "Mesh.h"
#include "Resource.h"


// Stroes all information about a texture atlas Including it's Texture, the names and 
// texture coordinates of the sprites
// 
// Texture atlasses are specified using a Path like "res/atlases/XXX"
// than a file "res/atlases/XXX.atl" is expected to hold the text output form Spride Sheet Packer
// and a "res/atlases/XXX.png" file is expected to be the texture atlas
class Atlas : public Resource
{
private:

	void handelLine(std::string & line, int totalWidth, int totalHight);

	std::map<std::string, Maths::Box2> sprites;

public:

	struct Vertex {
		float tx, ty;
		Vertex() : tx(0.0f), ty(0.0f) {}
		Vertex(float textureX, float textureY) : tx(textureX), ty(textureY) {}
	};

	TextureEx texture;
	const Maths::Box2 & getBox(const std::string & spriteName);

	void makeMesh(Mesh* textureMesh, const std::string & spriteName);

	Atlas(const std::string & path); // expects a call of init(path) (used by the Refrence Manager)
	~Atlas();

	// Resource Features
	static Resource* alloc(const std::string & path) { return new Atlas(path); }
	void init_resource(const std::string & path) override;
};


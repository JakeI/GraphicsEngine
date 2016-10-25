#include "Atlas.h"


void Atlas::handelLine(std::string & line, int totalWidth, int totalHigth) {
	std::stringstream ss(line);
	std::string name;
	ss >> name;
	ss.ignore(256, '=');
	int x, y, w, h;
	ss >> x >> y >> w >> h;
	Maths::Box2 box(
			(float)x / (float)totalWidth,
			(float)(x+w) / (float)totalWidth,
			(float)(totalHigth - (y+h)) / (float)totalHigth,
			(float)(totalHigth - y) / (float)totalHigth
		);
	sprites[name] = box;
}

const Maths::Box2 & Atlas::getBox(const std::string & spriteName) {
	std::map<std::string, Maths::Box2>::iterator it = sprites.find(spriteName);
	if (it != sprites.end()) {
		return it->second;
	}
	else {
		ilog->printError("getBox was called with the invalid key: '" + spriteName + "' the defualt box will be returned");
		return Maths::Box2();
	}
}

Atlas::Atlas(const std::string & path) :
	texture(path + ".png"),
	Resource(path)
{

}

void Atlas::init_resource(const std::string & path) {
	texture.init(path + ".png");
	
	std::ifstream in(path + ".atl", std::ios::in);

	if (in.is_open()) {
		std::string line;
		while (getline(in, line))
			handelLine(line, texture.getWidth(), texture.getHight());
	}
	else ilog->printError("The file '" + path + ".atl' wasn't found hence the texture atals couldn't be loaded");

	in.close();
}


Atlas::~Atlas()
{
}

void Atlas::makeMesh(Mesh* textureMesh, const std::string & spriteName) {
	
	std::vector<Vertex> data;
	Maths::Box2 box = getBox(spriteName);
	
	// this is only a test
	data.push_back(Vertex(box.x_min, box.y_min - 0.25f));
	data.push_back(Vertex(box.x_max, box.y_min - 0.25f));
	data.push_back(Vertex(box.x_max, box.y_max - 0.25f));
	data.push_back(Vertex(box.x_min, box.y_max - 0.25f));

	textureMesh->uploadData(data, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
}

#include "Mesh.h"




Mesh::Mesh(const std::string & path) : Resource(path), vbo(0), target(GL_ARRAY_BUFFER), size(0) {}

Mesh::Mesh() : vbo(0), target(GL_ARRAY_BUFFER), size(0) {

}

Mesh::~Mesh() {

}

void Mesh::readTarget(std::string & line, GLenum* result) {
	if (line.find("GL_ARRAY_BUFFER") != std::string::npos) *result = GL_ARRAY_BUFFER;
	else if (line.find("GL_ELEMENT_ARRAY_BUFFER") != std::string::npos) *result = GL_ELEMENT_ARRAY_BUFFER;
}

void Mesh::init_resource(const std::string & path) {
	std::ifstream in(path, std::ios::in);

	if (in.is_open()) {

		std::string line;
		while (getline(in, line)) {
			 
			if (line == "")
				continue;

			line = line.substr(0, line.find('#')); // stirip off comments

			if (line.find("target") != std::string::npos) {
				readTarget(line, &target);
				break;
			}
		}

		// TODO: add support for GL_ELEMENT_ARRAY_BUFFER to this

		std::vector<float> data;

		readData(in, data);
		uploadData(data, target);
	}
	else {
		ilog->printError("The File: '" + path + "' couldn't be opend hence connot be loaded by Mesh");
	}

	in.close();
}

void Mesh::readData(std::ifstream & in, std::vector<float> & data) {
	std::string line;
	while (getline(in, line)) {

		if (line == "" || line[0] == '#')
			continue;

		std::stringstream ss(line);
		std::string s;
		while (ss >> s) {
			data.push_back(std::stof(s));
			if (ss.peek() == ',')
				ss.ignore();
		}
	}
}

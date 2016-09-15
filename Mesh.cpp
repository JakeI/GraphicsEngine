#include "Mesh.h"

void Mesh::Atribute::set(int attrib, int start, int dim) {
	if (this->isUsed()) {
		std::stringstream ss;
		ss << "The atribute (attrib=" << this->attrib << ", start="
			<< this->start << ", dim=" << this->dim << ") is set another time to (attrib="
			<< attrib << ", start=" << start << ", dim=" << dim <<
			") that probably means that the *.data file is broken";
		ilog->printError(ss.str());
	}

	this->attrib = attrib; 
	this->start = start; 
	this->dim = dim;
}

Mesh::Atribute::Atribute(int attrib, int start, int dim) : Atribute() {
	set(attrib, start, dim);
}


Mesh::Mesh() {
	vao = 0;
	vbo = 0;
	primative = GL_LINE_STRIP;
}


Mesh::~Mesh() {

}

Mesh* Mesh::readMesh(const std::string & path) {
	Mesh* mesh = new Mesh();
	mesh->load(path);
	return mesh;
}

void Mesh::load(const std::string & path) {
	std::ifstream in(path, std::ios::in);

	if (in.is_open()) {

		std::vector<float> data;
		std::list<Atribute> atributes;
		int stride = -1;

		readPrimativeType(in);
		readLayoutLine(in, atributes, &stride);
		readData(in, data);

		setLocations(atributes);

		uploadData(data, atributes, stride);
	}
	else {
		ilog->printError("The File: '" + path + "' couldn't be opend hence connot be loaded by Mesh");
	}

	in.close();
}

void Mesh::readPrimativeType(std::ifstream & in) {
	std::string line;
	if (getline(in, line)) {
		if (line.find("GL_TRIANGLES") != std::string::npos) primative = GL_TRIANGLES;
		else if (line.find("GL_QUADS") != std::string::npos) primative = GL_QUADS;
		else {
			ilog->printError("The Primative type '" + line + "' cannot be interpreted");
		}
	}
}

void Mesh::readLayoutLine(std::ifstream & in, std::list<Atribute> & atributes, int* stride) {
	*stride = -1;
	atributes.clear();

	std::string line;
	if (getline(in, line)) {
		std::stringstream ss(line);
		std::string type;
		ss >> type;
		if (type == std::string("layout")) {
			std::string flag;
			int courser = 0;
			while (ss >> flag) {
				if (flag == std::string("xy")) {
					atributes.push_back(Atribute(0, courser, 2));
					courser += 2*sizeof(float);
				} else if (flag == std::string("uv")) {
					atributes.push_back(Atribute(3, courser, 2));
					courser += 2*sizeof(float);
				} else if (flag.find("=") != std::string::npos) {
					std::stringstream ss(flag);
					std::string key, commandAttrib, commandDim;
					
					getline(ss, key, '=');
					getline(ss, commandAttrib, ',');
					getline(ss, commandDim);

					if (key == "AtributeDimention" || key == "ad") {
						int location = std::stoi(commandAttrib);
						int dimention = std::stoi(commandDim);
						atributes.push_back(Atribute(location, courser, dimention));
						courser += dimention*sizeof(float);
					} else {
						ilog->printError("the layout key '" + key + "' is unknown");
					}

				} else {
					ilog->printError("The flag '" + flag + "' in the layout is unknown");
				}
			}
			*stride = courser;
		} else {
			ilog->printError("the line " + line + " dosen't start with the keyword 'layout'");
		}
	} else {
		ilog->printError("couldn't read the lyout line");
	}
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

void Mesh::setLocations(const std::list<Atribute> & atributes) {
	for (auto atribute : atributes)
		locations.push_back(atribute.attrib);
}

void Mesh::render() {
	if (vao == 0) return;

	glBindVertexArray(vao);

	for (int & location : locations)
		glEnableVertexAttribArray(location);

	glDrawArrays(primative, 0, count);

	for (int & location : locations)
		glDisableVertexAttribArray(location);
}

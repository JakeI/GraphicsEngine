#include "Mdl.h"


void Mdl::Atribute::set(int location, int start, int dim) {
	if (this->isUsed()) {
		std::stringstream ss;
		ss << "The atribute (attrib=" << this->location << ", start="
			<< this->start << ", dim=" << this->dim << ") is set another time to (attrib="
			<< location << ", start=" << start << ", dim=" << dim <<
			") that probably means that the *.data file is broken";
		ilog->printError(ss.str());
	}

	this->location = location;
	this->start = start;
	this->dim = dim;
}

Mdl::Atribute::Atribute(int location, int start, int dim) : Atribute() {
	set(location, start, dim);
}

void Mdl::MeshLayout::read(std::string & line) {
	std::stringstream ss(line);
	ss.ignore(256, ' '); // ignore keyword mesh
	std::string s;
	ss >> s;
	meshRef = Strings::stripQuotes(s);
	ss.get(); // get the space caracter
	ss.ignore(256, ' '); // ignore keyword leyout

	std::string flag;
	int courser = 0;
	while (ss >> flag) {
		if (flag == std::string("xy")) {
			atributes.push_back(Atribute(0, courser, 2));
			courser += 2 * sizeof(float);
		}
		else if (flag == std::string("uv")) {
			atributes.push_back(Atribute(3, courser, 2));
			courser += 2 * sizeof(float);
		}
		else if (flag.find("=") != std::string::npos) {
			std::stringstream ss(flag);
			std::string key, commandAttrib, commandDim;

			getline(ss, key, '=');
			getline(ss, commandAttrib, ',');
			getline(ss, commandDim);

			if (key == "ad" || key == "AtributeDimention") {
				int location = std::stoi(commandAttrib);
				int dimention = std::stoi(commandDim);
				atributes.push_back(Atribute(location, courser, dimention));
				courser += dimention*sizeof(float);
			}
			else ilog->printError("the layout key '" + key + "' is unknown");

		}
		else {
			ilog->printError("The flag '" + flag + "' in the layout is unknown");
		}
	}
	stride = courser;
}

void Mdl::MeshLayout::setGLDataPtrs(Mesh* myMesh) {

	myMesh->bind();
	for (auto atribute : atributes)
		glVertexAttribPointer(atribute.location, atribute.dim, GL_FLOAT, GL_FALSE,
			stride, (void*)(atribute.start));

}

void Mdl::MeshLayout::enableAtribArrays() {
	for (auto atribute : atributes)
		glEnableVertexAttribArray(atribute.location);
}

void Mdl::MeshLayout::disableAtribArrays() {
	for (auto atribbute : atributes)
		glDisableVertexAttribArray(atribbute.location);
}

Mdl::Stage::Stage() :
	mode(UNDEFINED),
	primative(GL_POINTS),
	shaderRef(""),
	meshLayouts(),
	begin(0),
	end(0),
	meshLenRef("")
{}

template <typename T> void Mdl::Stage::setValue(
		const std::map<std::string, T> & map, T* value, const std::string & line) {
	std::stringstream ss(line);
	ss.ignore(256, ' '); // ignore keyword
	std::string v;
	ss >> v;

	std::map<std::string, T>::const_iterator it = map.find(v);
	if (it != map.end()) 
		*value = it->second;
	else 
		ilog->printError("tried to set value: '" + v + "' unsucessfully");
}

const std::map<std::string, RenderMode> Mdl::Stage::renderModeMap = {
	{ "UNIFORM", UNIFORM },
	{ "FULL", FULL }
};

void Mdl::Stage::readMode(std::string & line) {
	//setValue(renderModeMap, &mode, line);

	std::stringstream ss(line);
	ss.ignore(256, ' '); // Ignoer keyword Mode
	std::string s;
	while (ss >> s) {
		std::map<std::string, RenderMode>::const_iterator it = renderModeMap.find(s);
		if (it != renderModeMap.end()) { // found
			mode |= it->second;
		} else {
			ilog->printError("Couldn't interpret Rendermode: " + s + " when reading from *.mdl file");
		}
	}
}

const std::map<std::string, GLenum> Mdl::Stage::primativeTypeMap = {
	{ "GL_POINTS", GL_POINTS },
	{ "GL_LINES", GL_LINES },
	{ "GL_LINE_STRIP", GL_LINE_STRIP },
	{ "GL_LINE_LOOP", GL_LINE_LOOP },
	{ "GL_TRIANGLES", GL_TRIANGLES },
	{ "GL_TRIANGLE_STRIP", GL_TRIANGLE_STRIP },
	{ "GL_TRIANGLE_FAN", GL_TRIANGLE_FAN },
	// depreciated and removed in newer versions - Quads are nice though and thats why I still support them
	{ "GL_QUADS", GL_QUADS },
	{ "GL_QUAD_STRIP", GL_QUAD_STRIP }
};

void Mdl::Stage::readPrimative(std::string & line) {
	setValue(primativeTypeMap, &primative, line);
}

std::string Mdl::Stage::readRefrence(std::string & line) {
	std::stringstream ss(line);
	ss.ignore(256, ' '); // ignore keyword
	std::string s;
	ss >> s;
	return Strings::stripQuotes(s);
}

void Mdl::Stage::readShader(std::string & line) {
	shaderRef = readRefrence(line);
}

void Mdl::Stage::readTexture(std::string & line) {
	textureRef = readRefrence(line);
}

void Mdl::Stage::readRange(std::string & line) {
	std::stringstream ss(line);
	ss.ignore(256, ' '); // ignore keyword range
	ss.get(); // ignore space char
	ss.ignore(256, ' '); // ignore keyword from
	ss >> begin;
	ss.get(); // ignore space char
	ss.ignore(256, ' '); // ignore keyword to
	std::string endstr;
	ss >> endstr;
	if (endstr.find("end") != std::string::npos) {
		meshLenRef = Strings::stripQuotes(endstr.substr(endstr.find('(')+1, endstr.find_last_of(')')-1));
		end = -1;
	}
	else {
		end = std::stoi(endstr);
		meshLenRef = "";
	}
}

void Mdl::Stage::readMesh(std::string & line) {
	meshLayouts.push_back(MeshLayout(line));
}

void Mdl::Stage::readStage(std::ifstream & in) {
	std::string line;
	int lastPosition = in.tellg();
	bool moodLineFound = false;
	while (getline(in, line)) {

		if (line != "" && line != "\t") {

			line = line.substr(0, line.find('#')); // strip off comments

			unsigned int pos[] = {
				line.find("Mode"),			// 0
				line.find("primative"),		// 1
				line.find("shader"),		// 2
				line.find("range"),			// 3
				line.find("mesh"),			// 4
				line.find("texture")		// 5
			};
			int lenPos = sizeof(pos) / sizeof(unsigned int);
			unsigned int lowestId = 512, lowest = 512; // A hight number
			for (int i = 0; i < lenPos; i++) { if (lowest > pos[i]) { lowestId = i; lowest = pos[i]; } }

			if (lowestId == 4) readMesh(line); // do the most likly cases first
			else if (lowestId == 5) readTexture(line);
			else if (lowestId == 0) {
				if (moodLineFound) {
					in.seekg(lastPosition); // Unget the new Moodline
					return;
				}
				else {
					readMode(line);
					moodLineFound = true;
				}
			}
			else if (lowestId == 1) readPrimative(line);
			else if (lowestId == 2) readShader(line);
			else if (lowestId == 3) readRange(line);
			else {
				ilog->printError("couldn't handel the line: '" + line + "' in a mdl file");
			}
		}

		lastPosition = in.tellg();
	}
}

void Mdl::read(const std::string & path) {
	std::ifstream in(path, std::ios::in);

	if (in.is_open()) {
		while (in) {
			Stage stage;
			stage.readStage(in);
			stages.push_back(stage);
		}
	}

	in.close();
}

Mdl::Mdl(const std::string & path) {
	read(path);
}

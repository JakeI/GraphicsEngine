#include "Shader.h"

std::string Shader::shaderTypeToString(const int type) {
	switch (type) {
	case GL_VERTEX_SHADER:
		return std::string("GL_VERTEX_SHADER");
	case GL_FRAGMENT_SHADER:
		return std::string("GL_FFRAGMENT_SHADER");
	case GL_GEOMETRY_SHADER:
		return std::string("GL_GEOMETRY_SHADER");
	default:
		return std::string("UNSUPPORTED_SHADER_TYPE");
	}
}

void Shader::preproces(std::string & code, const std::string & path) {

	const char include[] = "#include";
	const int incluedeLen = sizeof(include) / sizeof(char);

	std::size_t position = code.find(include);
	while (position != std::string::npos) {
		std::size_t begin = position;
		std::size_t end = position + incluedeLen;
		
		char c = code[end++];
		while (c == ' ' || c == '\t')
			c = code[end++];

		std::string replaceStr("");

		if (c == '"') {
			std::stringstream f;
			c = code[end++];
			while (c != '\n' && c != '"') {
				f << c;
				c = code[end++];
			}
			std::string file = f.str();
			std::string dir = Strings::pathInSameDir(path, file);
			std::ifstream in(dir, std::ios::in);
			if (in.is_open()) {
				std::string line;
				std::stringstream ss;
				while (getline(in, line)) {
					ss << line << "\n";
				}
				replaceStr = ss.str();
			}
			in.close();
		}

		code = code.substr(0, begin) + replaceStr + code.substr(end);

		position = code.find(include, position + 1);
	}
	
}

GLuint Shader::loadShader(const std::string & file, const int type) {
	std::fstream in(file, std::ios::in);
	if(in.fail()){
		if (type == GL_GEOMETRY_SHADER) // A Geometry Shader is not required
			return 0;

		ilog->printError("Couldn't read file: '"+file+
			"'\nhence couldn't load shader of type: '"+shaderTypeToString(type)+"'");
		return 0;
	}

	in.seekg(0, std::ios::end);
	int len = ((int)(in.tellg())) + 1;
	in.seekg(0, std::ios::beg);

	char* source = new char[len];
	memset(source, '\0', len);
	in.read(source, len);
	in.close();

	std::string code = std::string(source);
	preproces(code, file);

	delete[] source;

	GLuint shader = glCreateShader(type);
	const char* str = code.c_str();
	glShaderSource(shader, 1, &str, NULL);
	glCompileShader(shader);
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		int logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		char* errorMsg = new char[logLen];
		glGetShaderInfoLog(shader, logLen, NULL, errorMsg);
		ilog->printError("Failed to compile shader form file: '" + file +
			"'\nof type: '" + shaderTypeToString(type) +
			"'\n\n" + std::string(errorMsg));
		return 0;
	}
	return shader;
}

void Shader::deleteShaders() {
	glUseProgram(0);
	if (!program && !vertex)
		glDetachShader(program, vertex);
	if (!program && !fragment)
		glDetachShader(program, fragment);
	if (!program && !geometry)
		glDetachShader(program, geometry);
	if (!vertex)
		glDeleteShader(vertex);
	if (!fragment)
		glDeleteShader(fragment);
	if (!geometry)
		glDeleteShader(geometry);
	if (!program)
		glDeleteProgram(program);
}

void Shader::load(const std::string & path) {
	vertex = loadShader(path + ".vert", GL_VERTEX_SHADER);
	fragment = loadShader(path + ".frag", GL_FRAGMENT_SHADER);
	geometry = loadShader(path + ".geom", GL_GEOMETRY_SHADER);
}

void Shader::link(const std::string & path) {
	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	if (geometry != 0)
		glAttachShader(program, geometry);

	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE) {
		int logLen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
		char* errorMsg = new char[logLen];
		glGetProgramInfoLog(program, logLen, NULL, errorMsg);
		ilog->printError("Failed to link shader program form path: '" + path +
			"'\n\n" + errorMsg);
	}

	glValidateProgram(program);
}

void Shader::findUniformLocations() {
	//source https://www.opengl.org/wiki/Program_Introspection

	GLint num = 0;
	glGetProgramInterfaceiv(program, GL_UNIFORM, GL_ACTIVE_RESOURCES, &num);
	const GLenum properties[] = { GL_NAME_LENGTH, GL_LOCATION };
	const int propNum = sizeof(properties) / sizeof(GLenum);

	for (int u = 0; u < num; ++u) {
		GLint values[propNum];
		glGetProgramResourceiv(program, GL_UNIFORM, u, propNum, properties, propNum, NULL, values);

		//Possibly jump ovor block variables here

		std::vector<char> nameData(values[0]);
		glGetProgramResourceName(program, GL_UNIFORM, u, nameData.size(), NULL, &nameData[0]);
		uniforms[std::string(nameData.begin(), nameData.end() - 1)] = values[1];

		//Maybe also store the types in the map and check them before calling glUniform*
	}

}

GLint Shader::getUniformLocation(const std::string & name) {
	UniformMap::iterator it = uniforms.find(name);
	if (it == uniforms.end()) {
		ilog->printError("couldn't find the uniform variable: '" + name +
			"' in the program hence it cannot be uploaded");
		return -1;
	}
	return it->second;
}

Shader::Shader(const std::string & path) :
	program(0), 
	vertex(0),
	fragment(0),
	geometry(0),
	Resource(path)
{
	
}


void Shader::init_resource(const std::string & path) {
	load(path);
	link(path);

	findUniformLocations();
}

Shader::~Shader() {
	deleteShaders();
}


GLuint Shader::getProgram() {
	return program;
}


void Shader::use() {
	glUseProgram(program);
}

void Shader::uniform(const std::string & name, const float f) {
	GLint location = getUniformLocation(name);
	if (location == -1) return;
	glUniform1f(location, f);
}

void Shader::uniform(const std::string & name, const glm::vec2 v) {
	GLint location = getUniformLocation(name);
	if (location == -1) return;
	glUniform2fv(location, 1, &v[0]);
}

void Shader::uniform(const std::string & name, const glm::vec3 v) {
	GLint location = getUniformLocation(name);
	if (location == -1) return;
	glUniform3fv(location, 1, &v[0]);
}

void Shader::uniform(const std::string & name, const glm::vec4 v) {
	GLint location = getUniformLocation(name);
	if (location == -1) return;
	glUniform4fv(location, 1, &v[0]);
}

void Shader::uniform(const std::string & name, const glm::mat4 m) {
	GLint location = getUniformLocation(name);
	if (location == -1) return;
	glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
}

void Shader::uniform(const std::string & name, const bool b) {
	GLint location = getUniformLocation(name);
	if (location == -1) return;
	glUniform1f(location, b ? 1.0f : -1.0f);
}

GLint Shader::uniformLocation(const std::string & name) {
	return getUniformLocation(name);
}

void Shader::uniform(const GLint location, const float f) {
	if (location == -1) return;
	glUniform1f(location, f);
}

void Shader::uniform(const GLint location, const glm::vec2 v) {
	if (location == -1) return;
	glUniform2f(location, v.x, v.y);
}

void Shader::uniform(const GLint location, const glm::vec3 v) {
	if (location == -1) return;
	glUniform3f(location, v.x, v.y, v.z);
}

void Shader::uniform(const GLint location, const glm::vec4 v) {
	if (location == -1) return;
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void Shader::uniform(const GLint location, const glm::mat4 m) {
	if (location == -1) return;
	glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
}

void Shader::uniform(const GLint location, const bool b) {
	if (location == -1) return;
	glUniform1f(location, b ? 1.0f : -1.0f);
}
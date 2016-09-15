#pragma once

#include "StdAfx.h"
#include "InfoLog.h"
#include "Strings.h"

class Shader
{
private:

	static std::string shaderTypeToString(const int type);

	static void preproces(std::string & code, const std::string & path);

	GLuint program, vertex, fragment, geometry;

	static GLuint loadShader(const std::string & file, const int type);
	void deleteShaders();
	void load(const std::string & path);
	void link(const std::string & path);

	/*//		 type			 name		  location
	//std::map<GLint, std::map<std::string, GLint>> uniforms;*/

	//		 name		  location
	std::map<std::string, GLint> uniforms;
	typedef std::map<std::string, GLint> uniformMap;

	GLint getUniformLocation(const std::string & name);
	void findUniformLocations();

public:
	Shader(const std::string & path);
	~Shader();
	
	GLuint getProgram();

	// use has to be called befor uniform is called
	void use();

	void uniform(const std::string & name, const float f);
	void uniform(const std::string & name, const glm::vec2 v);
	void uniform(const std::string & name, const glm::vec3 v);
	void uniform(const std::string & name, const glm::vec4 v);
	void uniform(const std::string & name, const glm::mat4 m);
	void uniform(const std::string & name, const bool b);
};


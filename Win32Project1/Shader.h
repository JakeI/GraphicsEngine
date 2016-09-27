#pragma once

#include "StdAfx.h"
#include "InfoLog.h"
#include "Strings.h"

class Shader
{
public:
	//		         name		  location
	typedef std::map<std::string, GLint> UniformMap;

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

	GLint getUniformLocation(const std::string & name);
	void findUniformLocations();

public:
	UniformMap uniforms;

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
	GLint uniformLocation(const std::string & name);
	void uniform(const GLint location, const float f);
	void uniform(const GLint location, const glm::vec2 v);
	void uniform(const GLint location, const glm::vec3 v);
	void uniform(const GLint location, const glm::vec4 v);
	void uniform(const GLint location, const glm::mat4 m);
	void uniform(const GLint location, const bool b);
};


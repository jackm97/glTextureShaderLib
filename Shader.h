#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// program ID
	unsigned int ID;
	std::string name;

	// Empty Constructor
	Shader(){ID = -1; name = "";};	

	// Constructor reads and builds shader
	Shader(const char* vertexPath, const char* fragmentPath);
	// Constructor reads and builds shader and adds name
	Shader(const char* vertexPath, const char* fragmentPath, const char* name);
	// activate shader
	void use() const;

	// set uniform functions (best to just do this manually)
	// in other words, don't bother with these unless you want to
	// take the time to implement all the possibilities yourself
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string &name, float value[3]) const;
	void setVec4(const std::string &name, float value[4]) const;
	void setMat4(const std::string &name, float* value) const;
};

// IMPLEMENTATION BELOW:


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	this->name = "";
	
	//1. retrieve vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream, colormapStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		
		vShaderFile.close();
		fShaderFile.close();
		
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		exit(1);
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	
	// 2. Compile Shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(1);
	}

	// fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(1);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		exit(1);
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


	// Constructor reads and builds shader and adds name
Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* name){
    // gladLoadGL();
	this->name = name;
	
	//1. retrieve vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream, colormapStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		
		vShaderFile.close();
		fShaderFile.close();
		
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		exit(1);
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	
	// 2. Compile Shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(1);
	}

	// fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		exit(1);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		exit(1);
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
	unsigned int uLocation = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uLocation, (int) value);
}

void Shader::setInt(const std::string &name, int value) const
{
	unsigned int uLocation = glGetUniformLocation(ID, name.c_str());
	glUniform1i(uLocation, value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	unsigned int uLocation = glGetUniformLocation(ID, name.c_str());
	glUniform1f(uLocation, value);
}

void Shader::setVec3(const std::string &name, float value[3]) const
{
	unsigned int uLocation = glGetUniformLocation(ID, name.c_str());
	glUniform3f(uLocation, value[0], value[1], value[2]);
}

void Shader::setVec4(const std::string &name, float value[4]) const
{
	unsigned int uLocation = glGetUniformLocation(ID, name.c_str());
	glUniform4f(uLocation, value[0], value[1], value[2], value[3]);
}

void Shader::setMat4(const std::string &name, float* value) const
{
	unsigned int uLocation = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(uLocation, 1, GL_FALSE, value);
}

#endif

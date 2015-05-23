#include "Shader.hpp"

#include <string>
#include <fstream>

Shader::Shader(GLenum shaderType) : _isCompiled(false), _shaderType(shaderType)
{
	_shaderId = glCreateShader(shaderType);
}

Shader::~Shader()
{
}

bool	Shader::compileSourceCode(const char* sourceCode)
{
	if (!this->isValid()) {
		return false;
	}
	_isCompiled = false;
	glShaderSource(_shaderId, 1, &sourceCode, NULL);
	glCompileShader(_shaderId);
	GLint result = GL_FALSE;
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		return false;
	}
	_isCompiled = true;
	return true;
}

bool	Shader::compileSourceFile(const char* filename)
{
	std::string		shaderCode;
	std::ifstream	shaderStream(filename, std::ios::in);
	if (!shaderStream.is_open()) {
		return false;
	}
	std::string line = "";
	while (getline(shaderStream, line)) {
		shaderCode += "\n" + line;
	}
	shaderStream.close();
	return compileSourceCode(shaderCode.c_str());
}

bool	Shader::isValid() const
{
	return _shaderId != 0;
}

bool	Shader::isCompiled() const
{
	return _isCompiled;
}

GLenum	Shader::shaderType() const
{
	return _shaderType;
}

GLuint	Shader::shaderId() const
{
	return _shaderId;
}
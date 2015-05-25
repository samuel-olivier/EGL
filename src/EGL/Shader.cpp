#include "EGL/Shader.hpp"

#include <string>
#include <fstream>

namespace EGL
{
	Shader::Shader(GLenum shaderType) : _isCompiled(false), _shaderType(shaderType)
	{
		_shaderId = glCreateShader(shaderType);
	}

	Shader::~Shader()
	{
		if (this->isValid()) {
			glDeleteShader(this->_shaderId);
		}
	}

	bool	Shader::compileSourceCode(const char* sourceCode)
	{
		if (!this->isValid()) {
			return false;
		}
		this->_isCompiled = false;
		glShaderSource(this->_shaderId, 1, &sourceCode, NULL);
		if (glGetError() != GL_NO_ERROR) {
			return false;
		}
		glCompileShader(this->_shaderId);
		if (glGetError() != GL_NO_ERROR) {
			return false;
		}
		GLint result = GL_FALSE;
		glGetShaderiv(this->_shaderId, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE || glGetError() != GL_NO_ERROR) {
			return false;
		}
		this->_isCompiled = true;
		return true;
	}

	bool	Shader::compileSourceFile(std::string const& filename)
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
		return this->compileSourceCode(shaderCode.c_str());
	}

	bool	Shader::isValid() const
	{
		return this->_shaderId != 0;
	}

	bool	Shader::isCompiled() const
	{
		return this->_isCompiled;
	}

	GLenum	Shader::shaderType() const
	{
		return this->_shaderType;
	}

	GLuint	Shader::shaderId() const
	{
		return this->_shaderId;
	}
}
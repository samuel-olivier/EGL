#include "EGL/ShaderProgram.hpp"

#include "EGL/Shader.hpp"

namespace EGL
{
	ShaderProgram::ShaderProgram() : _isLinked(false)
	{
		this->_programId = glCreateProgram();
	}

	ShaderProgram::~ShaderProgram()
	{
		if (this->isValid()) {
			glDeleteProgram(this->_programId);
		}
	}


	bool	ShaderProgram::addShader(Shader *shader)
	{
		if (!this->isValid() || shader == NULL || !shader->isValid()) {
			return false;
		}
		glAttachShader(this->_programId, shader->shaderId());
		if (glGetError() != GL_NO_ERROR) {
			return false;
		}
		this->_shaders.push_back(shader);
		return true;
	}

	void	ShaderProgram::removeShader(Shader *shader)
	{
		size_t	nbShader = this->_shaders.size();

		this->_shaders.remove(shader);
		if (nbShader != this->_shaders.size()) {
			glDetachShader(this->_programId, shader->shaderId());
		}
	}

	int		ShaderProgram::attributeLocation(std::string const& name)
	{
		if (!this->isValid()) {
			return -1;
		}
		return glGetAttribLocation(this->_programId, name.c_str());
	}

	int		ShaderProgram::uniformLocation(std::string const& name)
	{
		if (!this->isValid()) {
			return -1;
		}
		return glGetUniformLocation(this->_programId, name.c_str());
	}

	bool	ShaderProgram::use()
	{
		if (!this->isValid()) {
			return false;
		}
		if (!this->isLinked() && !this->link()) {
			return false;
		}
		glUseProgram(this->_programId);
		if (glGetError() != GL_NO_ERROR) {
			return false;
		}
		return true;
	}

	bool	ShaderProgram::link()
	{
		if (!this->isValid()) {
			return false;
		}
		glLinkProgram(this->_programId);
		if (glGetError() != GL_NO_ERROR) {
			return false;
		}
		this->_isLinked = true;
		return true;
	}

	bool	ShaderProgram::isValid() const
	{
		return this->_programId != 0;
	}

	bool	ShaderProgram::isLinked() const
	{
		return this->_isLinked;
	}

	GLuint	ShaderProgram::programId() const
	{
		return this->_programId;
	}

	std::list<Shader*>	ShaderProgram::shaders() const
	{
		return this->_shaders;
	}

}
#include "EGL/ShaderProgram.hpp"

#include <algorithm>

#include "EGL/Shader.hpp"

namespace EGL
{
	ShaderProgram::ShaderProgram() : _programId(0), _isLinked(false)
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		if (this->isCreated()) {
			glDeleteProgram(this->_programId);
		}
	}

	bool	ShaderProgram::create()
	{
		if (this->isCreated()) {
			return false;
		}
		this->_programId = glCreateProgram();
		return this->isCreated();
	}

	bool	ShaderProgram::addShader(Shader *shader)
	{
		if (!this->isCreated() || shader == NULL || !shader->isValid()) {
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
		if (!this->isCreated() || !this->isLinked()) {
			return -1;
		}
		auto it = this->_attributeLocations.find(name);
		if (it == this->_attributeLocations.end()) {
			int	location = glGetAttribLocation(this->_programId, name.c_str());

			if (location >= 0) {
				this->_attributeLocations[name] = location;
			}
			return location;
		}
		return it->second;
	}

	int		ShaderProgram::uniformLocation(std::string const& name)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return -1;
		}
		auto it = this->_uniformLocations.find(name);
		if (it == this->_uniformLocations.end()) {
			int	location = glGetUniformLocation(this->_programId, name.c_str());

			if (location >= 0) {
				this->_uniformLocations[name] = location;
			}
			return location;
		}
		return it->second;
	}

	bool	ShaderProgram::use()
	{
		if (!this->isCreated()) {
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
		if (!this->isCreated()) {
			return false;
		}
		glLinkProgram(this->_programId);
		if (glGetError() != GL_NO_ERROR) {
			return false;
		}
		this->_isLinked = true;
		this->_attributeLocations.clear();
		this->_uniformLocations.clear();
		return true;
	}

	bool	ShaderProgram::isCreated() const
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

	void	ShaderProgram::setAttributeBuffer(int location, GLenum type, int offset, int tupleSize, int stride)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glVertexAttribPointer(location, tupleSize, type, GL_FALSE, stride, (void*)offset);
	}

	void	ShaderProgram::setAttributeBuffer(std::string const& name, GLenum type, int offset, int tupleSize, int stride)
	{
		int	location = this->attributeLocation(name);

		if (location >= 0) {
			this->setAttributeBuffer(location, type, offset, tupleSize, stride);
		}
	}

	void	ShaderProgram::setAttributeValue(int location, GLfloat value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glVertexAttrib1fv(location, &value);
	}

	void	ShaderProgram::setAttributeValue(int location, glm::vec2 const& value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glVertexAttrib2fv(location, &value[0]);
	}

	void	ShaderProgram::setAttributeValue(int location, glm::vec3 const& value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glVertexAttrib3fv(location, &value[0]);
	}

	void	ShaderProgram::setAttributeValue(int location, glm::vec4 const& value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glVertexAttrib4fv(location, &value[0]);
	}

	void	ShaderProgram::setAttributeValue(std::string const& name, GLfloat value)
	{
		this->_setAttributeValueFromString(name, value);
	}

	void	ShaderProgram::setAttributeValue(std::string const& name, glm::vec2 const& value)
	{
		this->_setAttributeValueFromString(name, value);
	}

	void	ShaderProgram::setAttributeValue(std::string const& name, glm::vec3 const& value)
	{
		this->_setAttributeValueFromString(name, value);
	}

	void	ShaderProgram::setAttributeValue(std::string const& name, glm::vec4 const& value)
	{
		this->_setAttributeValueFromString(name, value);
	}

	void	ShaderProgram::setUniformValue(int location, GLfloat value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glUniform1fv(location, 1, &value);
	}

	void	ShaderProgram::setUniformValue(int location, GLint value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glUniform1iv(location, 1, &value);
	}

	void	ShaderProgram::setUniformValue(int location, GLuint value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glUniform1uiv(location, 1, &value);
	}

	void	ShaderProgram::setUniformValue(int location, glm::vec2 const& value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glUniform2fv(location, 1, &value[0]);
	}

	void	ShaderProgram::setUniformValue(int location, glm::vec3 const& value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glUniform3fv(location, 1, &value[0]);
	}

	void	ShaderProgram::setUniformValue(int location, glm::vec4 const& value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glUniform4fv(location, 1, &value[0]);
	}

	void	ShaderProgram::setUniformValue(int location, glm::mat2 const& value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]);
	}

	void	ShaderProgram::setUniformValue(int location, glm::mat3 const& value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
	}

	void	ShaderProgram::setUniformValue(int location, glm::mat4 const& value)
	{
		if (!this->isCreated() || !this->isLinked()) {
			return ;
		}
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}

	void	ShaderProgram::setUniformValue(std::string const& name, GLfloat value)
	{
		this->_setUniformValueFromString(name, value);
	}

	void	ShaderProgram::setUniformValue(std::string const& name, GLint value)
	{
		this->_setUniformValueFromString(name, value);
	}

	void	ShaderProgram::setUniformValue(std::string const& name, GLuint value)
	{
		this->_setUniformValueFromString(name, value);
	}

	void	ShaderProgram::setUniformValue(std::string const& name, glm::vec2 const& value)
	{
		this->_setUniformValueFromString(name, value);
	}
	
	void	ShaderProgram::setUniformValue(std::string const& name, glm::vec3 const& value)
	{
		this->_setUniformValueFromString(name, value);
	}
	
	void	ShaderProgram::setUniformValue(std::string const& name, glm::vec4 const& value)
	{
		this->_setUniformValueFromString(name, value);
	}
	
	void	ShaderProgram::setUniformValue(std::string const& name, glm::mat2 const& value)
	{
		this->_setUniformValueFromString(name, value);
	}
	
	void	ShaderProgram::setUniformValue(std::string const& name, glm::mat3 const& value)
	{
		this->_setUniformValueFromString(name, value);
	}
	
	void	ShaderProgram::setUniformValue(std::string const& name, glm::mat4 const& value)
	{
		this->_setUniformValueFromString(name, value);
	}
}
#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <GL/glew.h>
#include <unordered_map>
#include <list>
#include <string>
#include <glm/glm.hpp>

namespace EGL
{
	class Shader;

	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		bool	create();
		bool	addShader(Shader *shader);
		void	removeShader(Shader *shader);
		int		attributeLocation(std::string const& name);
		int		uniformLocation(std::string const& name);
		bool	use();
		bool	link();

		bool	isCreated() const;
		bool	isLinked() const;
		GLuint	programId() const;
		std::list<Shader*>	shaders() const;

		void	enableAttributeArray(int location);
		void	disableAttributeArray(int location);
		void	enableAttributeArray(std::string const& name);
		void	disableAttributeArray(std::string const& name);

		void	setAttributeBuffer(int location, GLenum type, int offset, int tupleSize, int stride = 0);
		void	setAttributeBuffer(std::string const& name, GLenum type, int offset, int tupleSize, int stride = 0);

		void	setAttributeValue(int location, GLfloat value);
		void	setAttributeValue(int location, glm::vec2 const& value);
		void	setAttributeValue(int location, glm::vec3 const& value);
		void	setAttributeValue(int location, glm::vec4 const& value);
		void	setAttributeValue(std::string const& name, GLfloat value);
		void	setAttributeValue(std::string const& name, glm::vec2 const& value);
		void	setAttributeValue(std::string const& name, glm::vec3 const& value);
		void	setAttributeValue(std::string const& name, glm::vec4 const& value);

		void	setUniformValue(int location, GLfloat value);
		void	setUniformValue(int location, GLint value);
		void	setUniformValue(int location, GLuint value);
		void	setUniformValue(int location, glm::vec2 const& value);
		void	setUniformValue(int location, glm::vec3 const& value);
		void	setUniformValue(int location, glm::vec4 const& value);
		void	setUniformValue(int location, glm::mat2 const& value);
		void	setUniformValue(int location, glm::mat3 const& value);
		void	setUniformValue(int location, glm::mat4 const& value);
		void	setUniformValue(std::string const& name, GLfloat value);
		void	setUniformValue(std::string const& name, GLint value);
		void	setUniformValue(std::string const& name, GLuint value);
		void	setUniformValue(std::string const& name, glm::vec2 const& value);
		void	setUniformValue(std::string const& name, glm::vec3 const& value);
		void	setUniformValue(std::string const& name, glm::vec4 const& value);
		void	setUniformValue(std::string const& name, glm::mat2 const& value);
		void	setUniformValue(std::string const& name, glm::mat3 const& value);
		void	setUniformValue(std::string const& name, glm::mat4 const& value);

	private:
		template<class T>
		void	_setAttributeValueFromString(std::string const& name, T value);

		template<class T>
		void	_setUniformValueFromString(std::string const& name, T value);

		GLuint				_programId;
		std::list<Shader*>	_shaders;
		bool				_isLinked;
		std::unordered_map<std::string, int>	_attributeLocations;
		std::unordered_map<std::string, int>	_uniformLocations;
	};

	template<class T>
	void	ShaderProgram::_setAttributeValueFromString(std::string const& name, T value) {
		int	location = this->attributeLocation(name);

		if (location >= 0) {
			this->setAttributeValue(location, value);
		}
	}

	template<class T>
	void	ShaderProgram::_setUniformValueFromString(std::string const& name, T value) {
		int	location = this->uniformLocation(name);

		if (location >= 0) {
			this->setUniformValue(location, value);
		}
	}


}

#endif
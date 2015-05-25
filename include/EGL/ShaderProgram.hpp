#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <GL/glew.h>
#include <list>
#include <string>

namespace EGL
{
	class Shader;

	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		bool	addShader(Shader *shader);
		void	removeShader(Shader *shader);
		int		attributeLocation(std::string const& name);
		int		uniformLocation(std::string const& name);
		bool	use();
		bool	link();

		bool	isValid() const;
		bool	isLinked() const;
		GLuint	programId() const;
		std::list<Shader*>	shaders() const;

	private:
		GLuint				_programId;
		std::list<Shader*>	_shaders;
		bool				_isLinked;
	};
}

#endif
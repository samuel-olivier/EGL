#ifndef __SHADER__
#define __SHADER__

#include <GL/glew.h>
#include <string>

namespace EGL
{
	class Shader
	{
	public:
		Shader(GLenum shaderType);
		~Shader();

		bool	compileSourceCode(const char* sourceCode);
		bool	compileSourceFile(std::string const& filename);

		bool	isValid() const;
		bool	isCompiled() const;
		GLenum	shaderType() const;
		GLuint	shaderId() const;

	private:
		bool	_isCompiled;
		GLenum	_shaderType;
		GLuint	_shaderId;
	};
}

#endif
#ifndef __EGL_BUFFER__
#define __EGL_BUFFER__

#include <GL/glew.h>

namespace EGL
{
	class Buffer
	{
	public:
		Buffer(GLenum type = GL_ARRAY_BUFFER);
		~Buffer();

		bool	create();
		void	destroy();
		bool	bind();
		void	setUsage(GLenum usage);
		void	allocate(const void *data, int count);
		void	write(int offset, const void * data, int count);

		bool	isCreated() const;
		GLenum	type() const;
		GLuint	bufferId() const;
		GLenum	usage() const;
		GLint	size() const;

	private:
		GLenum	_type;
		GLuint	_bufferId;
		GLenum	_usage;
	};
}

#endif
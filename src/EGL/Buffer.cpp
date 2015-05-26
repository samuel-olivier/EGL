#include "EGL/Buffer.hpp"

namespace EGL
{
	Buffer::Buffer(GLenum type) : _type(type), _bufferId(0), _usage(GL_STATIC_DRAW)
	{
	}

	Buffer::~Buffer()
	{
	}

	bool	Buffer::create()
	{
		if (this->_bufferId != 0) {
			return false;
		}
		glGenBuffers(1, &this->_bufferId);
		if (glGetError() != GL_NO_ERROR) {
			this->_bufferId = 0;
		}
		return this->isCreated();
	}

	void	Buffer::destroy()
	{
		glDeleteBuffers(1, &this->_bufferId);
		this->_bufferId = 0;
	}

	bool	Buffer::bind()
	{
		if (!this->isCreated()) {
			return false;
		}
		glBindBuffer(this->_type, this->_bufferId);
		return glGetError() == GL_NO_ERROR;
	}

	void	Buffer::setUsage(GLenum usage)
	{
		this->_usage = usage;
	}

	void	Buffer::allocate(const void *data, int count)
	{
		if (!this->isCreated()) {
			return ;
		}
		glBufferData(this->_type, count, data, this->_usage);		
	}

	void	Buffer::write(int offset, const void * data, int count)
	{
		if (!this->isCreated()) {
			return ;
		}
		glBufferSubData(this->_type, offset, count, data);		
	}

	bool	Buffer::isCreated() const
	{
		return this->_bufferId != 0;
	}

	GLenum	Buffer::type() const
	{
		return this->_type;
	}

	GLuint	Buffer::bufferId() const
	{
		return this->_bufferId;
	}

	GLenum	Buffer::usage() const
	{
		return this->_usage;
	}

	GLint	Buffer::size() const
	{
		GLint	res;

		glGetBufferParameteriv(this->_type, GL_BUFFER_SIZE, &res);
		return res;
	}
}

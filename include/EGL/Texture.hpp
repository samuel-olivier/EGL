#ifndef __EGL_TEXTURE__
#define __EGL_TEXTURE__

#include <GL/glew.h>
#include <string>

namespace sf
{
	class Texture;
}

namespace EGL
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		bool	load(std::string const& filePath);
		void	bind();

		GLuint	textureId() const;

		static void		unBind();

	private:
		sf::Texture		*_texture;
		GLuint			_id;
	};
}

#endif
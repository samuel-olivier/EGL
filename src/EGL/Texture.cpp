#include "EGL/Texture.hpp"

#include <SFML/Graphics.hpp>

namespace EGL
{
	Texture::Texture() : _texture(new sf::Texture), _id(0)
	{
	}

	Texture::~Texture()
	{
		delete this->_texture;
	}

	bool	Texture::load(std::string const& filePath)
	{
		this->_id = 0;
		sf::Image img;
		if (!img.loadFromFile(filePath))
			return false;
		glGenTextures(1, &this->_id);
		glBindTexture(GL_TEXTURE_2D, this->_id);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.getSize().x, img.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		return true;
	}

	void	Texture::bind()
	{
		if (this->_id > 0) {
			glBindTexture(GL_TEXTURE_2D, this->_id);
		} else {
			Texture::unBind();
		}
	}

	GLuint	Texture::textureId() const
	{
		return this->_id;
	}

	void	Texture::unBind()
	{
		sf::Texture::bind(NULL);
	}
}
#ifndef __CUBE__
#define __CUBE__

#include "Node.hpp"

#include <EGL/Texture.hpp>

namespace EGL
{
	class Mesh;
}

class Cube : public Node
{
public:
	Cube();
	~Cube();

	bool			initialize(glm::vec4 const& color);
	virtual bool	initialize();
	virtual void	update(EGL::InputManager& inputs, EGL::Clock const& clock);
	virtual void	draw(EGL::ShaderProgram& program, glm::mat4 const& view, glm::mat4 const& projection);

	void	setTexture(EGL::Texture const& texture);

private:
	EGL::Texture		_texture;
	EGL::Mesh			*_mesh;
};

#endif
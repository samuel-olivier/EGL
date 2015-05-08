#ifndef __CUBE__
#define __CUBE__

#include "Node.hpp"

namespace EGL
{
	class Mesh;
}

class Cube : public Node
{
public:
	Cube();
	~Cube();

	virtual bool	initialize();
	virtual void	update(EGL::InputManager& inputs, EGL::Clock const& clock);
	virtual void	draw(EGL::ShaderProgram& program, glm::mat4 const& view, glm::mat4 const& projection);

private:
	EGL::Mesh	*_mesh;
};

#endif
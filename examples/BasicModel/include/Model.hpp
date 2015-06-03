#ifndef __MODEL__
#define __MODEL__

#include "Node.hpp"

#include <string>

namespace EGL
{
	class Model;
}

class Model : public Node
{
public:
	Model();
	~Model();

	virtual bool	initialize();
	virtual bool	load(std::string const& filename);
	virtual void	update(EGL::InputManager& inputs, EGL::Clock const& clock);
	virtual void	draw(EGL::ShaderProgram& program, glm::mat4 const& view, glm::mat4 const& projection);

private:
	EGL::Model	*_model;
};

#endif
#ifndef __NODE__
#define __NODE__

#include <glm/glm.hpp>

#include <EGL/InputManager.hpp>
#include <EGL/ShaderProgram.hpp>
#include <EGL/Clock.hpp>

class Node
{
public:
	Node();
	~Node();

	virtual bool	initialize() = 0;
	virtual void	update(EGL::InputManager& inputs, EGL::Clock const& clock) = 0;
	virtual void	draw(EGL::ShaderProgram& program, glm::mat4 const& view, glm::mat4 const& projection) = 0;

	void	setPosition(glm::vec3 const& position);
	void	translate(glm::vec3 const& tranlation);
	glm::vec3 const&	position() const;

	void	setRotation(glm::vec3 const& rotation);
	void	rotate(float angle, glm::vec3 const& axe);
	glm::vec3 const&	rotation() const;

	void	setScaling(glm::vec3 const& scaling);
	void	scale(glm::vec3 const& scaling);
	glm::vec3 const&	scaling() const;

	glm::mat4 const&	worldSpaceMatrix();

private:
	bool		_needUpdate;
	glm::mat4	_worldSpaceMatrix;
	glm::vec3	_position;
	glm::vec3	_rotation;
	glm::vec3	_scaling;
};

#endif
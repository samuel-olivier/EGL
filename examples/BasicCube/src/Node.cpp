#include "../include/Node.hpp"

#include <glm/gtc/matrix_transform.hpp>


Node::Node() : _needUpdate(true), _worldSpaceMatrix(1.f), _position(0.f), _rotation(0.f), _scaling(1.f)
{
}

Node::~Node()
{
}

void	Node::setPosition(glm::vec3 const& position)
{
	this->_position = position;
	this->_needUpdate = true;
}

void	Node::translate(glm::vec3 const& tranlation)
{
	this->_position += tranlation;
	this->_needUpdate = true;
}

glm::vec3 const&	Node::position() const
{
	return this->_position;
}

void	Node::setRotation(glm::vec3 const& rotation)
{
	this->_rotation = rotation;
	this->_needUpdate = true;
}

void	Node::rotate(float angle, glm::vec3 const& axe)
{
	this->_rotation += angle * axe;
	this->_needUpdate = true;
}

glm::vec3 const&	Node::rotation() const
{
	return this->_rotation;
}

void	Node::setScaling(glm::vec3 const& scaling)
{
	this->_scaling = scaling;
	this->_needUpdate = true;
}

void	Node::scale(glm::vec3 const& scaling)
{
	this->_scaling.x *= scaling.x;
	this->_scaling.y *= scaling.y;
	this->_scaling.z *= scaling.z;
	this->_needUpdate = true;
}

glm::vec3 const&	Node::scaling() const
{
	return this->_scaling;
}

glm::mat4 const&	Node::worldSpaceMatrix()
{
	if (this->_needUpdate) {
		this->_worldSpaceMatrix = glm::mat4(1.f);
		this->_worldSpaceMatrix = glm::translate(this->_worldSpaceMatrix, this->_position);
		this->_worldSpaceMatrix = glm::rotate(this->_worldSpaceMatrix, this->_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		this->_worldSpaceMatrix = glm::rotate(this->_worldSpaceMatrix, this->_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		this->_worldSpaceMatrix = glm::rotate(this->_worldSpaceMatrix, this->_rotation.z, glm::vec3(0.f, 0.f, 1.f));
		this->_worldSpaceMatrix = glm::scale(this->_worldSpaceMatrix, this->_scaling);
		printf("%f %f %f\n", this->_scaling.x, this->_scaling.y, this->_scaling.z);
		this->_needUpdate = false;
	}
	return this->_worldSpaceMatrix;
}
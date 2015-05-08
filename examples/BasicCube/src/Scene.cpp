#include "../include/Scene.hpp"

#include "../include/Node.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void	Scene::addNode(Node *node)
{
	this->_nodes.insert(node);
}

void	Scene::removeNode(Node *node)
{
	auto	it = this->_nodes.find(node);

	if (it != this->_nodes.end()) {
		this->_nodes.erase(it);
	}
}

void	Scene::update(EGL::InputManager& inputs, EGL::Clock const& clock)
{
	for (Node *node : this->_nodes) {
		node->update(inputs, clock);
	}
}

void	Scene::draw(EGL::ShaderProgram& program, glm::mat4 const& view, glm::mat4 const& projection)
{
	for (Node *node : this->_nodes) {
		node->draw(program, view, projection);
	}
}

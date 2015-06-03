#ifndef __SCENE__
#define __SCENE__

#include <unordered_set>

#include <glm/glm.hpp>

#include <EGL/InputManager.hpp>
#include <EGL/Clock.hpp>
#include <EGL/ShaderProgram.hpp>

class Node;

class Scene
{
public:
	Scene();
	~Scene();

	void	addNode(Node *node);
	void	removeNode(Node *node);

	void	update(EGL::InputManager& inputs, EGL::Clock const& clock);
	void	draw(EGL::ShaderProgram& program, glm::mat4 const& view, glm::mat4 const& projection);

private:
	std::unordered_set<Node*>	_nodes;
};

#endif
#include "../include/Cube.hpp"

#include <iostream>

#include <EGL/Mesh.hpp>

Cube::Cube() : _mesh(new EGL::Mesh)
{
}

Cube::~Cube()
{
	delete _mesh;
}

bool	Cube::initialize()
{
	float	positions[24][3] = {
		// Front face
		{-0.5f, -0.5f, -0.5f},
		{-0.5f, 0.5f, -0.5f},
		{0.5f, 0.5f, -0.5f},
		{0.5f, -0.5f, -0.5f},
		// Back face
		{-0.5f, -0.5f, 0.5f},
		{-0.5f, 0.5f, 0.5f},
		{0.5f, 0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		// Top face
		{-0.5f, 0.5f, -0.5f},
		{-0.5f, 0.5f, 0.5f},
		{0.5f, 0.5f, 0.5f},
		{0.5f, 0.5f, -0.5f},
		// Bottom face
		{-0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		{0.5f, -0.5f, -0.5f},
		// Left face
		{-0.5f, -0.5f, 0.5f},
		{-0.5f, 0.5f, 0.5f},
		{-0.5f, 0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		// Right face
		{0.5f, -0.5f, 0.5f},
		{0.5f, 0.5f, 0.5f},
		{0.5f, 0.5f, -0.5f},
		{0.5f, -0.5f, -0.5f},
	};

	for (int i = 0; i < 24; ++i) {
		this->_mesh->pushVertex(glm::vec3(positions[i][0], positions[i][1], positions[i][2]), glm::vec3(), glm::vec2(), glm::vec4(1.f, 0.f, 0.f, 1.f));
	}
	for (int i = 0; i < 6; ++i) {
		int first = i * 4;
		this->_mesh->pushFace(first + 0, first + 1, first + 2);
		this->_mesh->pushFace(first + 0, first + 2, first + 3);
	}
	return this->_mesh->build();
}

void	Cube::update(EGL::InputManager& inputs)
{
	this->rotate(M_PI / 60, glm::vec3(0.f, 1.f, 0.f));
	// if (inputs.hasKeyInput(sf::Keyboard::Left))
}

void	Cube::draw(EGL::ShaderProgram& program, glm::mat4 const& view, glm::mat4 const& projection)
{
	this->_mesh->draw(program, this->worldSpaceMatrix(), view, projection, GL_QUADS);
}

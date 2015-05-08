#include "../include/Cube.hpp"

#include <iostream>
#include <SFML/Window.hpp>

#include <EGL/Mesh.hpp>

EGL::Mesh	*Cube::_mesh;

Cube::Cube()
{
}

Cube::~Cube()
{
}

bool	Cube::initialize()
{
	if (Cube::_mesh == NULL) {
		Cube::_mesh = new EGL::Mesh();
		float	positions[24][3] = {
			// Front face
			{-0.5f, -0.5f, 0.5f},
			{0.5f, -0.5f, 0.5f},
			{0.5f, 0.5f, 0.5f},
			{-0.5f, 0.5f, 0.5f},
			// Back face
			{-0.5f, -0.5f, -0.5f},
			{-0.5f, 0.5f, -0.5f},
			{0.5f, 0.5f, -0.5f},
			{0.5f, -0.5f, -0.5f},
			// Top face
			{-0.5f, 0.5f, -0.5f},
			{-0.5f, 0.5f, 0.5f},
			{0.5f, 0.5f, 0.5f},
			{0.5f, 0.5f, -0.5f},
			// Bottom face
			{-0.5f, -0.5f, -0.5f},
			{0.5f, -0.5f, -0.5f},
			{0.5f, -0.5f, 0.5f},
			{-0.5f, -0.5f, 0.5f},
			// Left face
			{-0.5f, -0.5f, 0.5f},
			{-0.5f, 0.5f, 0.5f},
			{-0.5f, 0.5f, -0.5f},
			{-0.5f, -0.5f, -0.5f},
			// Right face
			{0.5f, -0.5f, 0.5f},
			{0.5f, -0.5f, -0.5f},
			{0.5f, 0.5f, -0.5f},
			{0.5f, 0.5f, 0.5f},
		};

		for (int i = 0; i < 24; ++i) {
			Cube::_mesh->pushVertex(glm::vec3(positions[i][0], positions[i][1], positions[i][2]), glm::vec3(), glm::vec2(), glm::vec4(1.f, 0.f, 0.f, 1.f));
		}
		for (int i = 0; i < 6; ++i) {
			int first = i * 4;
			Cube::_mesh->pushFace(first + 0, first + 1, first + 2);
			Cube::_mesh->pushFace(first + 0, first + 2, first + 3);
		}
		Cube::_mesh->generateNormals();
		return Cube::_mesh->build();
	}
	return true;
}

void	Cube::update(EGL::InputManager& inputs, EGL::Clock const& clock)
{
	this->rotate(clock.elapsed() * M_PI, glm::vec3(0.f, 1.f, 0.f));
	if (inputs.isKeyPressed(sf::Keyboard::Left)) {
		this->translate(glm::vec3(-2.f, 0.f, 0.f) * clock.elapsed());
	}
	if (inputs.isKeyPressed(sf::Keyboard::Right)) {
		this->translate(glm::vec3(2.f, 0.f, 0.f) * clock.elapsed());
	}
	if (inputs.isKeyPressed(sf::Keyboard::Up)) {
		this->translate(glm::vec3(0.f, 0.f, -2.f) * clock.elapsed());
	}
	if (inputs.isKeyPressed(sf::Keyboard::Down)) {
		this->translate(glm::vec3(0.f, 0.f, 2.f) * clock.elapsed());
	}
}

void	Cube::draw(EGL::ShaderProgram& program, glm::mat4 const& view, glm::mat4 const& projection)
{
	Cube::_mesh->draw(program, this->worldSpaceMatrix(), view, projection);
}

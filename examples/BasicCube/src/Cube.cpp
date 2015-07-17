#include "../include/Cube.hpp"

#include <iostream>
#include <SFML/Window.hpp>

#include <EGL/Mesh.hpp>

Cube::Cube()
{
}

Cube::~Cube()
{
}

bool	Cube::initialize(glm::vec4 const& color)
{
	this->_mesh = new EGL::Mesh();
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
		glm::vec2 uv;
		uv.y = (i % 4) / 2;
		if (i % 4 == 1 || i % 4 == 2)
			uv.x = 1.f;
		this->_mesh->pushVertex(glm::vec3(positions[i][0], positions[i][1], positions[i][2]), glm::vec3(), uv, color);
	}
	for (int i = 0; i < 6; ++i) {
		int first = i * 4;
		this->_mesh->pushFace(first + 0, first + 1, first + 2);
		this->_mesh->pushFace(first + 0, first + 2, first + 3);
	}
	this->_mesh->generateNormals();
	return this->_mesh->build();
}

bool	Cube::initialize()
{
	return this->initialize(glm::vec4(0.f, 0.f, 0.f, 1.f));
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
	this->_texture.bind();
	this->_mesh->draw(program, this->worldSpaceMatrix(), view, projection);
}

void	Cube::setTexture(EGL::Texture const& texture)
{
	this->_texture = texture;
}
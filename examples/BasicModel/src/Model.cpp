#include "../include/Model.hpp"

#include <iostream>
#include <SFML/Window.hpp>

#include <EGL/Model.hpp>

Model::Model() : _model(NULL)
{
}

Model::~Model()
{
}

bool	Model::initialize()
{
	this->_model = new EGL::Model();

	return true;
}

bool	Model::load(std::string const& filename)
{
	if (this->_model != NULL) {
		return this->_model->load(filename);
	}
	return false;
}

void	Model::update(EGL::InputManager& inputs, EGL::Clock const& clock)
{
	// this->rotate(clock.elapsed() * M_PI, glm::vec3(0.f, 1.f, 0.f));
	if (inputs.isKeyPressed(sf::Keyboard::Left)) {
		this->translate(glm::vec3(-4.f, 0.f, 0.f) * clock.elapsed());
	}
	if (inputs.isKeyPressed(sf::Keyboard::Right)) {
		this->translate(glm::vec3(4.f, 0.f, 0.f) * clock.elapsed());
	}
	if (inputs.isKeyPressed(sf::Keyboard::Up)) {
		this->translate(glm::vec3(0.f, 0.f, -4.f) * clock.elapsed());
	}
	if (inputs.isKeyPressed(sf::Keyboard::Down)) {
		this->translate(glm::vec3(0.f, 0.f, 4.f) * clock.elapsed());
	}
	if (inputs.isKeyPressed(sf::Keyboard::Q)) {
		this->rotate(2.f * clock.elapsed(), glm::vec3(0.f, 1.f, 0.f));
	}
	if (inputs.isKeyPressed(sf::Keyboard::D)) {
		this->rotate(-2.f * clock.elapsed(), glm::vec3(0.f, 1.f, 0.f));
	}
	if (inputs.isKeyPressed(sf::Keyboard::Z)) {
		this->translate(glm::vec3(0.f, 4.f, 0.f) * clock.elapsed());
	}
	if (inputs.isKeyPressed(sf::Keyboard::S)) {
		this->translate(glm::vec3(0.f, -4.f, 0.f) * clock.elapsed());
	}
}

void	Model::draw(EGL::ShaderProgram& program, glm::mat4 const& view, glm::mat4 const& projection)
{
	this->_model->draw(program, this->worldSpaceMatrix(), view, projection);
}

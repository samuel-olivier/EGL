#include "../include/Game.hpp"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include <EGL/SFMLContext.hpp>
#include <EGL/ShaderProgram.hpp>
#include <EGL/Shader.hpp>

#include "../include/Node.hpp"
#include "../include/Model.hpp"

Game::Game() : _context(new EGL::SFMLContext)
{
}

Game::~Game()
{
}

bool	Game::initialize()
{
	this->_context->initialize(WINDOW_WIDTH, WINDOW_HEIGHT, "Window");
	std::cout << "Using OpenGL version " << glGetString(GL_VERSION) << std::endl;
	glEnable(GL_DEPTH_TEST);

	EGL::Shader			*vertexShader = new EGL::Shader(GL_VERTEX_SHADER);
	EGL::Shader			*fragmentShader = new EGL::Shader(GL_FRAGMENT_SHADER);
	std::cout << "Creating shader program : " << this->_shaderProgram.create() << std::endl;
	std::cout << "Compile vertex shader : " << vertexShader->compileSourceFile("../examples/assets/vertexShader.glsl") << std::endl;
	std::cout << "Compile fragment shader : " << fragmentShader->compileSourceFile("../examples/assets/fragmentShader.glsl") << std::endl;
	std::cout << "Adding vertex shader : " << this->_shaderProgram.addShader(vertexShader) << std::endl;
	std::cout << "Adding fragment shader : " << this->_shaderProgram.addShader(fragmentShader) << std::endl;
	std::cout << "Linking shader program : " << this->_shaderProgram.link() << std::endl;

	this->_cameraViewMatrix = glm::lookAt(glm::vec3(0.f, 30.f, 30.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	this->_cameraProjectionMatrix = glm::perspective(glm::radians(45.0f), float(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.0f);

	Model	*marvin = new Model();
	marvin->initialize();
	std::cout << "Loading Marvin : " << marvin->load("../examples/assets/marvin.fbx") << std::endl;
	marvin->scale(glm::vec3(0.08f));
	this->_scene.addNode(marvin);
	return true;
}

void	Game::update()
{
	this->_context->updateInputs(this->_inputs);
	this->_clock.update();
	this->_scene.update(this->_inputs, this->_clock);
}

void	Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->_scene.draw(this->_shaderProgram, this->_cameraViewMatrix, this->_cameraProjectionMatrix);
	this->_context->display();
}

void	Game::run()
{
	while (this->_context->windowIsOpen()) {
		this->update();
		this->draw();
	}
}

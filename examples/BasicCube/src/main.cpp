#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <EGL/SFMLContext.hpp>
#include <EGL/ShaderProgram.hpp>
#include <EGL/Shader.hpp>

#include "../include/Cube.hpp"

#define WINDOW_WIDTH 800.f
#define WINDOW_HEIGHT 600.f

EGL::ShaderProgram	*basicShaderProgram()
{
	EGL::ShaderProgram	*program = new EGL::ShaderProgram;
	EGL::Shader			*vertexShader = new EGL::Shader(GL_VERTEX_SHADER);
	EGL::Shader			*fragmentShader = new EGL::Shader(GL_FRAGMENT_SHADER);

	std::cout << "Creating shader program : " << program->create() << std::endl;
	std::cout << "Compile vertex shader : " << vertexShader->compileSourceFile("../examples/BasicCube/assets/vertexShader.glsl") << std::endl;
	std::cout << "Compile fragment shader : " << fragmentShader->compileSourceFile("../examples/BasicCube/assets/fragmentShader.glsl") << std::endl;
	std::cout << "Adding vertex shader : " << program->addShader(vertexShader) << std::endl;
	std::cout << "Adding fragment shader : " << program->addShader(fragmentShader) << std::endl;
	std::cout << "Linking shader program : " << program->link() << std::endl;
	return program;
}

int	main()
{
	EGL::RenderContext	*context = new EGL::SFMLContext();
	EGL::InputManager	inputs;
	EGL::ShaderProgram	*program;
	EGL::Clock			clock;

	//Creating OpenGL Context & Window
	context->initialize(WINDOW_WIDTH, WINDOW_HEIGHT, "Window");
	std::cout << "Using OpenGL version " << glGetString(GL_VERSION) << std::endl;

	//Create the shader prograg
	program = basicShaderProgram();

	// Setting Up Camera
	glm::mat4			v = glm::lookAt(glm::vec3(0.f, 1.f, 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4			p = glm::perspective(glm::radians(45.0f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

	Node	*cube = new Cube();
	cube->initialize();

	glEnable(GL_DEPTH_TEST);

	// Game Loop
	while (context->windowIsOpen()) {
		// Update Input & Clock
		context->updateInputs(inputs);
		clock.update();

		// Update scene
		cube->update(inputs, clock);

		// Draw
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cube->draw(*program, v, p);
		context->display();
	}
	return 0;
}
#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>

#include "EGL/SFMLContext.hpp"
#include "EGL/ShaderProgram.hpp"
#include "EGL/Shader.hpp"
#include "EGL/Mesh.hpp"

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

	context->initialize(800, 600, "Window");
	std::cout << "Using OpenGL version " << glGetString(GL_VERSION) << std::endl;
	program = basicShaderProgram();
	EGL::Mesh	*cube = new EGL::Mesh;
	cube->pushVertex(glm::vec3(-1.f, -1.f, 0.f), glm::vec3(), glm::vec2(), glm::vec4(1.f, 0.f, 0.f, 1.f));
	cube->pushVertex(glm::vec3(0.f, 1.f, 0.f), glm::vec3(), glm::vec2(), glm::vec4(0.f, 1.f, 0.f, 1.f));
	cube->pushVertex(glm::vec3(1.f, -1.f, 0.f), glm::vec3(), glm::vec2(), glm::vec4(0.f, 0.f, 1.f, 1.f));
	cube->pushFace(0, 1, 2);
	std::cout << "Building cube : " << cube->build() << std::endl;
	while (context->windowIsOpen()) {
		context->updateInputs(inputs);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cube->draw(*program, glm::mat4(1.f), glm::mat4(1.f), glm::mat4(1.f));
		context->display();
	}
	return 0;
}
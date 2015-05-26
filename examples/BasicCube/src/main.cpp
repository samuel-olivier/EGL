#include "EGL/SFMLContext.hpp"
#include <iostream>
#include <SFML/Window.hpp>

#include "EGL/SFMLContext.hpp"
#include "EGL/ShaderProgram.hpp"

int	main()
{
	EGL::RenderContext	*context = new EGL::SFMLContext();
	EGL::InputManager	inputs;
	EGL::ShaderProgram	program;

	std::cout << "Creating shader program : " << program.create() << std::endl;
	std::cout << "Linking shader program : " << program.link() << std::endl;
	context->initialize(800, 600, "Window");
	while (context->windowIsOpen()) {
		context->updateInputs(inputs);
		context->display();
	}
	return 0;
}
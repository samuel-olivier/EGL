#include "EGL/SFMLContext.hpp"

#include <iostream>
#include <SFML/Window.hpp>

int	main()
{
	EGL::RenderContext	*context = new EGL::SFMLContext();
	EGL::InputManager	inputs;

	context->initialize(800, 600, "Window");
	while (context->windowIsOpen()) {
		context->updateInputs(inputs);
			std::cout << "up : " << inputs.isKeyPressed(sf::Keyboard::Up) << std::endl;
		context->display();
	}
	return 0;
}
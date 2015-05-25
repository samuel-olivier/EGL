#include "EGL/SFMLContext.hpp"

#include <SFML/Window.hpp>

namespace EGL
{
	SFMLContext::SFMLContext() : _window(NULL)
	{
	}

	SFMLContext::~SFMLContext()
	{
	}

	bool	SFMLContext::initialize(unsigned int windowWidth, unsigned int windowHeight, std::string const& windowName)
	{
		sf::ContextSettings settings;

		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 3;
		settings.minorVersion = 0;
		_window = new sf::Window(sf::VideoMode(windowWidth, windowHeight), windowName, sf::Style::Default, settings);
		_window->setVerticalSyncEnabled(true);
		return _window->isOpen();
	}
	
	void	SFMLContext::display()
	{
		_window->display();
	}
}
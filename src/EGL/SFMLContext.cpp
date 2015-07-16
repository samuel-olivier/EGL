#include "EGL/SFMLContext.hpp"

#include <SFML/Window.hpp>
#include <GL/glew.h>

namespace EGL
{
	SFMLContext::SFMLContext() : _window(NULL)
	{
	}

	SFMLContext::~SFMLContext()
	{
		if (this->_window) {
			delete _window;
		}
	}

	bool	SFMLContext::initialize(unsigned int windowWidth, unsigned int windowHeight, std::string const& windowName)
	{
		sf::ContextSettings settings;

		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 3;
		settings.minorVersion = 0;
		this->_window = new sf::Window(sf::VideoMode(windowWidth, windowHeight), windowName, sf::Style::Default, settings);
		settings = this->_window->getSettings();
		this->_window->setVerticalSyncEnabled(true);
		this->_window->setFramerateLimit(60);
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			return false;
		}
		// GLuint VertexArrayID;
		// glGenVertexArrays(1, &VertexArrayID);
		// glBindVertexArray(VertexArrayID);
		return this->_window->isOpen();
	}
	
	void	SFMLContext::updateInputs(InputManager& inputs)
	{
		inputs.clear();
		if (!this->_window) {
			return ;
		}
		sf::Event event;
		while (this->_window->pollEvent(event)) {
		    if (event.type == sf::Event::Closed) {
		        this->_window->close();
		    } else if (event.type == sf::Event::KeyPressed) {
		    	inputs.addKeyPressed(event.key.code);
		    } else if (event.type == sf::Event::KeyReleased) {
		    	inputs.addKeyReleased(event.key.code);
		    } else if (event.type == sf::Event::MouseMoved) {
		    	inputs.setMousePosition(glm::ivec2(event.mouseMove.x, event.mouseMove.y));
		    } else if (event.type == sf::Event::MouseWheelMoved) {
		    	// Just for SFML 2.3+
		    	// glm::ivec2	delta;
		    	// if (event.mouseWheel.wheel == sf::Mouse::HorizontalWheel) {
		    	// 	delta.x = event.mouseWheel.delta;
		    	// } else if (event.mouseWheel.wheel == sf::Mouse::VerticalWheel) {
		    	// 	delta.y = event.mouseWheel.delta;
		    	// }
		    	// inputs.setMouseWheel(delta);
		    	inputs.setMouseWheel(glm::ivec2(0, event.mouseWheel.delta));
		    }
		}
	}

	void	SFMLContext::display()
	{
		if (this->_window) {
			this->_window->display();
		}
	}

	bool	SFMLContext::windowIsOpen() const
	{
		return this->_window ? this->_window->isOpen() : false;
	}

}

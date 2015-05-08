#ifndef __EGL_SFML_CONTEXT__
#define __EGL_SFML_CONTEXT__

#include "EGL/RenderContext.hpp"

namespace sf
{
	class Window;
}

namespace EGL
{
	class SFMLContext : public RenderContext
	{
	public:
		SFMLContext();
		virtual ~SFMLContext();

		virtual bool	initialize(unsigned int windowWidth, unsigned int windowHeight, std::string const& windowName);
		virtual void	updateInputs(InputManager& inputs);
		virtual void	display();

		virtual bool	windowIsOpen() const;

	private:
		sf::Window	*_window;
	};
}

#endif
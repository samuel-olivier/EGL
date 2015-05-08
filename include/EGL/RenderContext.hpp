#ifndef __EGL_RENDER_CONTEXT__
#define __EGL_RENDER_CONTEXT__

#include <string>

#include "InputManager.hpp"

namespace EGL
{
	class RenderContext
	{
	public:
		virtual ~RenderContext() {};

		virtual bool	initialize(unsigned int windowWidth, unsigned int windowHeight, std::string const& windowName) = 0;
		virtual void	updateInputs(InputManager& inputs) = 0;
		virtual void	display() = 0;

		virtual bool	windowIsOpen() const = 0;
	};
}

#endif
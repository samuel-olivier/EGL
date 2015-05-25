#ifndef __RENDER_CONTEXT__
#define __RENDER_CONTEXT__

#include <string>

namespace EGL
{
	class RenderContext
	{
	public:
		virtual ~RenderContext() {};

		virtual bool	initialize(unsigned int windowWidth, unsigned int windowHeight, std::string const& windowName) = 0;
		virtual void	display() = 0;
	};
}

#endif
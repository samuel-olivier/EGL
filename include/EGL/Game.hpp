#ifndef __EGL_GAME__
#define __EGL_GAME__

namespace EGL
{
	class Game
	{
	public:
		virtual ~Game() {}

		virtual bool	initialize() = 0;
		virtual void	update() = 0;
		virtual void	draw() = 0;
	};
}

#endif
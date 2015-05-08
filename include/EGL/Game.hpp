#ifndef __EGL_GAME__
#define __EGL_GAME__

namespace EGL
{
	class Game
	{
	public:
		virtual ~Game() {}

		virtual void	initialize() = 0;
		virtual void	update() = 0;
		virtual void	draw() = 0;
	};
}

#endif
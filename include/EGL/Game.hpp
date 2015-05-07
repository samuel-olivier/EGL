#ifndef __GAME__
#define __GAME__

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
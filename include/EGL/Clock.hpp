#ifndef __EGL_CLOCK__
#define __EGL_CLOCK__

#include <time.h>

namespace EGL
{
	class Clock
	{
	public:
		Clock();
		~Clock();

		float	restart();
		float	currentFrameDuration() const;
		
		void	update();
		float	elapsed() const;

		static float	currentTime();
		static void		sleep(float sec);

	private:
		static float	_toSeconds(timespec *time);
		static void		_currentTime(timespec *time);

		timespec	_last;
		float		_elapsed;
	};
}

#endif
#include "EGL/Clock.hpp"

namespace EGL
{
	Clock::Clock()
	{
		Clock::_currentTime(&this->_last);
	}

	Clock::~Clock()
	{
	}

	float	Clock::restart()
	{
		timespec now;
		timespec delta;

		Clock::_currentTime(&now);
		delta.tv_sec = now.tv_sec - this->_last.tv_sec;
		delta.tv_nsec = now.tv_nsec - this->_last.tv_nsec;
		this->_last = now;
		return Clock::_toSeconds(&delta);
	}

	float	Clock::currentFrameDuration() const
	{
		timespec delta;

		Clock::_currentTime(&delta);
		delta.tv_sec -= this->_last.tv_sec;
		delta.tv_nsec -= this->_last.tv_nsec;
		return Clock::_toSeconds(&delta);
	}

	void	Clock::update()
	{
		this->_elapsed = this->restart();
	}

	float	Clock::elapsed() const
	{
		return this->_elapsed;
	}

	float	Clock::currentTime()
	{
		timespec t;

		Clock::_currentTime(&t);
		return Clock::_toSeconds(&t);
	}

	void	Clock::sleep(float sec)
	{
		timespec d;

		d.tv_sec = sec;
		d.tv_nsec = (sec - (int)sec) * 10e8;
		nanosleep(&d, NULL);
	}

	float	Clock::_toSeconds(timespec *time)
	{
		return time->tv_sec + float(time->tv_nsec) / 1000000000;
	}

	void	Clock::_currentTime(timespec *t)
	{
		clock_gettime(CLOCK_MONOTONIC, t);
	}
}
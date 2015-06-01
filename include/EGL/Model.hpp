#ifndef __EGL_MODEL__
#define __EGL_MODEL__

#include <iostream>

namespace EGL
{
	class Model
	{
	public:
		Model();
		~Model();

		bool	load(std::string const& filename);

	private:
		
	};
}

#endif
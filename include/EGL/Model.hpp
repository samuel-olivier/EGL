#ifndef __EGL_MODEL__
#define __EGL_MODEL__

#include <string>

#include <glm/glm.hpp>

#include <EGL/ShaderProgram.hpp>

namespace EGL
{
	class FBXModel;

	class Model
	{
	public:
		Model();
		~Model();

		bool	load(std::string const& filename);
		void	draw(EGL::ShaderProgram& program, glm::mat4 const& model, glm::mat4 const& view, glm::mat4 const& projection);

	private:
		FBXModel	*_model;
	};
}

#endif
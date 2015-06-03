#include "EGL/Model.hpp"

#include "EGL/FBXModel.hpp"

namespace EGL
{
	Model::Model() : _model(NULL)
	{
	}

	Model::~Model()
	{
	}

	bool	Model::load(std::string const& filename)
	{
		this->_model = new FBXModel();

		return this->_model->load(filename);
	}

	void	Model::draw(EGL::ShaderProgram& program, glm::mat4 const& model, glm::mat4 const& view, glm::mat4 const& projection)
	{
		this->_model->draw(program, model, view, projection);
	}

}
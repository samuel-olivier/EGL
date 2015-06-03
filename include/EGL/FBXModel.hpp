#ifndef __EGL_FBX_MODEL__
#define __EGL_FBX_MODEL__

#include <string>
#include <unordered_map>

#include <fbxsdk.h>
#include <glm/glm.hpp>

#include <EGL/ShaderProgram.hpp>


namespace EGL
{
	class Buffer;

	struct NodeData
	{
		Buffer	*vertexBuffer;
		Buffer	*indexBuffer;
	};

	class FBXModel
	{
	public:
		FBXModel();
		~FBXModel();

		bool	load(std::string const& filename);
		void	draw(EGL::ShaderProgram& program, glm::mat4 const& model, glm::mat4 const& view, glm::mat4 const& projection);

	private:
		bool	_build(FbxNode *current = NULL);
		bool	_createMeshes(FbxNode *current);
		bool	_createMesh(FbxMesh *mesh);

		void	_draw(FbxNode *current, EGL::ShaderProgram& program, glm::mat4 const& model, glm::mat4 const& view, glm::mat4 const& projection);
		void	_drawMeshes(FbxNode *current, EGL::ShaderProgram& program, glm::mat4 const& model, glm::mat4 const& view, glm::mat4 const& projection);

		FbxNode						*_root;
		std::unordered_map<FbxMesh*, NodeData>	_data;
		std::unordered_map<int, int>	_tmp;

		static FbxManager	*_manager;
	};

}

#endif
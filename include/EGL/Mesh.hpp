#ifndef __MESH__
#define __MESH__

#include <glm/glm.hpp>
#include <vector>

#include "ShaderProgram.hpp"

namespace EGL
{
	class Buffer;

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		bool	build();
		void	pushVertex(glm::vec3 const& position, glm::vec3 const& normal = glm::vec3(), glm::vec2 const& texCoord = glm::vec2(), glm::vec4 const& color = glm::vec4());
		void	pushFace(int vertexIdx1, int vertexIdx2, int vertexIdx3);

		void	setVertexPosition(int idx, glm::vec3 const& position);
		void	setVertexNormal(int idx, glm::vec3 const& normal);
		void	setVertexTexCoord(int idx, glm::vec2 const& texCoord);
		void	setVertexColor(int idx, glm::vec4 const& color);

		std::vector<glm::vec3> const&	vertexPositions() const;
		std::vector<glm::vec3> const&	vertexNormals() const;
		std::vector<glm::vec2> const&	vertexTexCoords() const;
		std::vector<glm::vec4> const&	vertexColors() const;
		glm::vec3 const&	vertexPosition(int idx) const;
		glm::vec3 const&	vertexNormal(int idx) const;
		glm::vec2 const&	vertexTexCoord(int idx) const;
		glm::vec4 const&	vertexColor(int idx) const;

		void	draw(ShaderProgram& program, glm::mat4 const& model, glm::mat4 const& view, glm::mat4 const& projection, GLenum drawMode = GL_TRIANGLES);

	private:
		Buffer					*_vertexBuffer;
		Buffer					*_indexBuffer;
		std::vector<glm::vec3>	_vertexPositions;
		std::vector<glm::vec3>	_vertexNormals;
		std::vector<glm::vec2>	_vertexTexCoords;
		std::vector<glm::vec4>	_vertexColors;
		std::vector<unsigned int>		_faces;
	};
}

#endif
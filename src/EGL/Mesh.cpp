#include "EGL/Mesh.hpp"

#include "EGL/Buffer.hpp"

namespace EGL
{
	Mesh::Mesh() : _vertexBuffer(new Buffer(GL_ARRAY_BUFFER)), _indexBuffer(new Buffer(GL_ELEMENT_ARRAY_BUFFER))
	{
	}

	Mesh::~Mesh()
	{
		delete this->_vertexBuffer;
		delete this->_indexBuffer;
	}

	bool	Mesh::build()
	{
		if ((!this->_vertexBuffer->isCreated() && !this->_vertexBuffer->create()) ||
			(!this->_indexBuffer->isCreated() && !this->_indexBuffer->create())) {
			return false;
		}
		std::vector<float> vertexData;
		vertexData.resize(this->_vertexPositions.size() * 12);
		for (size_t i = 0; i < this->_vertexPositions.size(); ++i) {
			vertexData[i * 12 + 0] = this->_vertexPositions[i].x;
			vertexData[i * 12 + 1] = this->_vertexPositions[i].y;
			vertexData[i * 12 + 2] = this->_vertexPositions[i].z;
			vertexData[i * 12 + 3] = this->_vertexNormals[i].x;
			vertexData[i * 12 + 4] = this->_vertexNormals[i].y;
			vertexData[i * 12 + 5] = this->_vertexNormals[i].z;
			vertexData[i * 12 + 6] = this->_vertexTexCoords[i].x;
			vertexData[i * 12 + 7] = this->_vertexTexCoords[i].y;
			vertexData[i * 12 + 8] = this->_vertexColors[i].x;
			vertexData[i * 12 + 9] = this->_vertexColors[i].y;
			vertexData[i * 12 + 10] = this->_vertexColors[i].z;
			vertexData[i * 12 + 11] = this->_vertexColors[i].w;
		}
		if (!this->_vertexBuffer->bind()) {
			return false;
		}
		this->_vertexBuffer->allocate(vertexData.data(), sizeof(float) * vertexData.size());

		if (!this->_indexBuffer->bind()) {
			return false;
		}
		this->_indexBuffer->allocate(this->_faces.data(), sizeof(unsigned int) * this->_faces.size());
		return true;
	}

	void	Mesh::pushVertex(glm::vec3 const& position, glm::vec3 const& normal, glm::vec2 const& texCoord, glm::vec4 const& color)
	{
		this->_vertexPositions.push_back(position);
		this->_vertexNormals.push_back(normal);
		this->_vertexTexCoords.push_back(texCoord);
		this->_vertexColors.push_back(color);
	}

	void	Mesh::pushFace(int vertexIdx1, int vertexIdx2, int vertexIdx3)
	{
		this->_faces.push_back(vertexIdx1);
		this->_faces.push_back(vertexIdx2);
		this->_faces.push_back(vertexIdx3);
	}

	void	Mesh::draw(ShaderProgram& program, glm::mat4 const& model, glm::mat4 const& view, glm::mat4 const& projection, GLenum drawMode)
	{
		if (!this->_vertexBuffer->isCreated() || !this->_indexBuffer->isCreated()) {
			return ;
		}
		if (!this->_vertexBuffer->bind()) {
			return ;
		}
		program.use();
		program.enableAttributeArray("position");
		program.enableAttributeArray("normal");
		program.enableAttributeArray("texCoord");
		program.enableAttributeArray("color");

		program.setAttributeBuffer("position", GL_FLOAT, 0, 3, 12 * sizeof(float));
		program.setAttributeBuffer("normal", GL_FLOAT, 3 * sizeof(float), 3, 12 * sizeof(float));
		program.setAttributeBuffer("texCoord", GL_FLOAT, 6 * sizeof(float), 2, 12 * sizeof(float));
		program.setAttributeBuffer("color", GL_FLOAT, 8 * sizeof(float), 4, 12 * sizeof(float));
		program.setUniformValue("mvp", projection * view * model);
		program.setUniformValue("m", model);
		program.setUniformValue("v", view);
		program.setUniformValue("p", projection);

		if (!this->_indexBuffer->bind()) {
			return ;
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(drawMode, this->_faces.size(), GL_UNSIGNED_INT, (GLvoid*)0);
		program.disableAttributeArray("position");
		program.disableAttributeArray("normal");
		program.disableAttributeArray("texCoord");
		program.disableAttributeArray("color");
	}

	void	Mesh::setVertexPosition(int idx, glm::vec3 const& position)
	{
		this->_vertexPositions[idx] = position;
	}

	void	Mesh::setVertexNormal(int idx, glm::vec3 const& normal)
	{
		this->_vertexNormals[idx] = normal;
	}

	void	Mesh::setVertexTexCoord(int idx, glm::vec2 const& texCoord)
	{
		this->_vertexTexCoords[idx] = texCoord;
	}

	void	Mesh::setVertexColor(int idx, glm::vec4 const& color)
	{
		this->_vertexColors[idx] = color;
	}

	std::vector<glm::vec3> const&	Mesh::vertexPositions() const
	{
		return this->_vertexPositions;
	}

	std::vector<glm::vec3> const&	Mesh::vertexNormals() const
	{
		return this->_vertexNormals;
	}

	std::vector<glm::vec2> const&	Mesh::vertexTexCoords() const
	{
		return this->_vertexTexCoords;
	}

	std::vector<glm::vec4> const&	Mesh::vertexColors() const
	{
		return this->_vertexColors;
	}

	glm::vec3 const&	Mesh::vertexPosition(int idx) const
	{
		return this->_vertexPositions[idx];
	}

	glm::vec3 const&	Mesh::vertexNormal(int idx) const
	{
		return this->_vertexNormals[idx];
	}

	glm::vec2 const&	Mesh::vertexTexCoord(int idx) const
	{
		return this->_vertexTexCoords[idx];
	}

	glm::vec4 const&	Mesh::vertexColor(int idx) const
	{
		return this->_vertexColors[idx];
	}
}
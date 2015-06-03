#include "EGL/FBXModel.hpp"

#include <vector>

#include "EGL/Buffer.hpp"

namespace EGL
{
	FbxManager	*FBXModel::_manager = NULL;

	FBXModel::FBXModel() : _root(NULL)
	{
	}

	FBXModel::~FBXModel()
	{
	}

	bool	FBXModel::load(std::string const& filename)
	{
		if (FBXModel::_manager == NULL) {
			FBXModel::_manager = FbxManager::Create();
		}
		FbxIOSettings *ios = FbxIOSettings::Create(FBXModel::_manager, IOSROOT);
		FBXModel::_manager->SetIOSettings(ios);
		FbxImporter* importer = FbxImporter::Create(FBXModel::_manager, "");

		if(!importer->Initialize(filename.c_str(), -1, FBXModel::_manager->GetIOSettings())) {
			return false;
		}

		FbxScene* scene = FbxScene::Create(FBXModel::_manager, "scene");
		importer->Import(scene);
		importer->Destroy();

		FbxGeometryConverter converter(FBXModel::_manager);
		converter.Triangulate(scene, true);
		this->_root = scene->GetRootNode();
		bool res = this->_build();
		return res;
		// return this->_build();
	}

	void	FBXModel::draw(EGL::ShaderProgram& program, glm::mat4 const& model, glm::mat4 const& view, glm::mat4 const& projection)
	{
		program.use();
		program.enableAttributeArray("vertexPosition_modelspace");
		program.enableAttributeArray("vertexNormal_modelspace");
		program.enableAttributeArray("vertexUV");
		program.enableAttributeArray("vertexColor");

		program.setUniformValue("V", view);
		program.setUniformValue("LightPosition_worldspace", glm::vec3(0.0, 6.0, 0.0));

		this->_draw(this->_root, program, model, view, projection);

		program.disableAttributeArray("vertexPosition_modelspace");
		program.disableAttributeArray("vertexNormal_modelspace");
		program.disableAttributeArray("vertexUV");
		program.disableAttributeArray("vertexColor");
	}

	bool	FBXModel::_build(FbxNode *current)
	{
		if (current == NULL) {
			current = this->_root;
		}
		if (!this->_createMeshes(current)) {
			return false;
		}
		for (int i = 0; i < current->GetChildCount(); ++i) {
			FbxNode	*child = current->GetChild(i);

			if (child != NULL && !this->_build(child)) {
				return false;
			}
		}
		return true;
	}

	bool	FBXModel::_createMeshes(FbxNode *current)
	{
		for (int i = 0; i < current->GetNodeAttributeCount(); ++i) {
			FbxNodeAttribute	*attr = current->GetNodeAttributeByIndex(i);

			if (attr->GetAttributeType() != FbxNodeAttribute::eMesh) {
				continue ;
			}
			FbxMesh	*mesh = dynamic_cast<FbxMesh*>(attr);
			if (mesh == NULL) {
				continue ;
			}
			if (!this->_createMesh(mesh)) {
				return false;
			}
		}
		return true;
	}

	bool	FBXModel::_createMesh(FbxMesh *mesh)
	{
		NodeData	data;
		data.vertexBuffer = new EGL::Buffer(GL_ARRAY_BUFFER);
		if (!data.vertexBuffer->create()) {
			return false;
		}
		std::vector<float> vertexData;
		vertexData.resize(mesh->GetControlPointsCount() * 12);
		FbxVector4* controlPoints = mesh->GetControlPoints();
		std::vector<FbxVector4>	normals;
		normals.resize(mesh->GetControlPointsCount(), FbxVector4(0.f, 0.f, 0.f));
		for (int i = 0; i < mesh->GetPolygonCount(); ++i) {
			mesh->GetPolygonVertexNormal(i, 0, normals[mesh->GetPolygonVertex(i, 0)]);
			mesh->GetPolygonVertexNormal(i, 1, normals[mesh->GetPolygonVertex(i, 1)]);
			mesh->GetPolygonVertexNormal(i, 2, normals[mesh->GetPolygonVertex(i, 2)]);
		}
		for (int i = 0; i < mesh->GetControlPointsCount(); ++i) {
			vertexData[i * 12 + 0] = controlPoints[i][0];
			vertexData[i * 12 + 1] = controlPoints[i][1];
			vertexData[i * 12 + 2] = controlPoints[i][2];
			if ((size_t)i < normals.size()) {
				vertexData[i * 12 + 3] = normals[i][0];
				vertexData[i * 12 + 4] = normals[i][1];
				vertexData[i * 12 + 5] = normals[i][2];
			} else {
				vertexData[i * 12 + 3] = 0.f;
				vertexData[i * 12 + 4] = 0.f;
				vertexData[i * 12 + 5] = 0.f;
			}
			vertexData[i * 12 + 6] = 0.f;
			vertexData[i * 12 + 7] = 0.f;
			vertexData[i * 12 + 8] = 1.f;
			vertexData[i * 12 + 9] = 1.f;
			vertexData[i * 12 + 10] = 1.f;
			vertexData[i * 12 + 11] = 1.f;
		}
		if (!data.vertexBuffer->bind()) {
			return false;
		}
		data.vertexBuffer->allocate(vertexData.data(), sizeof(float) * vertexData.size());

		data.indexBuffer = new EGL::Buffer(GL_ELEMENT_ARRAY_BUFFER);
		if (!data.indexBuffer->create()) {
			return false;
		}
		if (!data.indexBuffer->bind()) {
			return false;
		}
		data.indexBuffer->allocate(mesh->GetPolygonVertices(), sizeof(unsigned int) * mesh->GetPolygonVertexCount());
		this->_data[mesh] = data;
		return true;
	}

	void	FBXModel::_draw(FbxNode *current, EGL::ShaderProgram& program, glm::mat4 const& model, glm::mat4 const& view, glm::mat4 const& projection)
	{
		FbxAMatrix& fbxLocal = current->EvaluateLocalTransform();
		glm::mat4	local;

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				local[i][j] = fbxLocal.Get(i, j);
			}
		}
		glm::mat4 world = model * local;
		_drawMeshes(current, program, world, view, projection);
		for (int i = 0; i < current->GetChildCount(); ++i) {
			FbxNode	*child = current->GetChild(i);

			if (child != NULL) {
				this->_draw(child, program, world, view, projection);
			}
		}
	}

	void	FBXModel::_drawMeshes(FbxNode *current, EGL::ShaderProgram& program, glm::mat4 const& model, glm::mat4 const& view, glm::mat4 const& projection)
	{
		for (int i = 0; i < current->GetNodeAttributeCount(); ++i) {
			FbxNodeAttribute	*attr = current->GetNodeAttributeByIndex(i);

			if (attr->GetAttributeType() != FbxNodeAttribute::eMesh) {
				continue ;
			}
			FbxMesh	*mesh = dynamic_cast<FbxMesh*>(attr);
			if (mesh == NULL) {
				continue ;
			}
			auto it = this->_data.find(mesh);
			if (it == this->_data.end()) {
				continue ;
			}
			NodeData& buffers = it->second;
			if (!buffers.vertexBuffer->bind()) {
				continue ;
			}
			program.setAttributeBuffer("vertexPosition_modelspace", GL_FLOAT, 0, 3, 12 * sizeof(float));
			program.setAttributeBuffer("vertexNormal_modelspace", GL_FLOAT, 3 * sizeof(float), 3, 12 * sizeof(float));
			program.setAttributeBuffer("vertexUV", GL_FLOAT, 6 * sizeof(float), 2, 12 * sizeof(float));
			program.setAttributeBuffer("vertexColor", GL_FLOAT, 8 * sizeof(float), 4, 12 * sizeof(float));
			program.setUniformValue("MVP", projection * view * model);
			program.setUniformValue("M", model);

			if (!buffers.indexBuffer->bind()) {
				continue ;
			}
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, mesh->GetPolygonVertexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
		}
	}
}
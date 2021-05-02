#include "GLTFLoader.h"
#include "rendering/Material.h"
#include "rendering/primitive.h"
#include <iostream>
#include <json.hpp>
#include "glm/gtc/type_ptr.hpp"

using json = nlohmann::json;

std::shared_ptr<Scene> GLTFLoader::Load(string path) {
	std::ifstream fileStream (path);
	json gltfJson;
	fileStream >> gltfJson;
	auto file = gltfJson.get<GLTFFile>();
	auto defaultScene = file.scenes[file.scene];
	return GLTFLoader::ProcessScene(file, defaultScene);
}

std::shared_ptr<Scene> GLTFLoader::ProcessScene(const GLTFFile& file, const GLTFScene& scene) {
	std::shared_ptr<Scene> scenePtr = std::make_shared<Scene>();
	for (auto nodeIndex : scene.nodes) {
		auto node = ProcessNode(file, file.nodes[nodeIndex]);
		scenePtr.get()->AppendGameObject(node);
	}
	return scenePtr;
}

std::shared_ptr<GameObject> GLTFLoader::ProcessNode(const GLTFFile& file, const GLTFNode& node) {
	std::shared_ptr<GameObject> objPtr = std::make_shared<GameObject>();

	// Load local transform matrix
	auto transform = objPtr->GetComponent<Transform>().lock();
	transform.get()->SetLocalMatrix(glm::make_mat4(node.matrix));
	
	// Load children
	for (auto childIndex : node.children) {
		auto childNode = ProcessNode(file, file.nodes[childIndex]);
		auto childTransform = childNode->GetComponent<Transform>().lock();
		transform.get()->AddChild(childTransform);
	}

	// Load mesh if available.
	if (node.mesh != -1) {
		auto mesh = file.meshes[node.mesh];
		auto meshComponent = ProcessMesh(file, file.meshes[node.mesh]);
		objPtr->SetName(mesh.name);
	} else {
		objPtr->SetName("TODO");
	}

	return objPtr;
}

std::shared_ptr<Mesh> GLTFLoader::ProcessMesh(const GLTFFile& file, const GLTFMesh& mesh) {
	std::vector<shared_ptr<Primitive>> primitives;
	for (const auto& primitive : mesh.primitives) {

		auto vertexAttributes = primitive.attributes;
		auto posAccessor = file.accessors[vertexAttributes.position];
		ReadAccessor(file, posAccessor);

		auto normalAccessor = file.accessors[vertexAttributes.normal];
		ReadAccessor(file, normalAccessor);

		auto indicesAccessor = file.accessors[primitive.indices];
		ReadAccessor(file, indicesAccessor);

		// Build Material
		auto materialDescriptor = file.materials[primitive.material];
		std::shared_ptr<MaterialBase> material = ProcessMaterial(file, materialDescriptor);

		primitives.push_back(std::make_shared<Primitive>(vertices, indices, material));
	}
	return std::make_shared<Mesh>(primitives);
}

std::shared_ptr<MaterialBase> GLTFLoader::ProcessMaterial(const GLTFFile& file, const GLTFMaterial& material) {
	std::shared_ptr<MaterialBase> materialPtr = std::make_shared<PBRMaterial>();
	return materialPtr;
}

vector<Texture> GLTFLoader::LoadMaterialTextures(string path, TextureType::Type typeName) {
	vector<Texture> textures;
	return textures;
}

void GLTFLoader::ReadAccessor(const GLTFFile& file, const GLTFAccessor& accessor)
{
	auto bufferView = file.bufferViews[accessor.bufferView];
	auto buffer = file.buffers[bufferView.buffer];
	char* data = nullptr;
	ReadBuffer(buffer.uri, &data, bufferView.byteOffset, bufferView.byteLength);
}

void GLTFLoader::ReadBuffer(std::string path, char** data, unsigned int byteOffset, unsigned int size) {
	ifstream file("../../resources/models/" + path, ios::in | ios::binary);
	if (file.is_open()) {
		size = file.tellg();
		*data = new char[size];
		file.seekg(byteOffset);
		file.read(*data, size);
		file.close();
	}
}

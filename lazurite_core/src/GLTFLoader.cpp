#include "GLTFLoader.h"
#include "rendering/Material.h"
#include <iostream>
#include <fstream>
#include <json.hpp>
#include "glm/gtc/type_ptr.hpp"

using json = nlohmann::json;

std::shared_ptr<Scene> GLTFLoader::Load(string path)
{
	std::ifstream fileStream (path);
	json gltfJson;
	fileStream >> gltfJson;
	auto file = gltfJson.get<GLTFFile>();
	auto defaultScene = file.scenes[file.scene];
	return GLTFLoader::ProcessScene(file, defaultScene);
}

std::shared_ptr<Scene> GLTFLoader::ProcessScene(const GLTFFile& const file, const GLTFScene& const scene)
{
	std::shared_ptr<Scene> scenePtr = std::make_shared<Scene>();
	for (auto nodeIndex : scene.nodes) 
	{
		auto node = ProcessNode(file, file.nodes[nodeIndex]);
		scenePtr.get()->AppendGameObject(node);
	}
	return scenePtr;
}

std::shared_ptr<GameObject> GLTFLoader::ProcessNode(const GLTFFile& const file, const GLTFNode& const node)
{
	std::shared_ptr<GameObject> objPtr = std::make_shared<GameObject>();

	// Load local transform matrix
	auto transform = objPtr->GetComponent<Transform>().lock();
	transform.get()->SetLocalMatrix(glm::make_mat4(node.matrix));
	
	// Load children
	for (auto childIndex : node.children) 
	{
		auto childNode = ProcessNode(file, file.nodes[childIndex]);
		auto childTransform = childNode->GetComponent<Transform>().lock();
		transform.get()->AddChild(childTransform);
	}

	// Load mesh if available.
	if (node.mesh != -1) 
	{
		auto mesh = file.meshes[node.mesh];
		auto meshComponent = ProcessMesh(file, file.meshes[node.mesh]);
		objPtr->SetName(mesh.name);
	}
	else 
	{
		objPtr->SetName("TODO: Handle no mesh name");
	}

	return objPtr;
}

std::shared_ptr<Mesh> GLTFLoader::ProcessMesh(const GLTFFile& const file, const GLTFMesh& const mesh)
{
	for (auto& const primitive : mesh.primitives)
	{
		auto indicesAccessor = file.accessors[primitive.indices];
		auto materialDescriptor = file.materials[primitive.material];
		std::shared_ptr<MaterialBase> material = ProcessMaterial(file, materialDescriptor);
	}
	return std::shared_ptr<Mesh>();
}

std::shared_ptr<MaterialBase> GLTFLoader::ProcessMaterial(const GLTFFile& const file, const GLTFMaterial& const material)
{
	std::shared_ptr<MaterialBase> materialPtr = std::make_shared<PBRMaterial>();
	return materialPtr;
}

vector<Texture> GLTFLoader::LoadMaterialTextures(string path, TextureType::Type typeName)
{
	vector<Texture> textures;
	return textures;
}
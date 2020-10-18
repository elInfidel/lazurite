#include "GLTFLoader.h"
#include "rendering/Material.h"
#include "gltf.h"
#include <iostream>
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

std::shared_ptr<GameObject> GLTFLoader::Load(string path)
{
	std::ifstream fileStream (path);
	json gltfJson;
	fileStream >> gltfJson;
	auto gltf = gltfJson.get<GLTFFile>();
	return std::shared_ptr<GameObject>(GLTFLoader::ProcessNode(path));
}

GameObject* GLTFLoader::ProcessNode(string path)
{
	auto obj = new GameObject();
	auto transform = obj->GetComponent<Transform>().lock();
	obj->SetName("TODO");
	return obj;
}

std::shared_ptr<Mesh> GLTFLoader::ProcessMesh(string path)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	MaterialBase* material = new PBRMaterial();
	return std::shared_ptr<Mesh>(new Mesh(vertices, indices, material));
}

MaterialBase* GLTFLoader::LoadMaterial(string path)
{
	MaterialBase* material = new PBRMaterial();
	return material;
}

vector<Texture> GLTFLoader::LoadMaterialTextures(string path, TextureType::Type typeName)
{
	vector<Texture> textures;
	return textures;
}
#pragma once
#include <vector>
#include <string>
#include <json.hpp>

struct GLTFAsset {
	std::string generator;
	std::string version;
};

struct GLTFScene {
	std::vector<int> nodes;
};

struct GLTFNode {
	std::vector<int> children;
	std::vector<int> matrix;
	int mesh;
};

struct GLTFAttributes {
	int normal;
	int position;
};

struct GLTFPrimitive {
	int indices;
	int material;
	int mode;
	GLTFAttributes attributes;
};

struct GLTFMesh {
	std::string name;
	std::vector<GLTFPrimitive> primitives;
};

struct GLTFAccessor {
	int bufferView;
	int byteOffset;
	int componentType;
	int count;
	std::vector<float> max;
	std::vector<float> min;
	std::string type;
};

struct GLTFMaterial {
	std::string name;
	// TODO: PBR description
};

struct GLTFBufferView {
	int buffer;
	int byteOffset;
	int byteLength;
	int target;
};

struct GLTFBuffer {
	int byteLength;
	std::string uri;
};

struct GLTFFile {
	GLTFAsset asset;
	int scene;
	std::vector<GLTFScene> scenes;
	std::vector<GLTFNode> nodes;
	std::vector<GLTFMesh> meshes;
	std::vector<GLTFAccessor> accessors;
	std::vector<GLTFMaterial> materials;
	std::vector<GLTFBufferView> bufferViews;
	std::vector<GLTFBuffer> buffers;
};

void from_json(const nlohmann::json& j, GLTFMaterial& material) {
	j.at("name").get_to(material.name);
}

void from_json(const nlohmann::json& j, GLTFBufferView& bufferView) {
	j.at("buffer").get_to(bufferView.buffer);
	j.at("byteOffset").get_to(bufferView.byteOffset);
	j.at("byteLength").get_to(bufferView.byteLength);
	j.at("target").get_to(bufferView.target);
}

void from_json(const nlohmann::json& j, GLTFBuffer& buffer) {
	j.at("byteLength").get_to(buffer.byteLength);
	j.at("uri").get_to(buffer.uri);
}

void from_json(const nlohmann::json& j, GLTFAccessor& accessor) {
	j.at("bufferView").get_to(accessor.bufferView);
	j.at("byteOffset").get_to(accessor.byteOffset);
	j.at("componentType").get_to(accessor.componentType);
	j.at("count").get_to(accessor.count);
	j.at("max").get_to(accessor.max);
	j.at("min").get_to(accessor.min);
	j.at("type").get_to(accessor.type);
}

void from_json(const nlohmann::json& j, GLTFAttributes& attributes) {
	j.at("NORMAL").get_to(attributes.normal);
	j.at("POSITION").get_to(attributes.position);
}

void from_json(const nlohmann::json& j, GLTFPrimitive& primitive) {
	j.at("attributes").get_to(primitive.attributes);
	j.at("indices").get_to(primitive.indices);
	j.at("material").get_to(primitive.material);
	j.at("mode").get_to(primitive.mode);
}

void from_json(const nlohmann::json& j, GLTFMesh& mesh) {
	j.at("name").get_to(mesh.name);
	j.at("primitives").get_to(mesh.primitives);
}

void from_json(const nlohmann::json& j, GLTFNode& node) {
	// TODO: Better handle nullable fields
	try {
		j.at("children").get_to(node.children);
	}
	catch (std::exception& e) {};
	try {
		j.at("matrix").get_to(node.matrix);
	} catch (std::exception& e) {};
	try { 
		j.at("mesh").get_to(node.mesh);
	} catch(std::exception& e) {};
}

void from_json(const nlohmann::json& j, GLTFScene& scene) {
	j.at("nodes").get_to(scene.nodes);
}

void from_json(const nlohmann::json& j, GLTFAsset& asset) {
	j.at("generator").get_to(asset.generator);
	j.at("version").get_to(asset.version);
}

void from_json(const nlohmann::json& j, GLTFFile& file) {
	j.at("asset").get_to(file.asset);
	j.at("scene").get_to(file.scene);
	j.at("scenes").get_to(file.scenes);
	j.at("nodes").get_to(file.nodes);
	j.at("meshes").get_to(file.meshes);
	j.at("accessors").get_to(file.accessors);
	j.at("materials").get_to(file.materials);
	j.at("bufferViews").get_to(file.bufferViews);
	j.at("buffers").get_to(file.buffers);
}
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
	float matrix[16];
	int mesh;
};

struct GLTFAttributes {
	int normal;
	int position;
};

struct GLTFPrimitive {
	unsigned int indices;
	unsigned int material;

	/*
	* Specifies OpenGL primitive render mode.
	* 0 POINTS
	* 1 LINES
	* 2 LINE_LOOP
	* 3 LINE_STRIP
	* 4 TRIANGLES
	* 5 TRIANGLE_STRIP
	* 6 TRIANGLE_FAN
	*/
	unsigned int mode;

	GLTFAttributes attributes;
};

struct GLTFMesh {
	std::string name;
	std::vector<GLTFPrimitive> primitives;
};

struct GLTFAccessor {
	unsigned int bufferView;
	unsigned int byteOffset;
	unsigned int componentType;
	unsigned int count;
	std::vector<float> max;
	std::vector<float> min;
	std::string type;
};

struct GLTFMaterial {
	std::string name;
	// TODO: PBR description
};

struct GLTFBufferView {
	unsigned int buffer;
	unsigned int byteOffset;
	unsigned int byteLength;
	unsigned int target;
};

struct GLTFBuffer {
	unsigned int byteLength;
	std::string uri;
};

struct GLTFFile {
	GLTFAsset asset;
	unsigned int scene;
	std::vector<GLTFScene> scenes;
	std::vector<GLTFNode> nodes;
	std::vector<GLTFMesh> meshes;
	std::vector<GLTFAccessor> accessors;
	std::vector<GLTFMaterial> materials;
	std::vector<GLTFBufferView> bufferViews;
	std::vector<GLTFBuffer> buffers;
};

void from_json(const nlohmann::json& j, GLTFMaterial& material);
void from_json(const nlohmann::json& j, GLTFBufferView& bufferView);
void from_json(const nlohmann::json& j, GLTFBuffer& buffer);
void from_json(const nlohmann::json& j, GLTFAccessor& accessor);
void from_json(const nlohmann::json& j, GLTFAttributes& attributes);
void from_json(const nlohmann::json& j, GLTFPrimitive& primitive);
void from_json(const nlohmann::json& j, GLTFMesh& mesh);
void from_json(const nlohmann::json& j, GLTFNode& node);
void from_json(const nlohmann::json& j, GLTFScene& scene);
void from_json(const nlohmann::json& j, GLTFAsset& asset);
void from_json(const nlohmann::json& j, GLTFFile& file);
// ---------------------------------------------------------------------------
// Transform.h
// An object for storing the transformation of an object.
//
// Original author: <Liam Parker>
// Date created: 21/12/2014
// ---------------------------------------------------------------------------
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "GLM/vec3.hpp"
#include "GLM/mat4x4.hpp"

using glm::mat4;
using glm::vec3;

namespace lazurite
{
	class Transform
	{
	public:
		// Constructs a transform with identity value
		Transform();
		~Transform();

		// Translates the transform by the vector
		void Translate(vec3& vector);
		void Translate(float x, float y, float z);
		// Rotates the transform by the vector
		void Rotate(vec3& vector);
		void Rotate(float x, float y, float z);
		// Scales the transform by the vector
		void Scale(vec3& vector);
		void Scale(float x, float y, float z);
		// Returns the transformation matrix associated with this transform
		mat4 GetTransformation();
		// Returns the inverse of the camera matrix
		mat4 Inverse();
		// Returns whether or not the transform is dirty
		inline bool GetDirty() { return isDirty; }

	private:
		// Returns true if the transformation matrix needs to be rebuilt
		bool isDirty;

		// Transformation data
		mat4 transformation;
		vec3 translation;
		vec3 rotation;
		vec3 scale;

		void GenerateMatrix();

	};
}

#endif // _TRANSFORM_H_
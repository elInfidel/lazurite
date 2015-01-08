// ---------------------------------------------------------------------------
// Transform.h
// An object for storing the transformation of an object.
//
// Original author: <Liam Parker>
// Date created: 21/12/2014
// ---------------------------------------------------------------------------
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "Math/Vector3.h"
#include "Math/Matrix4x4.h"

using namespace lazmath;

namespace lazurite
{
	class Transform
	{
	public:
		// Constructs a transform with identity value
		Transform();
		~Transform();

		// Translates the transform by the vector
		void Translate(Vector3& vector);
		void Translate(float x, float y, float z);
		// Rotates the transform by the vector
		void Rotate(Vector3& vector);
		void Rotate(float x, float y, float z);
		// Scales the transform by the vector
		void Scale(Vector3& vector);
		void Scale(float x, float y, float z);
		// Returns the transformation matrix associated with this transform
		Matrix4x4 GetTransformation();
		// Returns whether or not the transform is dirty
		inline bool GetDirty() { return isDirty; }

	private:
		// Returns true if the transformation matrix needs to be rebuilt
		bool isDirty;

		// Transformation data
		Matrix4x4 transformation;
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

		void GenerateMatrix();

	};
}

#endif // _TRANSFORM_H_
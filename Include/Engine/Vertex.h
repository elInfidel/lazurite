// ---------------------------------------------------------------------------
// Vertex.h
// A header file containing structs representing a wide range of vertex types.
//
// Original author: <Liam Parker>
// Date created: 21/12/2014
// ---------------------------------------------------------------------------
#ifndef _VERTEX_H_
#define _VERTEX_H_

namespace lazurite
{
	struct VertPos
	{
		// X Y Z W
		float positions[4];
	};

	struct VertPosColor
	{
		// X Y Z W
		float positions[4];
		// R G B A
		float colours[4];
	};

	struct VertPosColorUV
	{
		// X Y Z W
		float positions[4];
		// R G B A
		float colours[4];
		// U V
		float uv[2];
	};
}

#endif // _VERTEX_H_

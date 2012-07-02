#ifndef PARABOLA_VERTEXARRAYS_H
#define PARABOLA_VERTEXARRAYS_H

#include "Platform.h"
#include "Vectors.h"
#include <vector>
#include "Color.h"

PARABOLA_NAMESPACE_BEGIN

enum PrimitiveType{
	Triangles = 0,
	TriangleFan
};

class PARABOLA_API Vertex{
public:
	Vec2f position;
	Color color;	
	Vec2f texCoords;
};

class PARABOLA_API VertexArray{
public:
	/// Constructs an empty vertex array with default primitive type - Quads
	VertexArray();

	VertexArray(PrimitiveType primitiveType, unsigned int vertexCount);

	Vertex& operator[](unsigned int index);

	std::vector<Vertex> myVertices;

	PrimitiveType geometryType;
};

PARABOLA_NAMESPACE_END
#endif
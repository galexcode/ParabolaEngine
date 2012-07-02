#include <ParabolaCore/VertexArray.h>

PARABOLA_NAMESPACE_BEGIN

/// Constructs an empty vertex array with default primitive type - Quads
VertexArray::VertexArray(){

};

VertexArray::VertexArray(PrimitiveType primitiveType, unsigned int vertexCount){
	geometryType = primitiveType;
	myVertices.resize(vertexCount);
};

Vertex& VertexArray::operator[](unsigned int index){
	return myVertices[index];
};

PARABOLA_NAMESPACE_END
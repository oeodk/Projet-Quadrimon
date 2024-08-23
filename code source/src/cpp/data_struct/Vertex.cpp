#include "data_struct/Vertex.h"
#include "data_struct/SmallVertex.h"

Vertex::Vertex(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty)
	:Vertex(bdm::Vector3f(px,py,pz), bdm::Vector3f(nx, ny, nz), bdm::Vector2f(tx, ty))
{
	
}

Vertex::Vertex(bdm::Vector3f p, bdm::Vector3f n, bdm::Vector2f t)
	: position(p), normal(n), texture_coords(t)
{
}

void Vertex::operator=(const SmallVertex& vert)
{
	position = vert.position;
	normal = vert.normal;
}

Vertex operator*(const QMatrix4x4& transformation_matrix, const Vertex& vert)
{

	return Vertex(transformation_matrix * vert.position, transformation_matrix * vert.normal, vert.texture_coords);
}

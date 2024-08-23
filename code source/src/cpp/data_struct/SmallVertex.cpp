#include "data_struct/SmallVertex.h"


SmallVertex::SmallVertex(float px, float py, float pz, float nx, float ny, float nz)
	:SmallVertex(bdm::Vector3f(px, py, pz), bdm::Vector3f(nx, ny, nz))
{

}

SmallVertex::SmallVertex(bdm::Vector3f p, bdm::Vector3f n)
	: position(p), normal(n)
{
}

void SmallVertex::operator=(const Vertex& vert)
{
	position = vert.position;
	normal = vert.normal;
}

void SmallVertex::operator*=(float value)
{
	position *= value;
	normal *= value;
}

SmallVertex operator*(const QMatrix4x4& transformation_matrix, const SmallVertex& vert)
{

	return SmallVertex(transformation_matrix * vert.position, transformation_matrix * vert.normal);
}

SmallVertex operator*(const SmallVertex& vert, float value)
{
	return SmallVertex(vert.position * value, vert.normal * value);
}

SmallVertex operator+(const SmallVertex& v1, const SmallVertex& v2)
{
	return SmallVertex(v1.position + v2.position, v1.normal + v2.normal);
}

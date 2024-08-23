#pragma once
#include "data_struct/Vector3f.h"
#include "data_struct/Vector2f.h"

/*
Ce struct contient les informations d'un point

- Champs :
	position : la position du point
	normal : la normale de ce point
	texture_coords : le mappage de la texture

Struct réalisée par GONON Lucas
*/

struct SmallVertex;

struct Vertex
{
	bdm::Vector3f position;
	bdm::Vector3f normal;
	bdm::Vector2f texture_coords;

	Vertex(float px = 0, float py = 0, float pz = 0, float nx = 0, float ny = 0, float nz = 0, float tx = 0, float ty = 0);
	Vertex(bdm::Vector3f p, bdm::Vector3f n, bdm::Vector2f t);

	/*
	R : Permet d'inverser les normales
	*/
	void invertNormals() { normal.invert(); }

	/*
	R : Opérateur = permettant d'assigner un SmallVertex au Vertex
	E : vert : le SmallVertex
	*/
	void operator=(const SmallVertex& vert);

};
/*
R : Opérateur permettant d'appliqué une transformation 3D au Vertex
E : transformation_matrix : la matrice de transformation
	vert : le Vertex
S : un nouveau Vertex contenant le résultat 
*/
Vertex operator*(const QMatrix4x4& transformation_matrix, const Vertex& vert);
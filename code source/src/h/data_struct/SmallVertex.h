#pragma once
#include "data_struct/Vector3f.h"
#include "data_struct/Vertex.h"

/*
Ce struct contient une version alléger d'un Vertex

- Champs :
	position : la position du point
	normal : la normale de ce point

Struct réalisée par GONON Lucas
*/

struct SmallVertex
{
	bdm::Vector3f position;
	bdm::Vector3f normal;

	SmallVertex(float px = 0, float py = 0, float pz = 0, float nx = 0, float ny = 0, float nz = 0);
	SmallVertex(bdm::Vector3f p, bdm::Vector3f n);
	SmallVertex(const Vertex& v) : SmallVertex(v.position, v.normal) {}

	/*
	R : Permet d'inverser les normales
	*/
	void invertNormals() { normal.invert(); }

	/*
	R : Opérateur = permettant d'assigner un Vertex au SmallVertex
	E : vert : le Vertex
	*/
	void operator=(const Vertex& vert);

	/*
	R : Opérateur *= permettant de multiplier le SmallVertex par un float
	E : value : la valeur
	*/
	void operator*=(float value);
};
/*
R : Opérateur permettant d'appliqué une transformation 3D au SmallVertex
E : transformation_matrix : la matrice de transformation
	vert : le SmallVertex
S : un nouveau SmallVertex contenant le résultat
*/
SmallVertex operator*(const QMatrix4x4& transformation_matrix, const SmallVertex& vert);

/*
R : Opérateur * permettant de multiplier le SmallVertex par un float
E : vert : le SmallVertex
	value : la valeur
S : un nouveau SmallVertex contenant le résultat
*/
SmallVertex operator*(const SmallVertex& vert, float value);

/*
R : Opérateur + permettant d'additionner deux SmallVertex 
E : v1 : le 1er SmallVertex
	v2 : le 2nd SmallVertex
S : un nouveau SmallVertex contenant le résultat
*/
SmallVertex operator+(const SmallVertex& v1, const SmallVertex& v2);



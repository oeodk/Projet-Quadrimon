#pragma once
#define _USE_MATH_DEFINES
#include<cmath>
#include <vector>
#include "data_struct/Vertex.h"

/*
Ce fichier contient les fonctions permettant de générer différents polygons

Toutes ces fonctions prenne en entrée vertices et indices par référence, ces variables sont aussi des sortie
	vertices : possède tous les points des polygons généré
	indices : possède l'ordre dans lequel utiliser ces points
	
Fonctions réalisées par GONON Lucas
*/

/*
R : Créer un rectangle
E : width : la largeur du rectangle
	height : la hauteur du rectangle
*/
void createRectangle(float width, float height, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

/*
R : Créer un cube
E : width : la largeur du rectangle
	height : la hauteur du rectangle
	depth : la profondeur du rectangle
*/
void createCube(float width, float height, float depth, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

/*
R : Créer un tore
E : global_radius : le grand rayon du tore
	section_radius : le petit rayon du tore
	point : le nombre de points utilisé pour les cercles
*/
void createTorus(float global_radius, float section_radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

/*
R : Créer un cercle
E : radius : le rayon du cercle
	point : le nombre de points du cercle
*/
void createCircle(float radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

/*
R : Créer un cylindre
E : height : la hauteur du cylindre
	radius : le rayon du cylindre
	point : le nombre de points des disques
*/
void createCylinder(float height, float radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float proportion = 1.f);

/*
R : Créer un cone
E : cylindre : la hauteur du cone
	radius : le rayon du cone
	point : le nombre de points du disques
*/
void createCone(float height, float radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

/*
R : Créer une sphère
E : radius : le rayon de la sphère
	point : le nombre de points d'une section de la sphère
	proportion : le pourcentage de la sphère (0.5 => une demi sphère)
*/
void createSphere(float radius, int segments, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float proportion = 1);

/*
R : Créer une sphère utilisée pour les terrains
E : radius : le rayon de la sphère
	point : le nombre de points d'une section de la sphère
	proportion : le pourcentage de la sphère (0.5 => une demi sphère)
*/
void createTerrainSphere(float radius, int segments, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float proportion = 1);

/*
R : Créer une pyramide
E : cylindre : la hauteur de la pyramide
	radius : la moitié de la largeur de la base
	point : le nombre de points de la base
*/
void createPyramid(float height, float base_half_size, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
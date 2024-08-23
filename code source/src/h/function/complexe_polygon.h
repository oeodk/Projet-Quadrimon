#pragma once
#define _USE_MATH_DEFINES
#include<cmath>
#include <vector>
#include "data_struct/Vertex.h"

/*
Ce fichier contient les fonctions permettant de g�n�rer diff�rents polygons

Toutes ces fonctions prenne en entr�e vertices et indices par r�f�rence, ces variables sont aussi des sortie
	vertices : poss�de tous les points des polygons g�n�r�
	indices : poss�de l'ordre dans lequel utiliser ces points
	
Fonctions r�alis�es par GONON Lucas
*/

/*
R : Cr�er un rectangle
E : width : la largeur du rectangle
	height : la hauteur du rectangle
*/
void createRectangle(float width, float height, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

/*
R : Cr�er un cube
E : width : la largeur du rectangle
	height : la hauteur du rectangle
	depth : la profondeur du rectangle
*/
void createCube(float width, float height, float depth, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

/*
R : Cr�er un tore
E : global_radius : le grand rayon du tore
	section_radius : le petit rayon du tore
	point : le nombre de points utilis� pour les cercles
*/
void createTorus(float global_radius, float section_radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

/*
R : Cr�er un cercle
E : radius : le rayon du cercle
	point : le nombre de points du cercle
*/
void createCircle(float radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

/*
R : Cr�er un cylindre
E : height : la hauteur du cylindre
	radius : le rayon du cylindre
	point : le nombre de points des disques
*/
void createCylinder(float height, float radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float proportion = 1.f);

/*
R : Cr�er un cone
E : cylindre : la hauteur du cone
	radius : le rayon du cone
	point : le nombre de points du disques
*/
void createCone(float height, float radius, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

/*
R : Cr�er une sph�re
E : radius : le rayon de la sph�re
	point : le nombre de points d'une section de la sph�re
	proportion : le pourcentage de la sph�re (0.5 => une demi sph�re)
*/
void createSphere(float radius, int segments, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float proportion = 1);

/*
R : Cr�er une sph�re utilis�e pour les terrains
E : radius : le rayon de la sph�re
	point : le nombre de points d'une section de la sph�re
	proportion : le pourcentage de la sph�re (0.5 => une demi sph�re)
*/
void createTerrainSphere(float radius, int segments, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float proportion = 1);

/*
R : Cr�er une pyramide
E : cylindre : la hauteur de la pyramide
	radius : la moiti� de la largeur de la base
	point : le nombre de points de la base
*/
void createPyramid(float height, float base_half_size, int point, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
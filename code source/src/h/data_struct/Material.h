#pragma once
#include "data_struct/Vector3f.h"

/*
Ce struct contient les informations d'un mat�riaux

- Champs :
	ambient : la valeur de lumi�re ambiante
	diffuse : la valeur de lumi�re diffuse
	specular : la valeur de lumi�re sp�culaire
	shininess : la valeur de brillance

Struct r�alis�e par GONON Lucas
*/

struct Material
{
	bdm::Vector3f ambient;
	bdm::Vector3f diffuse;
	bdm::Vector3f specular;
	float shininess;
	Material(bdm::Vector3f a = bdm::Vector3f(0.2, 0.2, 0.2), bdm::Vector3f d = bdm::Vector3f(1, 1, 1), bdm::Vector3f s = bdm::Vector3f(0, 0, 0), float shi = 32);
};
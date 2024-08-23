#pragma once
#include "data_struct/Vector3f.h"

/*
Ce struct contient les informations d'un matériaux

- Champs :
	ambient : la valeur de lumière ambiante
	diffuse : la valeur de lumière diffuse
	specular : la valeur de lumière spéculaire
	shininess : la valeur de brillance

Struct réalisée par GONON Lucas
*/

struct Material
{
	bdm::Vector3f ambient;
	bdm::Vector3f diffuse;
	bdm::Vector3f specular;
	float shininess;
	Material(bdm::Vector3f a = bdm::Vector3f(0.2, 0.2, 0.2), bdm::Vector3f d = bdm::Vector3f(1, 1, 1), bdm::Vector3f s = bdm::Vector3f(0, 0, 0), float shi = 32);
};
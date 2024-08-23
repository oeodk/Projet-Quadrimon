#include "data_struct/Material.h"

Material::Material(bdm::Vector3f a, bdm::Vector3f d, bdm::Vector3f s, float shi)
	:ambient(a), diffuse(d), specular(s), shininess(shi)
{
}

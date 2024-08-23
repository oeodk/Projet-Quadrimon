#pragma once
#include <map>

/*
répertorie les éléments existants, ainsi que l'élément contre lequel ils sont efficaces
*/

namespace E_QuadrimonType
{
	enum e_QuadrimonType
	{
		WATER,
		FIRE,
		GRASS,
		E_END
	};
	inline bool isSuperEffective(E_QuadrimonType::e_QuadrimonType attacker, E_QuadrimonType::e_QuadrimonType target)
	{ return (target - attacker == -2 || target - attacker == 1);	}

	const std::map<E_QuadrimonType::e_QuadrimonType, std::string> QUADRIMON_TYPE_STRING_MAP{{ E_QuadrimonType::WATER, "Eau"},
																							{ E_QuadrimonType::FIRE , "Feu" },
																							{ E_QuadrimonType::GRASS, "Plante" }};
}
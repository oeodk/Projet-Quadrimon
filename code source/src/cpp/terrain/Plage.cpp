#include "terrain/Plage.h"

Plage::Plage(E_Player::e_Player player_side)
	:Terrain(player_side, true)
{
	turn_left_ = -1;
	total_turn_ = -1;
	name_ = E_TerrainName::PLAGE;
	terrains_polygons_[player_side_][0]->loadTexture("./assets/textures/terrain/beach.png");
	terrains_polygons_[player_side_][0]->color_.set(1, 1, 1);
	terrains_polygons_[player_side_][1]->loadTexture("./assets/textures/terrain/beach_floor.png");
	terrains_polygons_[player_side_][1]->color_.set(1, 1, 1);
}

void Plage::applyEffect(Quadrimon* quadrimon)
{
	if (quadrimon->getBaseType() == E_QuadrimonType::WATER)
	{
		quadrimon->setAdditionalTypeAdvantage({ 0,0.5,0 });
	}
	else
	{
		quadrimon->setType(E_QuadrimonType::WATER);
	}
}

void Plage::clearTerrainEffect(Quadrimon* quadrimon)
{
	quadrimon->resetType();
	quadrimon->setAdditionalTypeAdvantage({ 0,0,0 });
}

std::string Plage::getDisplayEffectText(const Quadrimon* quadrimon, int player_index)
{
	if (quadrimon->getType() != E_QuadrimonType::WATER)
	{
		return getTerrainActivationText(player_index) + " le " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(quadrimon->getName()) +
			" du joueur " + std::to_string(player_index + 1) + " prend le type eau ";
	}
	else
	{
		if (quadrimon->getBaseType() == E_QuadrimonType::WATER && quadrimon->getAdditionalTypeAdvantage().y == 0)
		{
			return getTerrainActivationText(player_index) + " l'avantage de type du " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(quadrimon->getName()) +
				" du joueur " + std::to_string(player_index + 1) + " passe a 2,5 ";
		}
	}
	return std::string();
}

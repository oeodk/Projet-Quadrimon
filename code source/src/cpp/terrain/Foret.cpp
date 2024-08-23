#include "terrain/Foret.h"

Foret::Foret(E_Player::e_Player player_side)
	:Terrain(player_side, true)
{
	turn_left_ = -1;
	total_turn_ = -1;
	name_ = E_TerrainName::FORET;
	terrains_polygons_[player_side_][0]->loadTexture("./assets/textures/terrain/forest.png");
	terrains_polygons_[player_side_][0]->color_.set(1, 1, 1);
	terrains_polygons_[player_side_][1]->loadTexture("./assets/textures/terrain/forest_floor.png");
	terrains_polygons_[player_side_][1]->color_.set(1, 1, 1);
}

void Foret::applyEffect(Quadrimon* quadrimon)
{
	if (quadrimon->getBaseType() == E_QuadrimonType::GRASS)
	{
		quadrimon->editLife(50);
	}
	else
	{
		quadrimon->setType(E_QuadrimonType::GRASS);
	}
}

std::string Foret::getDisplayEffectText(const Quadrimon* quadrimon, int player_index)
{
	if (quadrimon->getBaseType() == E_QuadrimonType::GRASS)
	{
		return getTerrainActivationText(player_index) + " le " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(quadrimon->getName()) +
			" du joueur " + std::to_string(player_index + 1) + " gagne 50 PV ";
	}
	else
	{
		if (quadrimon->getType() != E_QuadrimonType::GRASS)
		{
			return getTerrainActivationText(player_index) + " le " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(quadrimon->getName()) +
				" du joueur " + std::to_string(player_index + 1) + " prend le type plante ";
		}
	}
	return std::string();
}


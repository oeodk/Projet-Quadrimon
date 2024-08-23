#include "terrain/Volcan.h"

Volcan::Volcan(E_Player::e_Player player_side)
	: Terrain(player_side, true)
{
	turn_left_ = -1;
	total_turn_ = -1;
	name_ = E_TerrainName::VOLCAN;

	terrains_polygons_[player_side_][0]->loadTexture("./assets/textures/terrain/volcano.png");
	terrains_polygons_[player_side_][0]->color_.set(1, 1, 1);
	terrains_polygons_[player_side_][1]->loadTexture("./assets/textures/terrain/volcano_floor.png");
	terrains_polygons_[player_side_][1]->color_.set(1, 1, 1);
}

void Volcan::applyEffect(Quadrimon* quadrimon)
{
	if (quadrimon->getBaseType() == E_QuadrimonType::FIRE)
	{
		quadrimon->editDamage(100);
	}
	else
	{
		quadrimon->setType(E_QuadrimonType::FIRE);
	}

}

std::string Volcan::getDisplayEffectText(const Quadrimon* quadrimon, int player_index)
{
	if (quadrimon->getBaseType() == E_QuadrimonType::FIRE)
	{
		return getTerrainActivationText(player_index) + " le " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(quadrimon->getName()) +
			" du joueur " + std::to_string(player_index + 1) + " gagne 100 d'attaque ";
	}
	else
	{
		if (quadrimon->getType() != E_QuadrimonType::FIRE)
		{
			return getTerrainActivationText(player_index) + " le " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(quadrimon->getName()) +
				" du joueur " + std::to_string(player_index + 1) + " prend le type feu ";
		}
	}
	return std::string();
}

#include "terrain/Marai.h"

Marai::Marai(E_Player::e_Player player_side)
	:Terrain(player_side)
{
	turn_left_ = 5;
	total_turn_ = 5;
	name_ = E_TerrainName::MARAI;
	terrains_polygons_[player_side_][0]->loadTexture("./assets/textures/terrain/swamp.png");
	terrains_polygons_[player_side_][0]->color_.set(1, 1, 1);
	terrains_polygons_[player_side_][1]->loadTexture("./assets/textures/terrain/swamp_floor.png");
	terrains_polygons_[player_side_][1]->color_.set(1, 1, 1);
}

void Marai::applyEffect(Quadrimon* quadrimon)
{
	quadrimon->editLife(-50);
}
#include "terrain/Grotte.h"

Grotte::Grotte(E_Player::e_Player player_side)
	:Terrain(player_side)
{
	turn_left_ = 2;
	total_turn_ = 2;
	name_ = E_TerrainName::GROTTE;
	terrains_polygons_[player_side_][0]->loadTexture("./assets/textures/terrain/cave.png");
	terrains_polygons_[player_side_][0]->color_.set(1, 1, 1);
	terrains_polygons_[player_side_][1]->loadTexture("./assets/textures/terrain/cave_floor.png");
	terrains_polygons_[player_side_][1]->color_.set(1, 1, 1);
}


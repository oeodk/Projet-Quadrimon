#include "terrain/EmptyTerrain.h"

EmptyTerrain::EmptyTerrain(E_Player::e_Player player_side)
	: Terrain(player_side, true)
{
	turn_left_ = -1;
	total_turn_ = -1;
	name_ = E_TerrainName::E_END;
	terrains_polygons_[player_side_][0]->loadTexture("./assets/textures/terrain/empty_terrain_wall.png");
	terrains_polygons_[player_side_][0]->color_.set(1, 1, 1);
	terrains_polygons_[player_side_][1]->loadTexture("./assets/textures/terrain/empty_terrain_floor.png");
	terrains_polygons_[player_side_][1]->color_.set(1, 1, 1);
}
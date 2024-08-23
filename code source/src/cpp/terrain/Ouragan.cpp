#include "terrain/Ouragan.h"

Ouragan::Ouragan(E_Player::e_Player player_side)
	:Terrain(player_side)
{
	turn_left_ = 3;
	total_turn_ = 3;
	name_ = E_TerrainName::OURAGAN;
	terrains_polygons_[player_side_][0]->loadTexture("./assets/textures/terrain/tornado.png");
	terrains_polygons_[player_side_][0]->color_.set(1, 1, 1);
	terrains_polygons_[player_side_][1]->loadTexture("./assets/textures/terrain/tornado_floor.png");
	terrains_polygons_[player_side_][1]->color_.set(1, 1, 1);
}

void Ouragan::applyEffect(Quadrimon* quadrimon)
{
	quadrimon->editLife(100);
}
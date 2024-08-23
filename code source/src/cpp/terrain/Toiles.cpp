#include "terrain/Toiles.h"

Toiles::Toiles(E_Player::e_Player player_side)
	:Terrain(player_side)
{
	turn_left_ = 3;
	total_turn_ = 3;
	name_ = E_TerrainName::TOILE_ARAIGNEE;
	terrains_polygons_[player_side_][0]->loadTexture("./assets/textures/terrain/spider.png");
	terrains_polygons_[player_side_][0]->color_.set(1, 1, 1);
	terrains_polygons_[player_side_][1]->loadTexture("./assets/textures/terrain/spider_floor.png");
	terrains_polygons_[player_side_][1]->color_.set(1, 1, 1);
}

void Toiles::applyEffect(Quadrimon* quadrimon)
{
	quadrimon->editDamage(-100);
}	
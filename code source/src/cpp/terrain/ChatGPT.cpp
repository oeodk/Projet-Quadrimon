#include "terrain/ChatGPT.h"

ChatGPT::ChatGPT(E_Player::e_Player player_side)
	: Terrain(player_side)
{
	turn_left_ = 2;
	total_turn_ = 2;
	name_ = E_TerrainName::CHAT_GPT;
	terrains_polygons_[player_side_][0]->loadTexture("./assets/textures/terrain/gpt.png");
	terrains_polygons_[player_side_][0]->color_.set(1, 1, 1);
	terrains_polygons_[player_side_][1]->loadTexture("./assets/textures/terrain/gpt_floor.png");
	terrains_polygons_[player_side_][1]->color_.set(1, 1, 1);
}

void ChatGPT::clearTerrainEffect(Quadrimon* quadrimon)
{
	quadrimon->resetType();
	quadrimon->setAdditionalTypeAdvantage(0);
}

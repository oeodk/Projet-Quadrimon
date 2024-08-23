#include "terrain/Terrain.h"

Terrain::Terrain(E_Player::e_Player player_side, bool is_infinite)
	: player_side_(player_side), is_infinite_(is_infinite)
{
	total_turn_ = -1;
	if (terrains_polygons_[player_side_].size() == 0)
	{
		terrains_polygons_[player_side_].push_back(new OpenGlPolygon(&player_side_models_[player_side_]));
		createTerrainSphere(25, 24, terrains_polygons_[player_side_].back()->vertices_, terrains_polygons_[player_side_].back()->indices_, 0.5);

		for (auto& vertex : terrains_polygons_[player_side_].back()->vertices_)
		{
			vertex.invertNormals();
		}
		terrains_polygons_[player_side_].back()->initializeBuffers();

		terrains_polygons_[player_side_].push_back(new OpenGlPolygon(&player_side_models_[player_side_]));
		createRectangle(50, 25, terrains_polygons_[player_side_].back()->vertices_, terrains_polygons_[player_side_].back()->indices_);
		terrains_polygons_[player_side_].back()->base_model_.translate(0, 12.5, 0);
		terrains_polygons_[player_side_].back()->initializeBuffers();

		if (player_side_ == E_Player::PLAYER_1)
		{
			player_side_models_[player_side_].rotate(180, 0, 0, 1);
			terrains_polygons_[player_side_][0]->color_.set(0, 0, 1);
			terrains_polygons_[player_side_][1]->color_.set(0, 1, 1);
		}
		else
		{
			terrains_polygons_[player_side_][0]->color_.set(1, 0, 0);
			terrains_polygons_[player_side_][1]->color_.set(1, 1, 0);
		}
	}
}

Terrain::~Terrain()
{
	for (int i = 0; i < 2; i++)
	{
		terrains_polygons_[player_side_][i]->deleteTexture();
	}
}

std::string Terrain::getTurnLeftText()
{
	if (is_infinite_)
	{
		return std::string(" Infini ");
	}
	return std::string(std::to_string(turn_left_) + " / " + std::to_string(total_turn_));
}

void Terrain::update()
{
	if (!is_infinite_)
	{
		turn_left_--;
	}
}

bool Terrain::willDisappear() const
{
	if (turn_left_ == 0 && !is_infinite_) // tours a 0 et terrain qui n'a pas d'effet infini
	{
		return true;
	}
	return false;
}


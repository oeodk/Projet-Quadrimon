#include "utility/SceneOverlay.h"

SceneOverlay::SceneOverlay()
{
	players_quadrimon_cards_ = { E_QuadrimonName::E_END, E_QuadrimonName::E_END };
	players_terrain_cards_ = { E_TerrainName::E_END, E_TerrainName::E_END };
	refresh_scene_polygons_ = true;
}

void SceneOverlay::update(const std::array<E_QuadrimonName::e_QuadrimonName, 2>& players_quadrimon_card, const std::array<E_TerrainName::e_TerrainName, 2>& players_terrain_card)
{
	for (int i = 0; i < 2; i++)
	{
		if (players_quadrimon_card[i] != E_QuadrimonName::E_END && players_quadrimon_card[i] != players_quadrimon_cards_[i])
		{
			players_quadrimon_cards_[i] = players_quadrimon_card[i];
			card_displays_[i].setImage("./assets/cards/quadrimon/" + E_QuadrimonName::QUADRIMON_SHORT_NAME_STRING_MAP.at(players_quadrimon_cards_[i]) + ".png");
			refresh_scene_polygons_ = true;
			if (card_displays_[2 + i].getDisplay() && (card_displays_[2 + i].getState() == E_OverlayCardState::APPEARING || card_displays_[2 + i].getState() == E_OverlayCardState::WAITING))
			{
				card_displays_[2 + i].slideSide();
			}
		}
		players_quadrimon_cards_[i] = players_quadrimon_card[i];
		if (players_terrain_card[i] != E_TerrainName::E_END && players_terrain_card[i] != players_terrain_cards_[i])
		{
			players_terrain_cards_[i] = players_terrain_card[i];
			card_displays_[2 + i].setImage("./assets/cards/terrain/" + E_TerrainName::TERRAIN_SHORT_NAME_STRING_MAP.at(players_terrain_cards_[i]) + ".png");
			refresh_scene_polygons_ = true;
			if (card_displays_[i].getDisplay() && (card_displays_[i].getState() == E_OverlayCardState::APPEARING || card_displays_[i].getState() == E_OverlayCardState::WAITING))
			{
				card_displays_[i].slideSide();
			}
		}
		players_terrain_cards_[i] = players_terrain_card[i];
	}
	for (int i = 0; i < 4; i++)
	{
		card_displays_[i].update();
		if (card_displays_[i].getState() == E_OverlayCardState::PLAYING)
		{
			int ind = i > 1 ? i - 2 : i + 2;
			if (card_displays_[ind].getDisplay())
			{
				if(card_displays_[ind].getState() == E_OverlayCardState::WAITING)
				{
					card_displays_[ind].slideCenter();
				}
			}
		}
		if (card_displays_[i].getRefreshDisplay())
		{
			card_displays_[i].resetRefreshDisplay();
			refresh_scene_polygons_ = true;
		}
	}
	if (refresh_scene_polygons_)
	{
		scene_overlay_polygons_->clear();
		for (int i = 0; i < 4; i++)
		{
			if (card_displays_[i].getDisplay())
			{
				scene_overlay_polygons_->push_back(card_displays_[i].getPolygon());
			}
		}
		refresh_scene_polygons_ = false;
	}
}

void SceneOverlay::init()
{
	for (int i = 0; i < 4; i++)
	{
		int sign = -1;
		if (i % 2)
		{
			sign = 1;
		}
		card_displays_[i].init(&players_model_, sign);
	}
}

#pragma once
#include <vector>
#include "data_struct/OpenGlPolygon.h"
#include "enum/E_QuadrimonName.h"
#include "enum/E_TerrainName.h"
#include "function/complexe_polygon.h"
#include "enum/E_Player.h"
#include "enum/E_OverlayCardState.h"
#include "utility/CardDisplay.h"

/*
Cette classe de g�rer l'affichage et la gestion des cartes affich� par dessus la sc�ne

- Champs :
	scene_overlay_polygons_ : polygon de l'overlay de la sc�ne
	players_model_ : mod�le utilis� pour un OpenGlPolygon
	players_quadrimon_cards_ : cartes quadrimons scann�es par les joueurs
	players_terrain_cards_ : cartes terrains scann�es par les joueurs
	card_displays_ : Cartes affich�es
	refresh_scene_polygons_ : bool�en permettant si de nouveau �l�ment sont apparues � l'�cran

Classe r�alis�e par GONON Lucas
*/

class SceneOverlay
{
private : 
	std::vector<OpenGlPolygon*>* scene_overlay_polygons_;
	const QMatrix4x4 players_model_;
	std::array<E_QuadrimonName::e_QuadrimonName, 2> players_quadrimon_cards_;
	std::array<E_TerrainName::e_TerrainName, 2> players_terrain_cards_;
	std::array<CardDisplay, 4> card_displays_;
	
	bool refresh_scene_polygons_;
public :
	SceneOverlay();
	/*
	R : Initialise le pointeur vers les polygon correspondant de la sc�ne
	*/
	void initSceneOverlayPolygon(std::vector<OpenGlPolygon*>* scene_overlay_polygons) { scene_overlay_polygons_ = scene_overlay_polygons; }
	
	/*
	R : r�cup�re les cartes scann�es par les joueurs et met � jour les cartes affich�es
	E : les cartes scann�es
	*/
	void update(const std::array<E_QuadrimonName::e_QuadrimonName,2>& players_quadrimon_card, const std::array<E_TerrainName::e_TerrainName, 2>& players_terrain_card);
	void triggerQuadrimonCard(E_Player::e_Player player) { card_displays_[static_cast<int>(player)].trigger(); }
	void triggerTerrainCard(E_Player::e_Player player) { card_displays_[2 + static_cast<int>(player)].trigger(); }
	void discardQuadrimonCard(E_Player::e_Player player) { card_displays_[static_cast<int>(player)].discard(); }
	void init();
};


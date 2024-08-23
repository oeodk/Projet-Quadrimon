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
Cette classe de gérer l'affichage et la gestion des cartes affiché par dessus la scène

- Champs :
	scene_overlay_polygons_ : polygon de l'overlay de la scène
	players_model_ : modèle utilisé pour un OpenGlPolygon
	players_quadrimon_cards_ : cartes quadrimons scannées par les joueurs
	players_terrain_cards_ : cartes terrains scannées par les joueurs
	card_displays_ : Cartes affichées
	refresh_scene_polygons_ : booléen permettant si de nouveau élément sont apparues à l'écran

Classe réalisée par GONON Lucas
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
	R : Initialise le pointeur vers les polygon correspondant de la scène
	*/
	void initSceneOverlayPolygon(std::vector<OpenGlPolygon*>* scene_overlay_polygons) { scene_overlay_polygons_ = scene_overlay_polygons; }
	
	/*
	R : récupère les cartes scannées par les joueurs et met à jour les cartes affichées
	E : les cartes scannées
	*/
	void update(const std::array<E_QuadrimonName::e_QuadrimonName,2>& players_quadrimon_card, const std::array<E_TerrainName::e_TerrainName, 2>& players_terrain_card);
	void triggerQuadrimonCard(E_Player::e_Player player) { card_displays_[static_cast<int>(player)].trigger(); }
	void triggerTerrainCard(E_Player::e_Player player) { card_displays_[2 + static_cast<int>(player)].trigger(); }
	void discardQuadrimonCard(E_Player::e_Player player) { card_displays_[static_cast<int>(player)].discard(); }
	void init();
};


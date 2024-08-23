#pragma once
#include "quadrimon/Quadrimon.h"
#include "data_struct/OpenGlPolygon.h"
#include "enum/E_TerrainName.h"
#include "enum/E_Player.h"
#include "data_struct/LabelElementChange.h"

/*
Cette classe est une classe virtuelle/interface qui sert de template aux différents terrains :
Elle contient le modèle du terrain (basiquement un plan), sa texture, des méthodes permettant de faire valoir ses effets, le nombre de tours restants

Classe réalisé par GONON Lucas (60%) et  BELARIBI Ryan (40%)
*/

class Terrain
{
protected :
	inline static std::array<std::vector<OpenGlPolygon*>, 2>  terrains_polygons_; // modèle des terrains
	inline static std::array<QMatrix4x4, 2>  player_side_models_; // matrices de transformation permettant d'amener le modèle du terrain du bon côté/la où il est censé apparaître
	E_Player::e_Player player_side_;
	int turn_left_; // nombre de tours restants du terrain
	int total_turn_;
	bool is_infinite_; // pour les cartes a effet permanent
	E_TerrainName::e_TerrainName name_; // nom du terrain

	std::string getTerrainActivationText(int player_index)
	{
		return " Le terrain " + E_TerrainName::TERRAIN_NAME_STRING_MAP.at(name_) + " du joueur " + std::to_string(player_index + 1) + " s'active, \n";
	}
public :
	Terrain(E_Player::e_Player player_side, bool is_infinite = false);
	virtual ~Terrain();
	void update(); // fait appel aux autres méthodes en fonctionde l'état du jeu
	virtual void applyEffect(Quadrimon* quadrimon) = 0;// appplique l'effet de la carte terrain
	virtual void clearTerrainEffect(Quadrimon* quadrimon) {} // supprime le terrain une fois le nombre de tours arrivé a expiration (0)
	virtual std::string getDisplayEffectText(const Quadrimon* quadrimon, int player_index) = 0; // texte affiché dans l'overlay
	


	//getters et setters
	int getTurn() const { return turn_left_; }
	bool isInfinite() const {return is_infinite_;}
	E_TerrainName::e_TerrainName getName() const { return name_; }
	std::string getTurnLeftText();
	bool willDisappear() const; //vérifie si une carte doit disparaitre (tours a zero, carte non infinie)

	std::vector<OpenGlPolygon*>* getPolygons(E_Player::e_Player player_side) { return &terrains_polygons_[player_side]; }
};



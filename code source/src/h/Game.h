#pragma once
#include <vector>
#include <array>
#include "quadrimon/Quadrimon.h"
#include "terrain/Terrain.h"
#include "data_struct/LabelElementChange.h"
#include "utility/CardReader.h"
#include "enum/E_Player.h"
#include "enum/E_GameState.h"
#include "data_struct/BiTextureOpenGlPolygon.h"

#include <QTimer>
#include "quadrimon/CylindrusTexture.h"
#include "quadrimon/GlaceFraise.h"
#include "quadrimon/OlafBonHommeNeige.h"
#include "quadrimon/SoleilOpenGL.h"
#include "quadrimon/MecaPyramideGizeh.h"
#include "quadrimon/KhoneRoiDemonDemoniaqueSupreme.h"
#include "quadrimon/FlambyDeeseUltimeCreation.h"
#include "quadrimon/MenuDonutVegan.h"
#include "quadrimon/SaladierMystique.h"

#include "terrain/Ouragan.h"
#include "terrain/Marai.h"
#include "terrain/ChatGPT.h"
#include "terrain/Toiles.h"
#include "terrain/Grotte.h"
#include "terrain/Infirmerie.h"
#include "terrain/Volcan.h"
#include "terrain/Foret.h"
#include "terrain/Plage.h"
#include "terrain/EmptyTerrain.h"
#include "utility/SceneOverlay.h";

/*
Cette classe g�re le d�roulement logique du jeu : elle est responsable de la majorit� des appels de m�thodes.

Elle connait le quadrimons, les terrains, l'�tat du jeu, fait interface avec la webcam...

La m�thode principale de cette classe est update, qui fait �voluer l'�tat du jeu, et fait le diff�rents appels de m�thodes en fonction de cet �tat :
Cet �tat est bas� sur une machine d'�tat :cf h/enum/E_Gamestate

Classe r�alis� par BELARIBI Ryan (75%) et GONON Lucas (25%)
*/

class Game
{
private:
	// donn�es de base : ce sont des arrays de taille 2 (un pour le joueur 1, et l'autre pour le joueur 2) contenant un vecteur de taille 2 (chaque joueur peut avoir 2 quadrimons)
	std::array<std::vector<Quadrimon*>, 2> players_quadrimons_; // contient 2 quadrimons pour chaque joueurs
	std::array<unsigned int, 2> players_active_quadrimon_; // indique quel quadrimon parmi ceux qu'un joueur poss�de est sur le terrain
	std::array<Terrain*, 2> players_terrains_; // contient le terrain de chaque joueur, le premier slot contient le terrain de base Empty_terrain (cf h/terrain), et le deux�me contient un terrain de carte
	CardReader card_reader_; // objet webcam
	E_Player::e_Player player_turn_; // quel joueur doit jouer
	E_GameState::e_GameState game_state_;// �tat du jeu, cf h/enum/Gamestate
	std::vector<OpenGlPolygon*>* scene_polygons_; // polygons � afficher � l'�cran
	std::vector<OpenGlPolygon*>* scene_shadow_polygons_; // polygons poss�dant des ombres

	// Gestion de textures des deux terrains, et de la transition douce � la limite entre les deux terrains
	QMatrix4x4 terrain_transition_player_model_;
	std::array< BiTextureOpenGlPolygon*, 2> terrain_transition_;
	std::array<Terrain*, 2> old_terrain_;

	// overlay : informations affich�es a l'�cran
	SceneOverlay scene_overlay_; // Affichage des cartes scann�es

	std::map<std::string, LabelElementChange>* ui_label_text_; // Map permattant de modifier les labels de l'interface � partir de son nom

#ifdef DEBUG
	bool use_camera_ = false;
#endif

	// d�roulement du jeu
	int frame_counter_; // conteur utilis� pour la phase du tour des joueur
	int waiting_timer_;// timer utilis� pendant la phase d'attente
	int min_time_to_wait_; // temps minimum de la phase d'attente
	int quadrimon_damage_took_; // d�gat pris par le quadrimon

	unsigned char ready_ = 0; // signale quand la phase de pr�paration (d�but du jeu) est termin�e : il faut qu'il valle 3 pour qu'elle soit termin�e

	// FLAGS
	bool trigger_player_turn_start_event_ = true;
	bool trigger_terrain_ = true;
	bool refresh_polygon_ = true; // prise en compte d'�ventuel changement de mod�les de polygones
	std::array< E_QuadrimonName::e_QuadrimonName, 2> quadrimon_to_spawn_;
	E_GameState::e_GameState next_state_;
	bool make_quadrimon_attack_;

	// webcam analyse : ce que d�tecte la cam�ra est stock� ici
	std::array<E_QuadrimonName::e_QuadrimonName, 2> scanned_quadrimons_;
	std::array<E_TerrainName::e_TerrainName, 2> scanned_terrains_;

	//gestion exceptionnelle de cam�ra pour certaines animations
	bool p_new_camera_POV_;
	bdm::Vector3f camera_position_;
	bdm::Vector3f center_position_;

	/*
	R : G�n�re un terrain
	E : terrain_name : le terrain � g�n�rer
		player_side : le joueur auquel appartiens le terrain
	S : le terrain g�n�r�
	*/
	Terrain* generateTerrain(E_TerrainName::e_TerrainName terrain_name, E_Player::e_Player player_side); 
	
	/*
	R : Met � jour les information du quadrimon dans les labels affich�s � l'�cran
	E : player : le dresseur du quadrimon
	*/
	void updateQuadrimonUiInfo(E_Player::e_Player player); // mise a jour des infos graphiques sur les quadrimons (points  de vie, attaque, nom...)
	
	/*
	R : Met � jour les information du terrain dans les labels affich�s � l'�cran
	E : player : le joueur auquel appartient le terrain
	*/
	void updateTerrainUiInfo(E_Player::e_Player player); // mise a jour des infos graphiques sur les terrains (nombre de tours, nom...)
public:
	Game();

	/*
	R : Initialise les �l�ments graphique de la partie une fois que le contexte OpenGl est cr�e
	*/
	void initGame();

	/*
	R : Met � jour le jeu, m�thode appel� 20 fois par seconde
	*/
	int update(); // M�thode principale, fait l'appel de m�thodes plus basses en fonction du game_state_

	/*
	R : traite la phase de pr�paration de la partie
	*/
	void preparationPhase(); // phase de d�but du jeu :chacun choisit un quadrimon

	/*
	R : tirage au sort pour choisir le premier joueur
	*/
	void getStartingPlayer(); 

	/*
	R : change le terrain d'un joueur
	E : player : le joueur concern�
		terrain : le nouveau terrain
	*/
	void changeTerrain(E_Player::e_Player player, E_TerrainName::e_TerrainName terrain);

	/*
	R : change le quadrimon d'un joueur
	E : player : le joueur concern�
		quadrimon : le nouveau quadrimon
	*/
	bool changeQuadrimon(E_Player::e_Player player, E_QuadrimonName::e_QuadrimonName quadrimon);

	/*
	R : V�rifie si un joueur peut changer de quadrimon
	E : player : le joueur concern�
		quadrimon : le nouveau quadrimon 
	*/
	bool checkQuadrimon(E_Player::e_Player player, E_QuadrimonName::e_QuadrimonName quadrimon); // check si le changement de quadrimon est licite
	
	/*
	R : check si le nombre de tours restants est a z�ro, et l'efface de players_terrains_
	S : un bool�en permettant de savoir si un terrain a �t� supprim�
	*/
	bool cleanTerrain(E_Player::e_Player player);

	/*
	R : G�n�re un quadrimon
	E : quadrimon_name : le quadrimon � g�n�rer
		trainer : le joueur auquel appartiens le quadrimon
	S : le quadrimon g�n�r�
	*/
	static Quadrimon* generateQuadrimon(E_QuadrimonName::e_QuadrimonName quadrimon_name, E_Player::e_Player trainer); // g�n�re un objet de type Quadrimon d�tect� par la webcam dans scanned_quadrimons_
	
	/*
	R : recommencer une partie quand la premi�re est termin�e
	*/
	void resetGame();
	
	// getters and setters
	E_Player::e_Player getOpponent(); // permet d'avoir l'objet indiquant le joueur adverse (cf h/enum/E_Players.h)
	E_GameState::e_GameState getGameState() { return game_state_; }
	void setGameState(E_GameState::e_GameState newState) { game_state_ = newState; };
	void setScenePolygons(std::vector<OpenGlPolygon*>* scene_polygons) { scene_polygons_ = scene_polygons; }
	void setSceneShadowPolygons(std::vector<OpenGlPolygon*>* scene_shadow_polygons) { scene_shadow_polygons_ = scene_shadow_polygons; }
	void setSceneOverlayPolygons(std::vector<OpenGlPolygon*>* scene_final_visual_polygons) { scene_overlay_.initSceneOverlayPolygon(scene_final_visual_polygons); }
	void setUiLabelText(std::map<std::string, LabelElementChange>* ui_label_text) { ui_label_text_ = ui_label_text;; }
	QImage* getInImage() { return card_reader_.getInImage(); }


	// Gestion exceptionnelle de la cam�ra (animations sp�ciales)
	void getSpecificCamPos(); // met � jour un flag et des positions camera si un quadrimon requiert une animation sp�cifique

	bdm::Vector3f getCamPos() { return camera_position_; }
	bdm::Vector3f getCenterPos() { return center_position_; }
	bool getSpecificCameraPOV() { return p_new_camera_POV_; }
	void downSpecificCameraPOV() { p_new_camera_POV_ = false; }

#ifdef DEBUG
	void createFirstQuadrimon(E_QuadrimonName::e_QuadrimonName quadrimon, E_Player::e_Player player);
	void toggleCameraUse() { use_camera_ = !use_camera_; }
	void setScannedCard(int card_value, bool player, bool quadrimon) { card_reader_.setCardScanned(card_value, player, quadrimon); }
#endif
	~Game();
};


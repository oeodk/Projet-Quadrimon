#pragma once
#include <array>
#include "enum/E_OverlayCardState.h"
#include "data_struct/OpenGlPolygon.h"
#include "function/complexe_polygon.h"

/*
Cette classe de g�rer une carte affich�e par dessus la sc�ne

- Champs :
	card_polygons_ : polygon de la carte
	display_ : bool�en permettant de savoir si il faut afficher la carte
	card_animation_counter_ : conteur utilis� pour l'animation
	card_state_ : �tat de la carte (cf. E_OverlayCardState)
	side_sign_ : valeur permettant de d�terminer si la carte est a droite ou a gauche
	refresh_display_ : variable permettant de rafraichir la carte
	position_ : position de la carte
	dep_ : d�placement que la carte doit r�aliser

Classe r�alis�e par GONON Lucas
*/

class CardDisplay
{
private :
	OpenGlPolygon* card_polygons_;
	bool display_;
	int card_animation_counter_;
	E_OverlayCardState::e_OverlayCardState card_state_;
	int side_sign_;
	bool refresh_display_;
	bdm::Vector3f position_;
	bdm::Vector3f dep_;

	/*
	R : Effectue le d�placement
	*/
	void moveDep();
public :
	/*
	R : Initialisation de la carte
	E : player_model : Model de base de la carte
		side_sign : cot� de la carte
	*/
	void init(const QMatrix4x4* player_model, int side_sign);
	void update();
	void resetCard();
	void setImage(const std::string& path);
	bool getDisplay()const { return display_; }
	/*
	R : Fait apparaitre la carte
	*/
	void makeAppear();
	
	/*
	R : D�clenche la carte et lance l'animation 
	*/
	void trigger();

	/*
	R : d�fausse la carte
	*/
	void discard();

	/*
	Ces deux m�thodes permette de d�placer la carte (droite / gauche)
	*/
	void slideCenter();
	void slideSide();

	bool getRefreshDisplay() const {return refresh_display_; }
	void resetRefreshDisplay() { refresh_display_ = false;; }
	E_OverlayCardState::e_OverlayCardState getState() const { return card_state_; }
	OpenGlPolygon* getPolygon() { return card_polygons_; }
};


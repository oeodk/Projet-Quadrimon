#pragma once
#include "data_struct/OpenGlPolygon.h"
#include "data_struct/DynamicOpenGlPolygon.h"
#include "enum/E_QuadrimonName.h"
#include "enum/E_QuadrimonType.h"
#include "enum/E_Player.h"
#include "enum/E_QuadrimonState.h"
#include "function/complexe_polygon.h"

/*
Cette classe virtuelle donne un template pour chaque Quadrimon : c'est une interface
les quadrimons sont constitu�s d'OpenGLPolygons, agenc�s sous forme complexe : cf l'include complexe_polygon.h

On distingue les polygones du mod�le du quadrimon, et ceux qui servent a attaquer (boule de feu, rayon laser...)
Les polygones parmi ceux- ci qui doivent �tre affich�s a l'�cran sont rang�s dans le vecteur "displayed_polygons_"

Il contient des champs pour les stats des quadrimons, et des m�thodes, dont celles d'animation qui sont v�ritables

Classe r�alis� par GONON Lucas (85%) et  BELARIBI Ryan (15%)
*/

class Quadrimon
{
protected:
	//mod�le du quadrimon
	std::vector<OpenGlPolygon*> polygons_;
	std::vector<OpenGlPolygon*> attack_polygons_;
	std::vector<OpenGlPolygon*> death_polygons_;
	std::vector<OpenGlPolygon*> displayed_polygons_;
	//stats du quadrimon
	E_QuadrimonName::e_QuadrimonName name_;
	E_QuadrimonType::e_QuadrimonType type_;
	E_QuadrimonState::e_QuadrimonState state_;
	E_QuadrimonType::e_QuadrimonType base_type_;
	//joueur auquel appartient le quadrimon
	E_Player::e_Player trainer_;

	//animation
	bool animation_is_finished_; //indique quand une animation et en cours

	unsigned int internal_counter_; // compteur de temps interne permettant l'animation
	bool refresh_displayed_polygons_; // permet la prise en compte de la mise a jour des mod�les 

	QMatrix4x4 player_side_model_; // matrice de transformation qui place le quadrimon du c�t� o� il est cens� appara�tre
	int damage_;
	int life_point_;
	bdm::Vector3f additional_type_advantage_;
	bool is_alive_;

	//gestion exceptionnelle de la cam�ra pour animation
	bool new_camera_POV_;
	bdm::Vector3f camera_position_;
	bdm::Vector3f center_position_;

	void setPolygonScaleToZero();
	void initDisplayedPolygon();
public:
	Quadrimon(E_Player::e_Player trainer);
	
	/*
	R : M�thode permettant de r�liser l'animation du quadrimon en fonction de son �tat
	*/
	virtual void update(); 

	/*
	M�thode permettant l'animation des �tats correspondant
	*/
	virtual void waitingAnimation();
	virtual void appearingAnimation();
	virtual void attackingAnimation();
	virtual void takingDamageAnimation();
	virtual void dyingAnimation();
	virtual void switchingAnimation();
	virtual void deathSwitchingAnimation();

	/*
	R : Rement le quadrimon dans sa position initiale
	*/
	virtual void resetPolygonsModels();

	/*
	R : Permet d'infliger des d�g�ts au quadrimon
	E : damage : les d�g�ts
		oposent_type : le type de l'adversaire
		additional_type_advantage : avantage de type suppl�mentaire du quadrimon adverse
			composante x : avantage du type feu sur le type plante
			composante y : avantage du type eau sur le type feu
			composante z : avantage du type plante sur le type eau
	*/
	int takeDamage(int damage, E_QuadrimonType::e_QuadrimonType oposent_type, const bdm::Vector3f& additional_type_advantage = bdm::Vector3f());

	/*
	R : Permet de modifier la vie d'un quadrimon
	E : value : la vie � ajouter au quadrimon
	*/
	void editLife(int value);

	/*
	R : Permet de modifier les d�g�ts d'un quadrimon
	E : value : les d�g�ts � ajouter au quadrimon
	*/
	void editDamage(int value) { damage_ += value; }

	/*
	R : Permet de r�initialis� le type du quadrimon
	*/
	void resetType() { type_ = base_type_; }
	
	// Getter et Setter de quadrimons
	void setState(E_QuadrimonState::e_QuadrimonState state);
	void setType(E_QuadrimonType::e_QuadrimonType newType) { type_ = newType; }
	void setAdditionalTypeAdvantage(const bdm::Vector3f& new_additional_type_advantage) { additional_type_advantage_ = new_additional_type_advantage; }

	const bdm::Vector3f getAdditionalTypeAdvantage() const { return additional_type_advantage_; }
	bool getRefreshDisplayedPolygons();
	E_QuadrimonName::e_QuadrimonName getName() const { return name_; }
	E_QuadrimonType::e_QuadrimonType getType() const { return type_; }
	E_QuadrimonType::e_QuadrimonType getBaseType() const { return base_type_; }
	E_QuadrimonState::e_QuadrimonState getState() const { return state_; }
	bool isAlive()const { return is_alive_; }
	int getDamage()const { return damage_; }
	int getLife() const { return life_point_; }
	virtual bool animationIsFinished() { return animation_is_finished_; }
	std::vector<OpenGlPolygon*>* getPolygons() { return &displayed_polygons_; }

	virtual ~Quadrimon();

	// to get new camera positions different from the main one turning around the main scene
	bdm::Vector3f getCamPos() { return camera_position_; }
	bdm::Vector3f getCenterPos() { return center_position_; }
	bool getSpecificCameraPOV() { return new_camera_POV_; }
};

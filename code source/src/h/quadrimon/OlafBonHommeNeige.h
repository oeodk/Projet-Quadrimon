#pragma once
#include "quadrimon/Quadrimon.h"

/*
Quadrimon OlafBonHommeNeige

Classe réalisée par BELARIBI Ryan
*/

class OlafBonHommeNeige : public Quadrimon
{
private :
	int number_of_flocons_ = 100;
	void setCenterPos(float t);
	void setCameraPos(unsigned int t);
public:
	OlafBonHommeNeige(E_Player::e_Player trainer);
	void attackingAnimation();
	void waitingAnimation();
	void resetPolygonsModels();
	void takingDamageAnimation();
	void dyingAnimation();
	void deathSwitchingAnimation();
};
#pragma once
#include "quadrimon/Quadrimon.h"

/*
Quadrimon MenuDonutVegan

Classe r�alis�e par BELARIBI Ryan
*/

class MenuDonutVegan : public Quadrimon
{
public:
	MenuDonutVegan(E_Player::e_Player trainer);

	void waitingAnimation();
	void attackingAnimation();
	void takingDamageAnimation();
	void resetPolygonsModels();
};
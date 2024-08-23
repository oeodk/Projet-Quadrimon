#pragma once
#include "quadrimon/Quadrimon.h"

/*
Quadrimon KhoneRoiDemonDemoniaqueSupreme

Classe réalisée par GONON Lucas
*/

class KhoneRoiDemonDemoniaqueSupreme : public Quadrimon
{
	public:
		KhoneRoiDemonDemoniaqueSupreme(E_Player::e_Player trainer);
		void takingDamageAnimation() override;
		void attackingAnimation() override;
		void dyingAnimation() override;
		void waitingAnimation() override;
};
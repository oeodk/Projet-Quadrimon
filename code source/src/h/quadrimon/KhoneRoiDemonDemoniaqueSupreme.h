#pragma once
#include "quadrimon/Quadrimon.h"

/*
Quadrimon KhoneRoiDemonDemoniaqueSupreme

Classe r�alis�e par GONON Lucas
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
#pragma once
#include "quadrimon/Quadrimon.h"

/*
Quadrimon FlambyDeeseUltimeCreation 

Classe réalisée par GONON Lucas
*/

class FlambyDeeseUltimeCreation : public Quadrimon
{
private:
	std::array<int, 64> dying_cube_angle_;
	std::array<int, 64> dying_cube_z_;
	std::array<float, 64> dying_cube_acceleration_;
public:
	FlambyDeeseUltimeCreation(E_Player::e_Player trainer);
	void attackingAnimation() override;
	void dyingAnimation() override;
};
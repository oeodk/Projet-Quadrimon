#pragma once
#include "quadrimon/Quadrimon.h"
#include "data_struct/Vertex.h"

/*
Quadrimon GlaceFraise

Classe réalisée par BELARIBI Ryan
*/

class GlaceFraise : public Quadrimon
{
private:
	static constexpr int number_of_confettis = 100;
	static constexpr int vitesse_rotation_ = 60.f;
	static constexpr int colors_R_[6] = { 1,0,0,1,1,0 };
	static constexpr int colors_G_[6] = { 0,1,0,1,1,1 };
	static constexpr int colors_B_[6] = { 0,0,1,0,1,1 };
	std::array<int, 100> axes_rotations_confettis_;// [-30 à 30]
	std::array<float, 100> trajectoires_confettis_X_; // [-0.05 à 0.05]
	std::array<float, 100> trajectoires_confettis_Y_; // [0.6 à 0.8]
	std::array<float, 100> trajectoires_confettis_START_X_; // [-0.5 a 0.5]
	std::array<float, 100> trajectoires_confettis_START_Z_; // [2.5 a 3.5]

public:
	GlaceFraise(E_Player::e_Player trainer);

	virtual void waitingAnimation() override;
	virtual void attackingAnimation() override;
	void resetPolygonsModels() override;
};
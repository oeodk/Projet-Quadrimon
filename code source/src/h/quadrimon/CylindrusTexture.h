#pragma once
#include "quadrimon/Quadrimon.h"
#include "data_struct/SmallVertex.h"

/*
Quadrimon CylindrusTexture

Classe réalisée par GONON Lucas
*/

class CylindrusTexture : public Quadrimon
{
private :
	// Vertex des ailes sans transformation
	std::vector<SmallVertex> base_wing_vert_;

	std::vector<SmallVertex> particle_verts_;
	std::array<std::vector<float>, 4> particle_theta_angle_;
	std::array<std::vector<float>, 4> particle_phi_angle_;
	const float SIN_ANGLE_P2_ = std::sin(-150 / 180.f * M_PI);
	const float COS_ANGLE_P2_ = std::cos(-150 / 180.f * M_PI);
	const float SIN_ANGLE_P3_ = std::sin(-30 / 180.f * M_PI);
	const float COS_ANGLE_P3_ = std::cos(-30 / 180.f * M_PI);

	bool primitive_displayed_;
	void invertPrimitives();
public:
	CylindrusTexture(E_Player::e_Player trainer);
	void resetPolygonsModels() override;
	void waitingAnimation() override;
	void flapWings(const float& PI_2, const float& DURRATION);
	void attackingAnimation() override;
	void takingDamageAnimation() override;
	void dyingAnimation() override;
};
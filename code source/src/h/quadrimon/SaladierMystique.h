#pragma once
#include "quadrimon/Quadrimon.h"
#include "data_struct/SmallVertex.h"

/*
Quadrimon SaladierMystique

Classe réalisée par GONON Lucas
*/

class SaladierMystique :
	public Quadrimon
{
private :
	Quadrimon* cloned_quadrimon_;
	std::vector<SmallVertex> target_vert_;
	std::vector<SmallVertex> start_vert_;
	int reverse_transformation_;

	void refreshDisplayFromClone();
public:
	SaladierMystique(E_Player::e_Player trainer);
	~SaladierMystique();
	void takingDamageAnimation() override;
	void attackingAnimation() override;
	void dyingAnimation() override;

	void update(E_QuadrimonName::e_QuadrimonName opponent_quadrimon);
};
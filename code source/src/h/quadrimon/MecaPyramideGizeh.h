#pragma once
#include "quadrimon/Quadrimon.h"
#include "data_struct/SmallVertex.h"
#include "data_struct/BiTextureOpenGlPolygon.h"

/*
Quadrimon MecaPyramideGizeh

Classe réalisée par BELARIBI Ryan
*/

class MecaPyramideGizeh : public Quadrimon
{
public:
	MecaPyramideGizeh(E_Player::e_Player trainer);
	void attackingAnimation() override;
	void dyingAnimation() override;
	void setCenterPos(float t) ;
	void setCameraPos(unsigned int t) ;
	void appearingAnimation() override;
	void switchingAnimation() override;
};

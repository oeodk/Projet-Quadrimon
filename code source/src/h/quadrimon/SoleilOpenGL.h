#pragma once
#include "quadrimon/Quadrimon.h"

/*
Quadrimon SoleilOpenGL

Classe réalisée par BELARIBI Ryan
*/

class SoleilOpenGL :
    public Quadrimon
{
private :
    unsigned long other_counter_;
public :
    SoleilOpenGL(E_Player::e_Player trainer);
    void takingDamageAnimation() override;
    void attackingAnimation() override;
    void waitingAnimation() override;
    void dyingAnimation() override;
    void resetPolygonsModels() override{}
};


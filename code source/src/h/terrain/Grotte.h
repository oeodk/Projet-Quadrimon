#pragma once
#include "Terrain.h"

/*
Terrain Grotte

Classe réalisée par BELARIBI Ryan
*/

class Grotte :
    public Terrain
{
public:
    Grotte(E_Player::e_Player player_side);
    virtual void applyEffect(Quadrimon* quadrimon) override {};
    std::string getDisplayEffectText(const Quadrimon* quadrimon, int player_index) override { return ""; }
};


#pragma once
#include "Terrain.h"

/*
Terrain Volcan

Classe réalisée par GONON Lucas
*/

class Volcan :
    public Terrain
{
public:
    Volcan(E_Player::e_Player player_side);
    virtual void applyEffect(Quadrimon* quadrimon) override;
    void clearTerrainEffect(Quadrimon* quadrimon) override { quadrimon->resetType(); }
    std::string getDisplayEffectText(const Quadrimon* quadrimon, int player_index) override;

};



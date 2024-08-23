#pragma once
#include "Terrain.h"

/*
Terrain Foret

Classe r�alis�e par GONON Lucas
*/

class Foret :
    public Terrain
{
public:
    Foret(E_Player::e_Player player_side);
    virtual void applyEffect(Quadrimon* quadrimon) override;
    void clearTerrainEffect(Quadrimon* quadrimon) override { quadrimon->resetType(); }
    std::string getDisplayEffectText(const Quadrimon* quadrimon, int player_index) override;
};


#pragma once
#include "Terrain.h"

/*
Terrain Plage

Classe réalisée par GONON Lucas
*/

class Plage :
    public Terrain
{
public:
    Plage(E_Player::e_Player player_side);
    virtual void applyEffect(Quadrimon* quadrimon) override;
    void clearTerrainEffect(Quadrimon* quadrimon) override;
    std::string getDisplayEffectText(const Quadrimon* quadrimon, int player_index);

};


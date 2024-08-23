#pragma once
#include "terrain/Terrain.h"

/*
Terrain vide

Classe réalisée par GONON Lucas
*/

class EmptyTerrain :
    public Terrain
{
public:
    EmptyTerrain(E_Player::e_Player player_side);
    void applyEffect(Quadrimon* quadrimon) override {}	
    std::string getDisplayEffectText(const Quadrimon* quadrimon, int player_index) override { return ""; }
};


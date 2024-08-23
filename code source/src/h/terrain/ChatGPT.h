#pragma once
#include "Terrain.h"

/*
Terrain ChatGPT

Classe réalisée par BELARIBI Ryan
*/

class ChatGPT :
    public Terrain
{
public:
    ChatGPT(E_Player::e_Player player_side);
    void applyEffect(Quadrimon* quadrimon) override {};
    void clearTerrainEffect(Quadrimon* quadrimon) override;
    std::string getDisplayEffectText(const Quadrimon* quadrimon, int player_index) override { return ""; }
};


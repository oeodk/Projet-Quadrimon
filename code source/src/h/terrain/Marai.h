#pragma once
#include "Terrain.h"

/*
Terrain Marai

Classe réalisée par BELARIBI Ryan
*/

class Marai :
    public Terrain
{
public:
    Marai(E_Player::e_Player player_side);
    void applyEffect(Quadrimon* quadrimon) override;
    std::string getDisplayEffectText(const Quadrimon* quadrimon, int player_index) override
    {
        return getTerrainActivationText(player_index) + " le " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(quadrimon->getName()) +
            " du joueur " + std::to_string(player_index + 1) + " perd 50 PV ";
    }
};


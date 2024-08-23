#pragma once
#include "Terrain.h"

/*
Terrain Toile

Classe réalisée par BELARIBI Ryan
*/

class Toiles :
    public Terrain
{
public:
    Toiles(E_Player::e_Player player_side);
    virtual void applyEffect(Quadrimon* quadrimon) override;
    std::string getDisplayEffectText(const Quadrimon* quadrimon, int player_index) override
    {
        return getTerrainActivationText(player_index) + " le " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(quadrimon->getName()) +
            " du joueur " + std::to_string(player_index + 1) + " perd 100 points d'attaque ";
    }
};


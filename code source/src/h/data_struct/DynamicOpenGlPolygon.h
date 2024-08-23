#pragma once
#include "data_struct/OpenGlPolygon.h"

/*
Ce struct permet d'avoir un polygon avec des points pouvant être modifiés

- Champs :
	refresh : variable permettant de savoir si les points ont été modifier (et donc transférer les données dans les buffer correspondant)

Struct réalisée par GONON Lucas
*/

struct DynamicOpenGlPolygon :
    public OpenGlPolygon
{
	bool refresh;

	DynamicOpenGlPolygon(const QMatrix4x4* player_side_model);
	
	/*
	R : Créé les buffers OpenGl contenant toute les données du polygon
	*/
	void initializeBuffers() override;

	/*
	R : Lie les buffers du polygon au buffers actif et retransfer les points si ils ont été modifiés
	*/
	void bind() override;

	/*
	R : Libère les buffers actif
	*/
	void release() override;
};


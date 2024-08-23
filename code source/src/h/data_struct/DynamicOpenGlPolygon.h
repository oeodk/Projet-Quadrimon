#pragma once
#include "data_struct/OpenGlPolygon.h"

/*
Ce struct permet d'avoir un polygon avec des points pouvant �tre modifi�s

- Champs :
	refresh : variable permettant de savoir si les points ont �t� modifier (et donc transf�rer les donn�es dans les buffer correspondant)

Struct r�alis�e par GONON Lucas
*/

struct DynamicOpenGlPolygon :
    public OpenGlPolygon
{
	bool refresh;

	DynamicOpenGlPolygon(const QMatrix4x4* player_side_model);
	
	/*
	R : Cr�� les buffers OpenGl contenant toute les donn�es du polygon
	*/
	void initializeBuffers() override;

	/*
	R : Lie les buffers du polygon au buffers actif et retransfer les points si ils ont �t� modifi�s
	*/
	void bind() override;

	/*
	R : Lib�re les buffers actif
	*/
	void release() override;
};


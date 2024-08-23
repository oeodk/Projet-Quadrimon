#pragma once

/*
Contient les �tats possibles de la partie, utilis� par la machine d'�tat de la classe game
*/

namespace E_GameState
{
	enum e_GameState
	{
		PREPARATION, // �tat d'attente que les deux joueurs aient un quadrimon charg� 
		TIRAGE, // �tat d�clenchant le tirage au sort du joueur qui commencera
		TURN_PX, // �tat d�clenchant la phase de d�lai du joueur ayant la main, d�lai lequel il peut changer de terrain ou de quadrimon, avant qu'il se mette a attaquer son adveraire
		ATTACK_PX, // �tat d�clenchant l'animation d'attaque de l'attaquant
		DYING_PX, // �tat d�clench� par la mort d'un quadrimon, permettant le switch vers l'autre quadrimon s'il y en a un et qu'il n'est pas mort, ou demande le scan d'un deuxi�me quadrimon s'il n'existe pas encore
		SWITCH_PX, // �tat enclench� quand on veut switch de quadrimon, sous r�serve que le switch soit licite
		TERRAIN_PX, // idem, mais avec les terrains 
		FINISH, // fin de la partie
		WAITING // �tat quand des quadrimons ont une animation d'activ�e : on attend qu'elles prennent fin
	};
}

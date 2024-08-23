#pragma once

/*
Contient les états possibles de la partie, utilisé par la machine d'état de la classe game
*/

namespace E_GameState
{
	enum e_GameState
	{
		PREPARATION, // état d'attente que les deux joueurs aient un quadrimon chargé 
		TIRAGE, // état déclenchant le tirage au sort du joueur qui commencera
		TURN_PX, // état déclenchant la phase de délai du joueur ayant la main, délai lequel il peut changer de terrain ou de quadrimon, avant qu'il se mette a attaquer son adveraire
		ATTACK_PX, // état déclenchant l'animation d'attaque de l'attaquant
		DYING_PX, // état déclenché par la mort d'un quadrimon, permettant le switch vers l'autre quadrimon s'il y en a un et qu'il n'est pas mort, ou demande le scan d'un deuxième quadrimon s'il n'existe pas encore
		SWITCH_PX, // état enclenché quand on veut switch de quadrimon, sous réserve que le switch soit licite
		TERRAIN_PX, // idem, mais avec les terrains 
		FINISH, // fin de la partie
		WAITING // état quand des quadrimons ont une animation d'activée : on attend qu'elles prennent fin
	};
}

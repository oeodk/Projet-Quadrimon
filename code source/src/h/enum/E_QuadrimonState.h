#pragma once

/*
Répertorie les états possibles d'un quadrimon, permet l'appel circonstancié des bonnes méthodes
*/

namespace E_QuadrimonState
{
	enum e_QuadrimonState
	{
		NONE,
		WAITING,
		APPEARING,
		ATTACKING,
		TAKING_DAMAGE,
		DYING,
		SWITCHING,
		E_END
	};
}
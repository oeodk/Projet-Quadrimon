#pragma once

/*
R�pertorie les �tats possibles d'un quadrimon, permet l'appel circonstanci� des bonnes m�thodes
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
#pragma once

/*
�tat des cartes de affichage � l'�cran des cartes scann�e
*/

namespace E_OverlayCardState
{
	enum e_OverlayCardState
	{
		APPEARING,
		WAITING,
		PLAYING,
		SLIDING_SIDE,
		SLIDING_CENTER,
		DISAPPEARING,
		DISCARDING,
		HIDDED,
		E_END
	};
}
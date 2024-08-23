#pragma once

/*
État des cartes de affichage à l'écran des cartes scannée
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
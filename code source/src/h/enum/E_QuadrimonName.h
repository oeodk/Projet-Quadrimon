#pragma once
#include <map>

/*
Répertorie les quadrimons excitants, et permet d'obtenir son std::string associé long et abrégé
*/

namespace E_QuadrimonName
{
	enum e_QuadrimonName
	{
		CYLINDRUS_LE_TEXTURE,
		GLACE_A_LA_FRASE,
		OLAF_LE_BONHOMME_DE_NEIGE,
		SOLEIL_DU_TD_OPENGL,
		MECA_PYRAMIDE_GIZEH,
		KHONE_ROI_DEMON_DEMONIAQUE_SUPREME,
		FLAMBY_DEESSE_ULTIME_DE_LA_CREATION,
		MENU_DONUT_VEGAN,
		SALADIER_MYSTIQUE,
		E_END
	};
	const std::map<E_QuadrimonName::e_QuadrimonName, std::string> QUADRIMON_NAME_STRING_MAP{
		{ E_QuadrimonName::CYLINDRUS_LE_TEXTURE               , "Cylindrus le texture"},
		{ E_QuadrimonName::GLACE_A_LA_FRASE                   , "Glace a la fraise" },
		{ E_QuadrimonName::OLAF_LE_BONHOMME_DE_NEIGE          , "Olaf le bonhomme de neige" },
		{ E_QuadrimonName::SOLEIL_DU_TD_OPENGL                , "Soleil du TD d'OpenGL" },
		{ E_QuadrimonName::MECA_PYRAMIDE_GIZEH                , "Meca-Pyramide Gizeh" },
		{ E_QuadrimonName::KHONE_ROI_DEMON_DEMONIAQUE_SUPREME , "Khone, Roi demon demoniaque supreme" },
		{ E_QuadrimonName::FLAMBY_DEESSE_ULTIME_DE_LA_CREATION, "Flamby, Deesse ultime de la creation" },
		{ E_QuadrimonName::MENU_DONUT_VEGAN                   , "Menu Donut Vegan" },
		{ E_QuadrimonName::SALADIER_MYSTIQUE                  , "Saladier mystique" }};

	const std::map<E_QuadrimonName::e_QuadrimonName, std::string> QUADRIMON_SHORT_NAME_STRING_MAP{
		{ E_QuadrimonName::CYLINDRUS_LE_TEXTURE			      , "cylindrus"},
		{ E_QuadrimonName::GLACE_A_LA_FRASE                   , "glace_fraise" },
		{ E_QuadrimonName::OLAF_LE_BONHOMME_DE_NEIGE          , "olaf" },
		{ E_QuadrimonName::SOLEIL_DU_TD_OPENGL                , "soleil_opengl" },
		{ E_QuadrimonName::MECA_PYRAMIDE_GIZEH                , "meca_pyramide" },
		{ E_QuadrimonName::KHONE_ROI_DEMON_DEMONIAQUE_SUPREME , "khone" },
		{ E_QuadrimonName::FLAMBY_DEESSE_ULTIME_DE_LA_CREATION, "flamby" },
		{ E_QuadrimonName::MENU_DONUT_VEGAN                   , "donut_vegan" },
		{ E_QuadrimonName::SALADIER_MYSTIQUE                  , "saladier_mystique" }};
}
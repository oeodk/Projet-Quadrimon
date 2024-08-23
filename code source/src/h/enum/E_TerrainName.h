#pragma once
#include <map>

/*
Donne le nom de chaque terrain, et permet a partir de cette struct simple d'avoir le nom en std::string associé
*/

namespace E_TerrainName
{
	enum e_TerrainName
	{
		OURAGAN,
		MARAI,
		CHAT_GPT,
		TOILE_ARAIGNEE,
		GROTTE,
		INFIRMERIE,
		VOLCAN,
		FORET,
		PLAGE,
		E_END
	};
	const std::map<E_TerrainName::e_TerrainName, std::string> TERRAIN_NAME_STRING_MAP{
		{ E_TerrainName::OURAGAN       , "Ouragan"},
		{ E_TerrainName::MARAI         , "Marais" },
		{ E_TerrainName::CHAT_GPT      , "ChatGPT" },
		{ E_TerrainName::TOILE_ARAIGNEE, "Toiles d'araignee" },
		{ E_TerrainName::GROTTE        , "Grotte" },
		{ E_TerrainName::INFIRMERIE    , "Infirmerie" },
		{ E_TerrainName::VOLCAN        , "Volcan" },
		{ E_TerrainName::FORET         , "Foret" },
		{ E_TerrainName::PLAGE         , "Plage" },
		{ E_TerrainName::E_END         , "Aucun Terrain" }
	};

	const std::map<E_TerrainName::e_TerrainName, std::string> TERRAIN_SHORT_NAME_STRING_MAP{
		{ E_TerrainName::OURAGAN       , "ouragan"},
		{ E_TerrainName::MARAI         , "marai" },
		{ E_TerrainName::CHAT_GPT      , "chatGPT" },
		{ E_TerrainName::TOILE_ARAIGNEE, "toile_araignee" },
		{ E_TerrainName::GROTTE        , "grotte" },
		{ E_TerrainName::INFIRMERIE    , "infirmerie" },
		{ E_TerrainName::VOLCAN        , "volcan" },
		{ E_TerrainName::FORET         , "foret" },
		{ E_TerrainName::PLAGE         , "plage" }
	};
}
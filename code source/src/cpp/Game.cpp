#include <stdio.h>   
#include <stdlib.h>    
#include <time.h> 
#include "Game.h"

#ifdef DEBUG
#include "utility/Timer.h"
#endif

static constexpr int TURN_SECOND = 5;
static constexpr int GAME_FPS = 20;

Game::Game()
{
	players_quadrimons_[E_Player::PLAYER_1].reserve(2);
	players_quadrimons_[E_Player::PLAYER_2].reserve(2);
	players_active_quadrimon_ = { 0,0 };
	quadrimon_to_spawn_ = { E_QuadrimonName::E_END, E_QuadrimonName::E_END };
	game_state_ = E_GameState::PREPARATION;
	next_state_ = E_GameState::PREPARATION;

	old_terrain_ = { nullptr, nullptr };

	scanned_quadrimons_ = { E_QuadrimonName::E_END, E_QuadrimonName::E_END };
	scanned_terrains_ = { E_TerrainName::E_END, E_TerrainName::E_END };;

	player_turn_ = E_Player::E_END;
	ready_ = 0;
	frame_counter_ = 0;
	waiting_timer_ = 0;
	min_time_to_wait_ = 0;
	scene_polygons_ = nullptr;
	make_quadrimon_attack_ = true;
	p_new_camera_POV_ = false;
}

void Game::initGame()
{
	ui_label_text_->at("historic").setText(" Scannez vos quadrimons ");
	players_terrains_[0] = new EmptyTerrain(E_Player::PLAYER_1);
	players_terrains_[1] = new EmptyTerrain(E_Player::PLAYER_2);
	updateTerrainUiInfo(E_Player::e_Player(0));
	updateTerrainUiInfo(E_Player::e_Player(1));

	terrain_transition_[0] = new BiTextureOpenGlPolygon(&terrain_transition_player_model_);
	createTerrainSphere(25, 24, terrain_transition_[0]->vertices_, terrain_transition_[0]->indices_, 0.5);

	for (auto& vertex : terrain_transition_[0]->vertices_)
	{
		vertex.invertNormals();
	}
	terrain_transition_[0]->initializeBuffers();

	terrain_transition_[1] = new BiTextureOpenGlPolygon(&terrain_transition_player_model_);
	createRectangle(50, 25, terrain_transition_[1]->vertices_, terrain_transition_[1]->indices_);
	terrain_transition_[1]->base_model_.translate(0, 12.5, 0);
	terrain_transition_[1]->initializeBuffers();

	scene_overlay_.init();
}

void Game::updateQuadrimonUiInfo(E_Player::e_Player player) // mise a jour du texte dans l'overlay concernant les quadrimons
{
	ui_label_text_->at("pv_p" + std::to_string(player + 1)).setText(" PV : " + std::to_string(players_quadrimons_[player][players_active_quadrimon_[player]]->getLife()) + " ");
	ui_label_text_->at("atk_p" + std::to_string(player + 1)).setText(" ATK : " + std::to_string(players_quadrimons_[player][players_active_quadrimon_[player]]->getDamage()) + " ");
	ui_label_text_->at("type_p" + std::to_string(player + 1)).setText(" TYPE : " + E_QuadrimonType::QUADRIMON_TYPE_STRING_MAP.at(players_quadrimons_[player][players_active_quadrimon_[player]]->getType()) + " ");
	ui_label_text_->at("quadrimonName_p" + std::to_string(player + 1)).setText(" " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(players_quadrimons_[player][players_active_quadrimon_[player]]->getName()) + " ");

	ui_label_text_->at("quadrimon_pv_" + std::to_string(players_active_quadrimon_[player] + 1) + "_p" + std::to_string(player + 1)).setText(" " + std::to_string(players_quadrimons_[player][players_active_quadrimon_[player]]->getLife()) + " PV ");
}

void Game::updateTerrainUiInfo(E_Player::e_Player player) // mise a jour du texte dans l'overlay concernant les terrains
{
	ui_label_text_->at("terrainName_p" + std::to_string(player + 1)).setText(" " + E_TerrainName::TERRAIN_NAME_STRING_MAP.at(players_terrains_[player]->getName()) + " ");
	ui_label_text_->at("terrainLast_p" + std::to_string(player + 1)).setText(" " + players_terrains_[player]->getTurnLeftText() + " ");
}

int Game::update() // méthode principale : fait évoluler le jeu
{
#ifdef DEBUG
	Timer t;
	if (use_camera_)
	{
		t.start();
		card_reader_.analyseCameraImage();
		t.stopAndPrint("Camera time ");
	}
#else
	card_reader_.analyseCameraImage(); // analyse image webcam > rempli le champs scanned_quadrimons_ et scanned_terrains_
#endif
	for (int i = 0; i < 2; i++) // affectation de ces quadrimons et terrains détectés par la webcam aux joueurs
	{
		const auto [quadrimon, terrain] = card_reader_.getPlayerCards(E_Player::e_Player(i));
		if (quadrimon != E_QuadrimonName::E_END)
		{
			scanned_quadrimons_[i] = quadrimon;
		}
		if (terrain != E_TerrainName::E_END)
		{
			scanned_terrains_[i] = terrain;
		}
	}

	scene_overlay_.update(scanned_quadrimons_, scanned_terrains_); // fait apparaitre a l'écran la carte du quadrimon/terrain capté
	frame_counter_++;

	switch (game_state_) // machine d'état
	{
	case E_GameState::PREPARATION:
		preparationPhase(); //attente que le deux joueurs aient scanné un quadrimon pour démarrer le combat
		break;
	case E_GameState::TIRAGE: // tirage au sort du joueur qui commencera
	{
		bool can_advance = true;
		for (int i = 0; i < 2; i++)
		{
			if (!players_quadrimons_[i][players_active_quadrimon_[i]]->animationIsFinished())
			{
				can_advance = false;
			}
		}
		if (can_advance && frame_counter_ > 30)
		{
			game_state_ = E_GameState::TURN_PX;
			frame_counter_ = 0;
		}
	}
	break;
	case E_GameState::TURN_PX: // tour du joueur X : il a un certain temps pour changer de terrain ou de quadrimon avant que son quadrimon se mette a attaquer
		// début de tour : effets des terrains
		if (trigger_player_turn_start_event_)
		{
			frame_counter_ = 0;
			if (players_terrains_[player_turn_] != nullptr)
			{
				if (trigger_terrain_)
				{
					trigger_terrain_ = false;
					if (players_terrains_[player_turn_]->getName() != E_TerrainName::CHAT_GPT) // cas où ce n'est pas la carte CHATGPT
					{
						const std::string terrain_effect_msg = players_terrains_[player_turn_]->getDisplayEffectText(players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]], player_turn_);
						players_terrains_[player_turn_]->applyEffect(players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]);
						if (terrain_effect_msg != "")
						{
							ui_label_text_->at("historic").setText(terrain_effect_msg);
							frame_counter_ = 0;
							waiting_timer_ = 0;
							min_time_to_wait_ = GAME_FPS * 2;
							game_state_ = E_GameState::WAITING;
							next_state_ = E_GameState::TURN_PX;
							break;
						}
					}
					else //si le terrain et CHATGPT, il faut exécuter, pour soi-même, l'effet de la carte terrain du joueur adverse
					{
						const std::string terrain_effect_msg = players_terrains_[getOpponent()]->getDisplayEffectText(players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]], player_turn_);
						players_terrains_[getOpponent()]->applyEffect(players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]);
						if (terrain_effect_msg != "")
						{
							ui_label_text_->at("historic").setText(" ChatGPT copie l'effet du terrain de l'adversaire \n" + terrain_effect_msg);
							frame_counter_ = 0;
							waiting_timer_ = 0;
							min_time_to_wait_ = GAME_FPS * 2;
							game_state_ = E_GameState::WAITING;
							next_state_ = E_GameState::TURN_PX;
							break;
						}
					}
				}
				players_terrains_[player_turn_]->update(); // mise a jour des infos du terrain (on retire un tour à la carte, on l'enlève i elle et arrivée à expiration...)
				if (cleanTerrain(player_turn_))
				{
					break;
				}
				updateQuadrimonUiInfo(E_Player::e_Player(player_turn_));
				updateTerrainUiInfo(E_Player::e_Player(player_turn_));
			}
			for (int i = 0; i < 2; i++)
			{
				players_quadrimons_[i][players_active_quadrimon_[i]]->setState(E_QuadrimonState::WAITING);
			}
			trigger_terrain_ = true;
			trigger_player_turn_start_event_ = false;
		}
		ui_label_text_->at("historic").setText(" Tour du joueur " + std::to_string(player_turn_ + 1) + " [" + std::to_string((TURN_SECOND * GAME_FPS - frame_counter_ - 1) / GAME_FPS + 1) + "s] ");

		// milieu de tour : changements éventuels
		for (int i = 0; i < 2; i++)
		{
			if (player_turn_ == i)
			{
				//E_QuadrimonName::e_QuadrimonName player_quadrimon = card_reader_.getPlayerQuadrimon(player_turn_);
				if (scanned_quadrimons_[i] != E_QuadrimonName::E_END) //si on scanne un quadrimon
				{
					if (players_terrains_[player_turn_]->getName() != E_TerrainName::GROTTE && !(players_terrains_[player_turn_]->getName() == E_TerrainName::CHAT_GPT && players_terrains_[getOpponent()]->getName() == E_TerrainName::GROTTE)) // on vérifie qu'on a le droit (donc qu'on et pa affecté par un terrain GROTTE)
					{
						if (changeQuadrimon(player_turn_, scanned_quadrimons_[i]))
						{
							ui_label_text_->at("historic").setText(" Le joueur " + std::to_string(player_turn_ + 1) + " retire son " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]->getName()) + " \n et envoie son " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(scanned_quadrimons_[i]) + " ");
						}
					}
					else
					{
						ui_label_text_->at("historic").setText(" Le joueur " + std::to_string(player_turn_ + 1) + " ne peux pas retirer son " + E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]->getName()) + " \n a cause de la grotte sur son terrain ");
						frame_counter_ = 0;
						waiting_timer_ = 0;
						min_time_to_wait_ = GAME_FPS * 2;
						game_state_ = E_GameState::WAITING;
						next_state_ = E_GameState::TURN_PX;
						scene_overlay_.discardQuadrimonCard(player_turn_);
					}
					scanned_quadrimons_[i] = E_QuadrimonName::E_END;
					break;
				}
			}
			//E_TerrainName::e_TerrainName player_terrain = card_reader_.getPlayerTerrain(E_Player::e_Player(i));
			if (scanned_terrains_[i] != E_TerrainName::E_END) // si on scanne un nouveau terrain
			{
				scene_overlay_.triggerTerrainCard(E_Player::e_Player(i));
				changeTerrain(E_Player::e_Player(i), scanned_terrains_[i]);
				std::string historic_msg = " Le joueur " + std::to_string(i + 1) + " active le terrain " + E_TerrainName::TERRAIN_NAME_STRING_MAP.at(scanned_terrains_[i]) + " ";

				scanned_terrains_[i] = E_TerrainName::E_END;
				std::string terrain_effect_msg;
				if (players_terrains_[i]->getName() != E_TerrainName::CHAT_GPT)
				{
					terrain_effect_msg = players_terrains_[i]->getDisplayEffectText(players_quadrimons_[i][players_active_quadrimon_[i]], i);
					players_terrains_[i]->applyEffect(players_quadrimons_[i][players_active_quadrimon_[i]]);
				}
				else
				{
					terrain_effect_msg = players_terrains_[1 - i]->getDisplayEffectText(players_quadrimons_[i][players_active_quadrimon_[i]], i);
					players_terrains_[1 - i]->applyEffect(players_quadrimons_[i][players_active_quadrimon_[i]]);
					if (terrain_effect_msg != "")
					{
						terrain_effect_msg = " ChatGPT copie l'effet du terrain de l'adversaire \n" + terrain_effect_msg;
					}
				}
				if (terrain_effect_msg != "")
				{
					historic_msg += '\n';
					historic_msg += terrain_effect_msg;
				}
				updateQuadrimonUiInfo(E_Player::e_Player(i));
				updateTerrainUiInfo(E_Player::e_Player(i));
				ui_label_text_->at("historic").setText(historic_msg);
				break;
			}
		}
		// fin de tour () : passage en état d'attaque
		if (frame_counter_ > TURN_SECOND * GAME_FPS)
		{
			trigger_player_turn_start_event_ = true;
			game_state_ = E_GameState::ATTACK_PX;
		}
		break;
	case E_GameState::SWITCH_PX: // l'attaque est menée, le tour va changer dès quel'attaque termine
	{
		bool can_advance = true;
		for (int i = 0; i < 2; i++) // on vérifie que les animations d'attaque sont terminées
		{
			if (players_quadrimons_[i].size() > 0 && !players_quadrimons_[i][players_active_quadrimon_[i]]->animationIsFinished())
			{
				can_advance = false;
			}
		}
		frame_counter_--;
		if (can_advance)
		{
			frame_counter_ = 0;
			refresh_polygon_ = true;
			for (int i = 0; i < 2; i++)
			{
				if (quadrimon_to_spawn_[i] != E_QuadrimonName::E_END)
				{
					if (next_state_ == E_GameState::PREPARATION)
					{
						delete players_quadrimons_[i][0];
						refresh_polygon_ = true;
						players_quadrimons_[i][0] = generateQuadrimon(quadrimon_to_spawn_[i], E_Player::e_Player(i));
						ui_label_text_->at("quadrimon_sprite_1_p" + std::to_string(i + 1)).setImage("./assets/textures/small_sprite/" + E_QuadrimonName::QUADRIMON_SHORT_NAME_STRING_MAP.at(players_quadrimons_[i][0]->getName()) + ".png");
						ui_label_text_->at("quadrimon_pv_1_p" + std::to_string(i + 1)).setText(" " + std::to_string(players_quadrimons_[i][0]->getLife()) + " PV ");

					}
					else
					{
						players_terrains_[i]->clearTerrainEffect(players_quadrimons_[i][players_active_quadrimon_[i]]);
						players_active_quadrimon_[i] = 1 - players_active_quadrimon_[i];
						players_quadrimons_[i][players_active_quadrimon_[i]]->setState(E_QuadrimonState::APPEARING);
					}
					quadrimon_to_spawn_[i] = E_QuadrimonName::E_END;
					updateQuadrimonUiInfo(E_Player::e_Player(i));
				}
			}
			game_state_ = E_GameState::WAITING;
		}
	}
	break;
	case E_GameState::WAITING:
	{
		bool can_advance = true;
		for (int i = 0; i < 2; i++)
		{
			if (players_quadrimons_[i].size() > 0 && !players_quadrimons_[i][players_active_quadrimon_[i]]->animationIsFinished())
			{
				can_advance = false;
			}
		}
		waiting_timer_++;
		frame_counter_--;
		if (can_advance && waiting_timer_ > min_time_to_wait_)
		{
			game_state_ = next_state_;
			min_time_to_wait_ = 0;
		}
	}
	break;
	case E_GameState::ATTACK_PX:
		if (make_quadrimon_attack_)
		{
			const std::string active_player_quadrimon_name = E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]->getName());
			const std::string opponent_quadrimon_name = E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(players_quadrimons_[getOpponent()][players_active_quadrimon_[getOpponent()]]->getName());

			ui_label_text_->at("historic").setText(" Le " + active_player_quadrimon_name + " du joueur " + std::to_string(player_turn_ + 1) + " attaque  \n le " + opponent_quadrimon_name + " du joueur " + std::to_string(getOpponent() + 1) + " ");
			quadrimon_damage_took_ = players_quadrimons_[getOpponent()][players_active_quadrimon_[getOpponent()]]->takeDamage(players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]->getDamage(), players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]->getType(), players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]->getAdditionalTypeAdvantage());
			players_quadrimons_[getOpponent()][players_active_quadrimon_[getOpponent()]]->setState(E_QuadrimonState::TAKING_DAMAGE);
			players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]->setState(E_QuadrimonState::ATTACKING);
			make_quadrimon_attack_ = false;
			frame_counter_ = 0;
		}
		if (frame_counter_ == GAME_FPS * 2)
		{
			std::string message = " ";
			if (E_QuadrimonType::isSuperEffective(players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]->getType(), players_quadrimons_[getOpponent()][players_active_quadrimon_[getOpponent()]]->getType()))
			{
				message += "C'est super efficace ! \n ";
			}
			const std::string opponent_quadrimon_name = E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(players_quadrimons_[getOpponent()][players_active_quadrimon_[getOpponent()]]->getName());
			ui_label_text_->at("historic").setText(message + "Le " + opponent_quadrimon_name + " du joueur " + std::to_string(player_turn_ + 1) + " pert " + std::to_string(quadrimon_damage_took_) + " PV ");

		}
		if (players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]->animationIsFinished() && frame_counter_ > GAME_FPS * 4)
		{
			updateQuadrimonUiInfo(getOpponent());
			make_quadrimon_attack_ = true;
			if (players_quadrimons_[getOpponent()][players_active_quadrimon_[getOpponent()]]->isAlive())
			{
				player_turn_ = getOpponent();
				game_state_ = E_GameState::TURN_PX;
			}
			else
			{
				const std::string quadrimon_name = E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(players_quadrimons_[getOpponent()][players_active_quadrimon_[getOpponent()]]->getName());
				ui_label_text_->at("historic").setText(" Le " + quadrimon_name + " du joueur " + std::to_string(getOpponent() + 1) + " est KO ");
				players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]]->setState(E_QuadrimonState::WAITING);
				players_quadrimons_[getOpponent()][players_active_quadrimon_[getOpponent()]]->setState(E_QuadrimonState::DYING);
				game_state_ = E_GameState::DYING_PX;
			}
		}
		break;
	case E_GameState::DYING_PX:
		if (players_quadrimons_[getOpponent()][players_active_quadrimon_[getOpponent()]]->animationIsFinished())
		{
			if (players_quadrimons_[getOpponent()].size() == 1) // si on a toujours pas charg de second quadrimon
			{
				if (scanned_quadrimons_[getOpponent()] != E_QuadrimonName::E_END && scanned_quadrimons_[getOpponent()] != players_quadrimons_[getOpponent()][players_active_quadrimon_[getOpponent()]]->getName())
				{
					changeQuadrimon(getOpponent(), scanned_quadrimons_[getOpponent()]);
					scanned_quadrimons_[getOpponent()] = E_QuadrimonName::E_END;

					player_turn_ = getOpponent();
				}
				else
				{
					ui_label_text_->at("historic").setText(" Joueur " + std::to_string(getOpponent() + 1) + " scanne un Quadrimon ");
				}
			}
			else
			{
				if (players_quadrimons_[getOpponent()][1 - (players_active_quadrimon_[getOpponent()])]->isAlive())
				{
					scene_overlay_.discardQuadrimonCard(getOpponent());
					scanned_quadrimons_[getOpponent()] = E_QuadrimonName::E_END;
					changeQuadrimon(getOpponent(), players_quadrimons_[getOpponent()][1 - (players_active_quadrimon_[getOpponent()])]->getName());
					player_turn_ = getOpponent();
				}
				else
				{
					return player_turn_ + 1;
				}
			}
		}
		break;
	}
	for (int i = 0; i < 2; i++)
	{
		if (players_quadrimons_[i].size() > 0)
		{
			if (dynamic_cast<SaladierMystique*>(players_quadrimons_[i][players_active_quadrimon_[i]]) && players_quadrimons_[1 - i].size() > 0)
			{
				dynamic_cast<SaladierMystique*>(players_quadrimons_[i][players_active_quadrimon_[i]])->update(players_quadrimons_[1 - i][players_active_quadrimon_[1 - i]]->getName());
			}
			else
			{
				players_quadrimons_[i][players_active_quadrimon_[i]]->update();
			}
			if (players_quadrimons_[i][players_active_quadrimon_[i]]->getRefreshDisplayedPolygons())
			{
				refresh_polygon_ = true;
			}
		}
		if (old_terrain_[i] != nullptr)
		{
			if (terrain_transition_[0]->blend_factor_ > 0.9338)
			{
				std::vector<OpenGlPolygon*>* polygons = players_terrains_[i]->getPolygons(E_Player::e_Player(i));
				polygons->at(0)->has_texture_ = false;
				polygons->at(1)->has_texture_ = false;
				delete old_terrain_[i];
				old_terrain_[i] = nullptr;
				terrain_transition_[0]->blend_factor_ = 0;
				terrain_transition_[0]->deleteTexture();
				terrain_transition_[1]->blend_factor_ = 0;
				terrain_transition_[1]->deleteTexture();
				polygons->at(0)->has_texture_ = true;
				polygons->at(1)->has_texture_ = true;
				refresh_polygon_ = true;
			}
			else
			{
				terrain_transition_[0]->blend_factor_ += 0.0667;
				terrain_transition_[1]->blend_factor_ += 0.0667;
			}
		}
	}
	if (refresh_polygon_ && scene_polygons_ != nullptr)
	{
		scene_polygons_->clear();
		scene_shadow_polygons_->clear();
		for (int i = 0; i < 2; i++)
		{
			if (players_quadrimons_[i].size() > 0)
			{
				std::vector<OpenGlPolygon*>* quadrimon_polygons = players_quadrimons_[i][players_active_quadrimon_[i]]->getPolygons();
				for (int j = 0; j < quadrimon_polygons->size(); j++)
				{
					scene_polygons_->push_back(quadrimon_polygons->at(j));
					if (quadrimon_polygons->at(j)->color_.t == 1.f)
					{
						scene_shadow_polygons_->push_back(quadrimon_polygons->at(j));
					}
				}
			}
			if (old_terrain_[i] != nullptr)
			{
				for (const auto& polygon : terrain_transition_)
				{
					scene_polygons_->push_back(polygon);
				}
			}
			else
			{
				std::vector<OpenGlPolygon*>* terrain_polygons = players_terrains_[i]->getPolygons(E_Player::e_Player(i));
				for (const auto& polygon : *terrain_polygons)
				{
					scene_polygons_->push_back(polygon);
				}
			}
		}
		std::sort(scene_polygons_->begin(), scene_polygons_->end(), [](OpenGlPolygon* p1, OpenGlPolygon* p2)
			{
				bool test;
				if (p1->has_transparent_texture_ || p2->has_transparent_texture_)
				{
					return p1->has_transparent_texture_ < p2->has_transparent_texture_;
				}
				else
				{
				return p1->color_.t > p2->color_.t;
				}
			});
		refresh_polygon_ = false;
	}
	return 0;
}

E_Player::e_Player Game::getOpponent() // renvoie l'autre adversaire : cf h/enum/E_Player.h
{
	if (player_turn_ == E_Player::PLAYER_1)
		return E_Player::PLAYER_2;
	else
		return E_Player::PLAYER_1;
}

void Game::preparationPhase() // attente que chaque joueur aie (au moins) un quadrimon actif
{
	// quand le joueur 1 et pret, il ajoute 1 au compteur ready_ : le joueur 2 en ajoute 2
	for (int i = 0; i < 2; i++)
	{
		//E_QuadrimonName::e_QuadrimonName player_quadrimon = card_reader_.getPlayerQuadrimon(E_Player::e_Player(i));
		if (scanned_quadrimons_[i] != E_QuadrimonName::E_END)
		{
			if (ready_ != i + 1)
			{
				ready_ += i + 1;
			}
			changeQuadrimon(E_Player::e_Player(i), scanned_quadrimons_[i]);
			scanned_quadrimons_[i] = E_QuadrimonName::E_END;
		}
	}
	if (ready_ == 3) // le deux joueurs sont prêts
	{
		frame_counter_ = 0;
		getStartingPlayer();
		next_state_ = E_GameState::TURN_PX;
	}
}

void Game::getStartingPlayer()// tirage au ort du joeuru qui commencera
{
	/* initialize random seed: */
	srand(time(NULL));
	player_turn_ = E_Player::e_Player(rand() % 2);
	ui_label_text_->at("historic").setText(" Le joueur " + std::to_string(player_turn_ + 1) + " commence ");
	game_state_ = E_GameState::TIRAGE;
}

Quadrimon* Game::generateQuadrimon(E_QuadrimonName::e_QuadrimonName quadrimon_name, E_Player::e_Player trainer) 
// crée un objet quadrimon en fonction de ce qu'a scanné la webcam dans scanned_quadrimons_
{
	Quadrimon* quadrimon = nullptr;
	switch (quadrimon_name)
	{
	case 0:
		quadrimon = new CylindrusTexture(trainer);
		break;
	case 1:
		quadrimon = new GlaceFraise(trainer);
		break;
	case 2:
		quadrimon = new OlafBonHommeNeige(trainer);
		break;
	case 3:
		quadrimon = new SoleilOpenGL(trainer);
		break;
	case 4:
		quadrimon = new MecaPyramideGizeh(trainer);
		break;
	case 5:
		quadrimon = new KhoneRoiDemonDemoniaqueSupreme(trainer);
		break;
	case 6:
		quadrimon = new FlambyDeeseUltimeCreation(trainer);
		break;
	case 7:
		quadrimon = new MenuDonutVegan(trainer);
		break;
	case 8:
		quadrimon = new SaladierMystique(trainer);
		break;
	}
	return quadrimon;
}

bool Game::changeQuadrimon(E_Player::e_Player player, E_QuadrimonName::e_QuadrimonName quadrimon)
// permet de changer son quadrimon
{
	bool output = false;
	refresh_polygon_ = true;
	if (game_state_ == E_GameState::PREPARATION) 
	// Dans la phase de préparation, si un deuxième quadrimon est scanné pourun joueur, il écrase le premier
	{
		if (players_quadrimons_[player].size() == 0)
		{
			Quadrimon* q = generateQuadrimon(quadrimon, player);
			players_quadrimons_[player].push_back(q);
			ui_label_text_->at("quadrimon_sprite_1_p" + std::to_string(player + 1)).setImage("./assets/textures/small_sprite/" + E_QuadrimonName::QUADRIMON_SHORT_NAME_STRING_MAP.at(quadrimon) + ".png");
			ui_label_text_->at("quadrimon_pv_1_p" + std::to_string(player + 1)).setText(" " + std::to_string(q->getLife()) + " PV ");
			updateQuadrimonUiInfo(player);
			output = true;
		}
		else
		{
			if (checkQuadrimon(player, quadrimon))
			{
				quadrimon_to_spawn_[player] = quadrimon;
				players_quadrimons_[player][players_active_quadrimon_[player]]->setState(E_QuadrimonState::SWITCHING);
				game_state_ = E_GameState::SWITCH_PX;
				output = true;
			}
		}
	}
	else // hors de la phase de préparation, on switch en vérifiant que cela est licite
	{
		if (checkQuadrimon(player, quadrimon)) // le switch est licite
		{
			if (players_quadrimons_[player].size() == 1)
			{
				Quadrimon* q = generateQuadrimon(quadrimon, player);
				players_quadrimons_[player].push_back(q);
				ui_label_text_->at("quadrimon_sprite_2_p" + std::to_string(player + 1)).setImage("./assets/textures/small_sprite/" + E_QuadrimonName::QUADRIMON_SHORT_NAME_STRING_MAP.at(quadrimon) + ".png");
				ui_label_text_->at("quadrimon_pv_2_p" + std::to_string(player + 1)).setText(" " + std::to_string(q->getLife()) + " PV ");
			}
			quadrimon_to_spawn_[player] = quadrimon;
			players_quadrimons_[player][players_active_quadrimon_[player]]->setState(E_QuadrimonState::SWITCHING);
			game_state_ = E_GameState::SWITCH_PX;
			output = true;
		}
	}
	if (scanned_quadrimons_[player] != E_QuadrimonName::E_END) // partie cosmétique
		// cela permet de faire apparaître  l'écran la carte du quadrimon scanné
	{
		if (output)
		{
			scene_overlay_.triggerQuadrimonCard(player);
		}
		else
		{
			scene_overlay_.discardQuadrimonCard(player);
		}
	}
	return output;
}


Terrain* Game::generateTerrain(E_TerrainName::e_TerrainName terrain_name, E_Player::e_Player player_side)
// crée un objet terrain en fonction de ce qu'a scanné la webcam dans scanned_terrains_
{
	Terrain* terrain = nullptr;
	switch (terrain_name)
	{
	case E_TerrainName::OURAGAN:
		terrain = new Ouragan(player_side);
		break;
	case E_TerrainName::MARAI:
		terrain = new Marai(player_side);
		break;
	case E_TerrainName::CHAT_GPT:
		terrain = new ChatGPT(player_side);
		break;
	case E_TerrainName::TOILE_ARAIGNEE:
		terrain = new Toiles(player_side);
		break;
	case E_TerrainName::GROTTE:
		terrain = new Grotte(player_side);
		break;
	case E_TerrainName::INFIRMERIE:
		terrain = new Infirmerie(player_side);
		break;
	case E_TerrainName::VOLCAN:
		terrain = new Volcan(player_side);
		break;
	case E_TerrainName::FORET:
		terrain = new Foret(player_side);
		break;
	case E_TerrainName::PLAGE:
		terrain = new Plage(player_side);
		break;
	case E_TerrainName::E_END:
		terrain = new EmptyTerrain(player_side);
		break;
	}
	return terrain;
}


void Game::changeTerrain(E_Player::e_Player player, E_TerrainName::e_TerrainName terrain)
// permet de changer un terrain
{
	refresh_polygon_ = true;
	if (players_terrains_[player] != nullptr)
	{
		players_terrains_[player]->clearTerrainEffect(players_quadrimons_[player][players_active_quadrimon_[player]]);
		old_terrain_[player] = players_terrains_[player];
		for (int i = 0; i < 2; i++)
		{
			terrain_transition_[i]->has_texture_ = true;
			terrain_transition_[i]->texture_location_ = old_terrain_[player]->getPolygons(player)->at(i)->texture_location_;
			old_terrain_[player]->getPolygons(player)->at(i)->has_texture_ = false;
		}
		players_terrains_[player] = generateTerrain(terrain, player);

		terrain_transition_player_model_ = *old_terrain_[player]->getPolygons(player)->at(0)->player_side_model_;
		refresh_polygon_ = true;

		for (int i = 0; i < 2; i++)
		{
			terrain_transition_[i]->has_second_texture_ = true;
			terrain_transition_[i]->second_texture_location_ = players_terrains_[player]->getPolygons(player)->at(i)->texture_location_;
		}

		frame_counter_ = 0;
		waiting_timer_ = 0;
		min_time_to_wait_ = GAME_FPS * 2;
		game_state_ = E_GameState::WAITING;
		next_state_ = E_GameState::TURN_PX;

		updateQuadrimonUiInfo(player);
		updateTerrainUiInfo(player);
	}
}

bool Game::checkQuadrimon(E_Player::e_Player player, E_QuadrimonName::e_QuadrimonName quadrimon) {
	// vérification de si un changement de quadrimon est licite
	if (players_quadrimons_[player].size() == 1) // s'il n'y a qu'un seul quadrimon dans l'équipe du joueur
	{
		if (players_quadrimons_[player][0]->getName() != quadrimon) // si le quadrimon qu'on scanne n'est pas le même que celui déja dans l'équipe
			return true; // on a le droit
		return false;
	}
	else //s'il y a deux quadrimons dans l'équipe, on vérifie que le quadrimon scanné est bien le même que le deuxième quadrimon de l'équipe, et qu'il n'est pas mort
	{
		if ((players_quadrimons_[player][1 - players_active_quadrimon_[player]]->getName() == quadrimon) && (players_quadrimons_[player][players_active_quadrimon_[player]]->getName() != quadrimon) && (players_quadrimons_[player][1 - players_active_quadrimon_[player]]->isAlive()))
			return true;
		return false;
	}
}

bool Game::cleanTerrain(E_Player::e_Player player) // supprime un terrain dès qu'il arrive a expiration
{
	if (players_terrains_[player]->getTurn() == 0)
	{
		ui_label_text_->at("historic").setText(" L'effet du terrain " + E_TerrainName::TERRAIN_NAME_STRING_MAP.at(players_terrains_[player]->getName()) + " \n du joueur " + std::to_string(player + 1) + " s'estompe ");

		changeTerrain(player, E_TerrainName::E_END);
		return true;
	}
	return false;
}

void Game::resetGame() // recommencer une partie quand elle est terminée
{
	players_active_quadrimon_ = { 0,0 };
	quadrimon_to_spawn_ = { E_QuadrimonName::E_END, E_QuadrimonName::E_END };
	game_state_ = E_GameState::PREPARATION;
	next_state_ = E_GameState::PREPARATION;

	old_terrain_ = { nullptr, nullptr };

	scanned_quadrimons_ = { E_QuadrimonName::E_END, E_QuadrimonName::E_END };
	scanned_terrains_ = { E_TerrainName::E_END, E_TerrainName::E_END };;

	player_turn_ = E_Player::E_END;
	ready_ = 0;
	frame_counter_ = 0;
	waiting_timer_ = 0;
	min_time_to_wait_ = 0;
	make_quadrimon_attack_ = true;

	ready_ = 0;
	trigger_player_turn_start_event_ = true;
	trigger_terrain_ = true;
	refresh_polygon_ = true;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < players_quadrimons_[i].size(); j++)
		{
			delete players_quadrimons_[i][j];
		}
		players_quadrimons_[i].clear();
		delete players_terrains_[i];
		players_terrains_[i] = new EmptyTerrain(E_Player::e_Player(i));
		if (terrain_transition_[i] != nullptr)
		{
			delete terrain_transition_[i];
		}
	}
	scene_polygons_->clear();
	scene_shadow_polygons_->clear();
}

void Game::getSpecificCamPos()
{
	if (player_turn_ != E_Player::E_END)
	{
		if (players_quadrimons_[player_turn_].size() > 0)
		{
			Quadrimon* quadri = players_quadrimons_[player_turn_][players_active_quadrimon_[player_turn_]];
			if (quadri->getSpecificCameraPOV())
			{
				camera_position_ = quadri->getCamPos();
				center_position_ = quadri->getCenterPos();
				p_new_camera_POV_ = true;
			}
		}
	}
}


#ifdef DEBUG

void Game::createFirstQuadrimon(E_QuadrimonName::e_QuadrimonName quadrimon, E_Player::e_Player player)
{
	if (ready_ != player + 1)
	{
		ready_ += player + 1;
	}
	changeQuadrimon(player, quadrimon);
	refresh_polygon_ = true;
}
#endif
Game::~Game()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < players_quadrimons_[i].size(); j++)
		{
			if (players_quadrimons_[i][j] != nullptr)
			{
				delete players_quadrimons_[i][j];
			}
		}
		delete players_terrains_[i];
	}
}


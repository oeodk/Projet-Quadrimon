#include "quadrimon/Quadrimon.h"


Quadrimon::Quadrimon(E_Player::e_Player trainer)
{
	trainer_ = trainer;
	state_ = E_QuadrimonState::APPEARING;
	is_alive_ = true;
	base_type_ = E_QuadrimonType::E_END;

	player_side_model_.setToIdentity();
	animation_is_finished_ = true;
	internal_counter_ = 0;
	new_camera_POV_ = false;

	constexpr float distance_from_center = 7;

	if (trainer == E_Player::PLAYER_1)
	{
		player_side_model_.translate(0, -distance_from_center, 0);
		player_side_model_.rotate(90, 0, 0, 1);
	}
	else
	{
		player_side_model_.translate(0, distance_from_center, 0);
		player_side_model_.rotate(-90, 0, 0, 1);
	}
}

void Quadrimon::update()
{
	switch (state_)
	{
	case E_QuadrimonState::WAITING:
		waitingAnimation();
		break;
	case E_QuadrimonState::APPEARING:
		appearingAnimation();
		if (animation_is_finished_)
		{
			setState(E_QuadrimonState::WAITING);
		}
		break;
	case E_QuadrimonState::ATTACKING:
		attackingAnimation();
		break;
	case E_QuadrimonState::TAKING_DAMAGE:
		takingDamageAnimation();
		break;
	case E_QuadrimonState::DYING:
		dyingAnimation();
		break;
	case E_QuadrimonState::SWITCHING:
		if (is_alive_)
		{
			switchingAnimation();
		}
		else
		{
			deathSwitchingAnimation();
		}
		break;
	case E_QuadrimonState::E_END:
		break;
	default:
		break;
	}
	internal_counter_++;
}

void Quadrimon::setPolygonScaleToZero()
{
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_.scale(0);
	}
}

void Quadrimon::initDisplayedPolygon()
{
	displayed_polygons_.reserve(polygons_.size());
	for (int i = 0; i < polygons_.size(); i++)
	{
		displayed_polygons_.push_back(polygons_[i]);
	}
}


void Quadrimon::waitingAnimation()
{
	QMatrix4x4 transformation;
	transformation.translate(0, 0, 1 + sin((2 * M_PI / 30) * internal_counter_));
	transformation.rotate(360 * (internal_counter_ / 60.f), 0, 0, 1);
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_ = transformation;
	}
}

void Quadrimon::appearingAnimation()
{
	QMatrix4x4 transformation;
	if (internal_counter_ < 30)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		transformation.scale(internal_counter_ / 30.f);
	}
	else
	{
		animation_is_finished_ = true;
	}
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_ = transformation;
	}
}

void Quadrimon::attackingAnimation()
{
	QMatrix4x4 transformation;
	if (internal_counter_ < 30)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		transformation.translate(7 - 7 * std::cos((2 * M_PI / 30) * internal_counter_), 0, abs(7 * std::sin((2 * M_PI / 30) * internal_counter_)));
	}
	else
	{
		animation_is_finished_ = true;
	}
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_ = transformation;
	}
}

void Quadrimon::takingDamageAnimation()
{
	if (internal_counter_ < 15)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		for (auto& polygon : polygons_)
		{
			polygon->color_.set(1 + 5 * std::sin((2 * M_PI / 30) * internal_counter_), 1, 1);
		}
	}
	else
	{
		for (auto& polygon : polygons_)
		{
			polygon->color_.set(1, 1, 1);

		}
		animation_is_finished_ = true;
	}
}

void Quadrimon::dyingAnimation()
{
	QMatrix4x4 transformation;
	if (internal_counter_ < 16)
	{
		if (internal_counter_ == 0)
		{
			for (auto& polygon : polygons_)
			{
				polygon->material_.specular.set(0, 0, 0);
			}
			animation_is_finished_ = false;
		}
		for (auto& polygon : polygons_)
		{
			polygon->color_.set(1 - internal_counter_ / 15.f, 1 - internal_counter_ / 15.f, 1 - internal_counter_ / 15.f);
		}
	}
	else
	{
		if (internal_counter_ < 30)
		{
			transformation.scale(1, 1, (30 - internal_counter_) / 15.f);
		}
		else
		{
			transformation.scale(1, 1, 0);
			animation_is_finished_ = true;
		}
	}
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_ = transformation;
	}
}

void Quadrimon::switchingAnimation()
{
	QMatrix4x4 transformation;
	if (internal_counter_ < 30)
	{
		animation_is_finished_ = false;
		transformation.scale((30 - internal_counter_) / 30.f);
	}
	else
	{
		transformation.scale(0);

		animation_is_finished_ = true;
	}
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_ = transformation;
	}
}

void Quadrimon::deathSwitchingAnimation()
{
	if (internal_counter_ < 30)
	{
		animation_is_finished_ = false;
		for (auto& polygon : displayed_polygons_)
		{
			polygon->after_base_model_.scale(0.9);
		}
	}
	else
	{
		for (auto& polygon : displayed_polygons_)
		{
			polygon->after_base_model_.setToIdentity();
			polygon->after_base_model_.scale(0);
		}
		animation_is_finished_ = true;
	}
}

void Quadrimon::resetPolygonsModels()
{
	for (auto& polygon : polygons_)
	{
		polygon->before_base_model_.setToIdentity();
		polygon->after_base_model_.setToIdentity();
	}
}

void Quadrimon::setState(E_QuadrimonState::e_QuadrimonState state)
{
	internal_counter_ = 0;
	state_ = state;
	if (state_ != E_QuadrimonState::WAITING)
	{
		animation_is_finished_ = false;
	}
	else
	{
		animation_is_finished_ = true;
	}
	if (state_ != E_QuadrimonState::SWITCHING)
	{
		resetPolygonsModels();
	}
}

bool Quadrimon::getRefreshDisplayedPolygons()
{
	const bool refresh = refresh_displayed_polygons_;
	refresh_displayed_polygons_ = false;
	return refresh;
}

int Quadrimon::takeDamage(int damage, E_QuadrimonType::e_QuadrimonType opposent_type, const bdm::Vector3f& additional_type_advantage)
{
	float multiplier = 1;
	switch (opposent_type)
	{
	case E_QuadrimonType::FIRE:
		if (type_ == E_QuadrimonType::GRASS)
		{
			multiplier *= 2;
			multiplier += additional_type_advantage.x;
		}
		break;
	case E_QuadrimonType::WATER:
		if (type_ == E_QuadrimonType::FIRE)
		{
			multiplier *= 2;
			multiplier += additional_type_advantage.y;
		}
		break;
	case E_QuadrimonType::GRASS:
		if (type_ == E_QuadrimonType::WATER)
		{
			multiplier *= 2;
			multiplier += additional_type_advantage.z;
		}
		break;
	}
	life_point_ -= (damage * multiplier);
	if (life_point_ <= 0)
	{
		life_point_ = 0;
		is_alive_ = false;
	}
	return (damage * multiplier);
}

void Quadrimon::editLife(int value)
{
	life_point_ += value;
	if (life_point_ <= 0)
	{
		life_point_ = 0;
		is_alive_ = false;
	}
}

Quadrimon::~Quadrimon()
{
	for (int i = 0; i < polygons_.size(); i++)
	{
		delete polygons_[i];
	}
	for (int i = 0; i < attack_polygons_.size(); i++)
	{
		delete attack_polygons_[i];
	}
}
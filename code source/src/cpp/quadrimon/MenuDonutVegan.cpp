#include "quadrimon/MenuDonutVegan.h"

MenuDonutVegan::MenuDonutVegan(E_Player::e_Player trainer)
	: Quadrimon(trainer)
{
	name_ = E_QuadrimonName::MENU_DONUT_VEGAN;
	type_ = E_QuadrimonType::GRASS;
	base_type_ = E_QuadrimonType::GRASS;
	damage_ = 200;
	life_point_ = 500;

	polygons_.reserve(5);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(1, 1.5, 10, polygons_[0]->vertices_, polygons_[0]->indices_);
	polygons_[0]->loadTexture("./assets/textures/quadrimon/graine.png");
	polygons_[0]->base_model_.translate(0, 0, 1);
	polygons_[0]->color_.set(0.71, 0.47, 0.24);

	polygons_[0]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCube(2.2, 2.2, 0.5, polygons_[1]->vertices_, polygons_[1]->indices_);
	polygons_[1]->base_model_.translate(0, 0, 1.45);
	polygons_[1]->color_.set(1, 1, 0);
	polygons_[1]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createTorus(1.1, 0.4, 20, polygons_[2]->vertices_, polygons_[2]->indices_);
	polygons_[2]->base_model_.translate(0, 0, 2.1);
	polygons_[2]->loadTexture("./assets/textures/quadrimon/glacage.png");
	polygons_[2]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.3, 1.45, 10, polygons_[3]->vertices_, polygons_[3]->indices_);
	polygons_[3]->base_model_.translate(0, 0, 2.5);
	polygons_[3]->color_.set(1, 0, 0);
	polygons_[3]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createSphere(1.6, 10, polygons_[4]->vertices_, polygons_[4]->indices_, 0.5);
	polygons_[4]->loadTexture("./assets/textures/quadrimon/graine.png");
	polygons_[4]->base_model_.translate(0, 0, 2.8);
	polygons_[4]->base_model_.rotate(90, 1, 0, 0);
	polygons_[4]->color_.set(0.71, 0.47, 0.24);
	polygons_[4]->initializeBuffers();

	setPolygonScaleToZero();
	initDisplayedPolygon();
}


void MenuDonutVegan::waitingAnimation()
{
	QMatrix4x4 transformation;
	transformation.translate(0, 0, 1 + sin((2 * M_PI / 30) * internal_counter_));
	transformation.rotate(360 * (internal_counter_ / 60.f), 0, 0, 1);
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_ = transformation;
	}
}


void MenuDonutVegan::attackingAnimation()
{
	QMatrix4x4 sandwich_trajectory;
	QMatrix4x4 rotation1, rotation2, rotation3;
	if (internal_counter_ < 30)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		rotation1.rotate(45 * sin(2 * M_PI * (internal_counter_ - 60.f) / 60.f), 0, 1, 0);
		rotation2.rotate(-45 * sin(2 * M_PI * (internal_counter_ - 60.f) / 60.f), 0, 1, 0);
		rotation3.rotate(45 * sin(2 * M_PI * (internal_counter_ - 60.f) / 60.f), 0, 0, 1);
		for (int i = 0; i < 2; i++)
		{
			polygons_[i]->before_base_model_ = rotation1;
		}
		polygons_[3]->before_base_model_ = rotation2;
		polygons_[4]->before_base_model_ = rotation3;
		
		sandwich_trajectory.translate(14 - (((internal_counter_ - 15.f) * (internal_counter_ - 15.f)) / 16.f), 0, 0);

	}
	else
	{
		for (auto& polygon : polygons_)
		{
			polygon->before_base_model_.setToIdentity();
		}
		animation_is_finished_ = true;
	}
	polygons_[2]->after_base_model_ = sandwich_trajectory;
}

void MenuDonutVegan::takingDamageAnimation()
{
	if (internal_counter_ < 15)
	{
		polygons_[0]->color_.set(5 * std::sin((2 * M_PI / 30) * internal_counter_) + 0.71, 0.47, 0.24);
		polygons_[1]->color_.set(5 * std::sin((2 * M_PI / 30) * internal_counter_) + 1, 1, 0);
		polygons_[2]->color_.set(5 * std::sin((2 * M_PI / 30) * internal_counter_) + 1, 1, 1);
		polygons_[3]->color_.set(5 * std::sin((2 * M_PI / 30) * internal_counter_) + 1, 0, 0);
		polygons_[4]->color_.set(5 * std::sin((2 * M_PI / 30) * internal_counter_) + 0.71, 0.47, 0.24);
	}
	else
	{
		polygons_[0]->color_.set(0.71, 0.47, 0.24);
		polygons_[1]->color_.set(1, 1, 0);
		polygons_[2]->color_.set(1, 1, 1);
		polygons_[3]->color_.set(1, 0, 0);
		polygons_[4]->color_.set(0.71, 0.47, 0.24);

		animation_is_finished_ = true;
	}
}


void MenuDonutVegan::resetPolygonsModels()
{
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_.setToIdentity();
	}
}
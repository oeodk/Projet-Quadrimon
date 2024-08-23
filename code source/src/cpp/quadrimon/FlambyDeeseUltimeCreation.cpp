#include "quadrimon/FlambyDeeseUltimeCreation.h"

FlambyDeeseUltimeCreation::FlambyDeeseUltimeCreation(E_Player::e_Player trainer)
	: Quadrimon(trainer)
{
	name_ = E_QuadrimonName::FLAMBY_DEESSE_ULTIME_DE_LA_CREATION;
	type_ = E_QuadrimonType::GRASS;
	base_type_ = E_QuadrimonType::GRASS;
	damage_ = 0;
	life_point_ = 900;
	polygons_.reserve(28);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCube(4, 4, 4, polygons_.back()->vertices_, polygons_.back()->indices_);
	polygons_.back()->loadTexture("./assets/textures/quadrimon/flamby.png", GL_NEAREST);
	polygons_.back()->material_.specular.set(0, 0, 0);
	polygons_.back()->base_model_.translate(0, 0, 2);
	polygons_.back()->initializeBuffers();

	attack_polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createSphere(20, 20, attack_polygons_.back()->vertices_, attack_polygons_.back()->indices_, 0.5);
	attack_polygons_.back()->before_base_model_.scale(0);
	attack_polygons_.back()->base_model_.rotate(90, 1, 0, 0);
	attack_polygons_.back()->color_.set(0.8, 0.8, 0.8, 0.75);
	attack_polygons_.back()->material_.ambient.set(1, 1, 1);
	attack_polygons_.back()->material_.specular.set(0, 0, 0);
	attack_polygons_.back()->material_.diffuse.set(0, 0, 0);
	attack_polygons_.back()->initializeBuffers();

	setPolygonScaleToZero();
	initDisplayedPolygon();
	constexpr unsigned int CUBE_SECTION_NUMBER = 4;

	for (int i = 0; i < CUBE_SECTION_NUMBER; i++)
	{
		for (int j = 0; j < CUBE_SECTION_NUMBER; j++)
		{
			for (int k = 0; k < CUBE_SECTION_NUMBER; k++)
			{
				death_polygons_.push_back(new OpenGlPolygon(&player_side_model_));
				createCube(1, 1, 1, death_polygons_.back()->vertices_, death_polygons_.back()->indices_);
				death_polygons_.back()->base_model_.translate((i - 2), (j - 2), 0.5 + k);
				if (k == CUBE_SECTION_NUMBER - 1)
				{
					death_polygons_.back()->loadTexture("./assets/textures/quadrimon/flamby_small_cube_top.png", GL_NEAREST);
				}
				else
				{
					death_polygons_.back()->loadTexture("./assets/textures/quadrimon/flamby_small_cube_bottom.png", GL_NEAREST);
				}

				death_polygons_.back()->initializeBuffers();
				dying_cube_angle_[k + CUBE_SECTION_NUMBER * j + CUBE_SECTION_NUMBER * CUBE_SECTION_NUMBER * i] = rand() % 360;
				dying_cube_z_[k + CUBE_SECTION_NUMBER * j + CUBE_SECTION_NUMBER * CUBE_SECTION_NUMBER * i] = 0.5 + k;
				dying_cube_acceleration_[k + CUBE_SECTION_NUMBER * j + CUBE_SECTION_NUMBER * CUBE_SECTION_NUMBER * i] = (rand() % 100 - 100) / 100.f;
			}
		}
	}
}

void FlambyDeeseUltimeCreation::attackingAnimation()
{
	if (internal_counter_ < 60)
	{
		if (internal_counter_ < 40)
		{
			if (internal_counter_ == 0)
			{
				polygons_[0]->after_base_model_.setToIdentity();
				animation_is_finished_ = false;
				polygons_[0]->loadTexture("./assets/textures/quadrimon/flamby_tnt.png", GL_NEAREST);
			}
			if (internal_counter_ % 5 == 0)
			{
				polygons_[0]->has_texture_ = !polygons_[0]->has_texture_;
			}
		}
		else
		{
			if (internal_counter_ == 40)
			{
				polygons_[0]->has_texture_ = true;
				polygons_[0]->loadTexture("./assets/textures/quadrimon/flamby.png", GL_NEAREST);
				displayed_polygons_.push_back(attack_polygons_[0]);
				refresh_displayed_polygons_ = true;
			}
			attack_polygons_[0]->before_base_model_.setToIdentity();
			attack_polygons_[0]->before_base_model_.scale((internal_counter_ - 40) / 20.f);
		}
	}
	else
	{
		animation_is_finished_ = true;
		displayed_polygons_.clear();
		displayed_polygons_.push_back(polygons_[0]);
		attack_polygons_[0]->before_base_model_.scale(0);
	}
}

void FlambyDeeseUltimeCreation::dyingAnimation()
{
	//movement equation : -(dispersion * x - sqrt(h))² + h
	constexpr int TOTAL_DURATION = 15;
	if (internal_counter_ < TOTAL_DURATION + 15)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
			displayed_polygons_.clear();
			for (int i = 0; i < death_polygons_.size(); i++)
			{
				displayed_polygons_.push_back(death_polygons_[i]);
			}
			refresh_displayed_polygons_ = true;
		}
		const float x = (4 * internal_counter_) / float(TOTAL_DURATION);
		for (int i = 0; i < death_polygons_.size(); i++)
		{
			const float height = 4 + dying_cube_acceleration_[i];
			const float z = -std::pow(0.75 * x - sqrt(height), 2) + height;
			if(z + dying_cube_z_[i] > -0.5)
			{
				death_polygons_[i]->before_base_model_.setToIdentity();
				death_polygons_[i]->before_base_model_.rotate(dying_cube_angle_[i] * (internal_counter_ / float((dying_cube_acceleration_[i] + 1) * 10)), 0, 1, 0);
				death_polygons_[i]->after_base_model_.setToIdentity();
				death_polygons_[i]->after_base_model_.rotate(dying_cube_angle_[i], 0, 0, 1);
				death_polygons_[i]->after_base_model_.translate(x, 0, z);
			}
		}
	}
	else
	{
		animation_is_finished_ = true;
	}
}

#include "quadrimon/KhoneRoiDemonDemoniaqueSupreme.h"
static constexpr float FLOATER_COLOR = 20;


KhoneRoiDemonDemoniaqueSupreme::KhoneRoiDemonDemoniaqueSupreme(E_Player::e_Player trainer)
	: Quadrimon(trainer)
{
	name_ = E_QuadrimonName::KHONE_ROI_DEMON_DEMONIAQUE_SUPREME;
	type_ = E_QuadrimonType::FIRE;
	base_type_ = E_QuadrimonType::FIRE;
	damage_ = 350;
	life_point_ = 350;

	polygons_.reserve(9);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCone(5, 1.5, 20, polygons_[0]->vertices_, polygons_[0]->indices_);
	polygons_[0]->base_model_.translate(0, 0, 2.5);
	polygons_[0]->loadTexture("./assets/textures/quadrimon/khone_cone.png");
	polygons_[0]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.9, 0.19, 15, polygons_[1]->vertices_, polygons_[1]->indices_);
	polygons_[1]->base_model_.translate(0, 0.75, 3.4);
	polygons_[1]->base_model_.rotate(-45, 1, 0, 0);
	polygons_[1]->loadTexture("./assets/textures/quadrimon/khone_cylinder.png");
	polygons_[1]->initializeBuffers();
	
	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.9, 0.19, 15, polygons_[2]->vertices_, polygons_[2]->indices_);
	polygons_[2]->base_model_.translate(0, -0.75, 3.4);
	polygons_[2]->base_model_.rotate(45, 1, 0, 0);
	polygons_[2]->loadTexture("./assets/textures/quadrimon/khone_cylinder.png");
	polygons_[2]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCone(1.2, 0.19, 15, polygons_[3]->vertices_, polygons_[3]->indices_);
	polygons_[3]->base_model_.translate(0, 1.04, 4.15);
	polygons_[3]->base_model_.rotate(-2, 1, 0, 0);
	polygons_[3]->loadTexture("./assets/textures/quadrimon/khone_cone.png");
	polygons_[3]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCone(1.2, 0.19, 15, polygons_[4]->vertices_, polygons_[4]->indices_);
	polygons_[4]->base_model_.translate(0, -1.04, 4.15);
	polygons_[4]->base_model_.rotate(2, 1, 0, 0);
	polygons_[4]->loadTexture("./assets/textures/quadrimon/khone_cone.png");
	polygons_[4]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCone(0.9, 0.2, 15, polygons_[5]->vertices_, polygons_[5]->indices_);
	polygons_[5]->base_model_.translate(0, 2, 2.9);
	polygons_[5]->initializeBuffers();	
	polygons_[5]->color_.set(FLOATER_COLOR, 0, 0);
	polygons_[5]->material_.ambient.set(1, 1, 1);
	polygons_[5]->material_.diffuse.set(0, 0, 0);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCone(0.9, 0.2, 15, polygons_[6]->vertices_, polygons_[6]->indices_);
	polygons_[6]->base_model_.translate(0, 2, 2);
	polygons_[6]->base_model_.rotate(180, 1, 0, 0);
	polygons_[6]->initializeBuffers();
	polygons_[6]->color_.set(FLOATER_COLOR, 0, 0);
	polygons_[6]->material_.ambient.set(1, 1, 1);
	polygons_[6]->material_.diffuse.set(0, 0, 0);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCone(0.9, 0.2, 15, polygons_[7]->vertices_, polygons_[7]->indices_);
	polygons_[7]->base_model_.translate(0, -2, 2.9);
	polygons_[7]->initializeBuffers();
	polygons_[7]->color_.set(FLOATER_COLOR, 0, 0);
	polygons_[7]->material_.ambient.set(1, 1, 1);
	polygons_[7]->material_.diffuse.set(0, 0, 0);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCone(0.9, 0.2, 15, polygons_[8]->vertices_, polygons_[8]->indices_);
	polygons_[8]->base_model_.translate(0, -2, 2);
	polygons_[8]->base_model_.rotate(180, 1, 0, 0);
	polygons_[8]->initializeBuffers();
	polygons_[8]->color_.set(FLOATER_COLOR, 0, 0);
	polygons_[8]->material_.ambient.set(1, 1, 1);
	polygons_[8]->material_.diffuse.set(0, 0, 0);

	for(int i = 0;i< polygons_.size();i++)
	{
		polygons_[i]->material_.specular.set(0, 0, 0);
	}

	//polygons_.back()->loadTexture("./assets/textures/flamby.png");
	attack_polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createSphere(3, 20, attack_polygons_.back()->vertices_, attack_polygons_.back()->indices_);
	attack_polygons_.back()->base_model_.translate(0, 0, 10);
	attack_polygons_.back()->loadTexture("./assets/textures/quadrimon/khone_fireball.png");
	attack_polygons_.back()->material_.diffuse.set(0, 0, 0);
	attack_polygons_.back()->material_.specular.set(0, 0, 0);
	attack_polygons_.back()->material_.ambient.set(17, 17, 1);//13
	attack_polygons_.back()->before_base_model_.scale(0, 0, 0);
	attack_polygons_.back()->color_.set(1, 0.5, 0, 0.99);
	attack_polygons_.back()->initializeBuffers();

	setPolygonScaleToZero();
	initDisplayedPolygon();
}

void KhoneRoiDemonDemoniaqueSupreme::takingDamageAnimation()
{
	if (internal_counter_ < 15)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		for (int i = 0; i < 5; i++)
		{
			polygons_[i]->color_.set(1 + std::sin((2 * M_PI / 30) * internal_counter_), 1, 1);
		}
		for (int i = 5; i < polygons_.size(); i++)
		{
			polygons_[i]->color_.set(FLOATER_COLOR - FLOATER_COLOR * std::sin((2 * M_PI / 30) * internal_counter_), 0, 0);
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			polygons_[i]->color_.set(1, 1, 1);

		}
		for (int i = 5; i < polygons_.size(); i++)
		{
			polygons_[i]->color_.set(FLOATER_COLOR, 0, 0);
		}
		animation_is_finished_ = true;
	}
}

void KhoneRoiDemonDemoniaqueSupreme::attackingAnimation()
{
	QMatrix4x4 right_flyer_transformation, left_flyer_transformation;
	if (internal_counter_ < 45)
	{
		if (internal_counter_ < 15)
		{
			if (internal_counter_ == 0)
			{
				animation_is_finished_ = false;
			}
			if(internal_counter_>10)
			{
				right_flyer_transformation.rotate(30 * ((internal_counter_ - 10) / 5.f), 1, 0, 0);
				left_flyer_transformation.rotate(-30 * ((internal_counter_ - 10) / 5.f), 1, 0, 0);
			}
			right_flyer_transformation.translate(0, 0, 3.5 * (internal_counter_ / 15.f));
			left_flyer_transformation.translate(0, 0, 3.5 * (internal_counter_ / 15.f));
		}
		else
		{
			if(internal_counter_<30)
			{
				if (internal_counter_ == 15)
				{
					displayed_polygons_.push_back(attack_polygons_.back());
					refresh_displayed_polygons_ = true;

					attack_polygons_.back()->after_base_model_.setToIdentity();
					attack_polygons_.back()->before_base_model_.setToIdentity();
					attack_polygons_.back()->before_base_model_.scale(0);
				}
				attack_polygons_.back()->before_base_model_.setToIdentity();
				attack_polygons_.back()->before_base_model_.scale((internal_counter_ - 15) / 15.f);

				right_flyer_transformation.rotate(360 * ((internal_counter_ - 15) / 10.f), 0, 0, 1);
				right_flyer_transformation.rotate(30, 1, 0, 0);
				right_flyer_transformation.translate(0, 0, 3.5);

				left_flyer_transformation.rotate(360 * ((internal_counter_ - 15) / 10.f), 0, 0, 1);
				left_flyer_transformation.rotate(-30, 1, 0, 0);
				left_flyer_transformation.translate(0, 0, 3.5);
			}
			else
			{
				attack_polygons_.back()->before_base_model_.setToIdentity();
				attack_polygons_.back()->after_base_model_.setToIdentity();
				attack_polygons_.back()->after_base_model_.translate(14 * ((internal_counter_ - 30) / 15.f), 0, -4.5 * ((internal_counter_ - 30) / 15.f));
				if (internal_counter_ < 35)
				{
					right_flyer_transformation.rotate(30 - 30 * ((internal_counter_ - 30) / 5.f), 1, 0, 0);
					left_flyer_transformation.rotate(-30 + 30 * ((internal_counter_ - 30) / 5.f), 1, 0, 0);
				}
				right_flyer_transformation.translate(0, 0, 3.5 - 3.5 * ((internal_counter_ - 30) / 15.f));
				left_flyer_transformation.translate(0, 0, 3.5 - 3.5 * ((internal_counter_ - 30) / 15.f));
			}
		}
	}
	else
	{
		refresh_displayed_polygons_ = true;
		displayed_polygons_.clear();
		initDisplayedPolygon();
		animation_is_finished_ = true;
	}
	for (int i = 5; i < 7; i++)
	{
		polygons_[i]->after_base_model_ = right_flyer_transformation;
	}
	for (int i = 7; i < polygons_.size(); i++)
	{
		polygons_[i]->after_base_model_ = left_flyer_transformation;
	}
}

void KhoneRoiDemonDemoniaqueSupreme::dyingAnimation()
{
	QMatrix4x4 flyer_transformation, flyer_transformation_before, body_transformation;
	if (internal_counter_ < 15)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		body_transformation.rotate(-90 * (internal_counter_ / 15.f), 0, 1, 0);
		
		flyer_transformation.translate(0, 0, -2.5f * (internal_counter_ / 15.f));
		flyer_transformation_before.rotate(-90 * (internal_counter_ / 5.f), 0, 1, 0);
		for (int i = 5; i < polygons_.size(); i++)
		{
			polygons_[i]->color_.set(1 - (internal_counter_ / 15.f), 0, 0);
		}
	}
	else
	{
		body_transformation.rotate(-90, 0, 1, 0);

		flyer_transformation.translate(2.45, 0, -2.5f);
		flyer_transformation.rotate(-90, 0, 1, 0);
		for (int i = 5; i < polygons_.size(); i++)
		{
			polygons_[i]->color_.set(1 - (internal_counter_ / 15.f), 0, 0);
		}
		animation_is_finished_ = true;
	}
	for (int i = 0; i < 5; i++)
	{
		polygons_[i]->after_base_model_ = body_transformation;
	}
	for (int i = 5; i < polygons_.size(); i++)
	{
		polygons_[i]->after_base_model_ = flyer_transformation;
		polygons_[i]->before_base_model_ = flyer_transformation_before;
	}
}

void KhoneRoiDemonDemoniaqueSupreme::waitingAnimation()
{
	QMatrix4x4 flyer_transformation, body_transformation;
	flyer_transformation.translate(std::cos(2 * M_PI * internal_counter_ / 15.f), 0, std::sin(2 * M_PI * internal_counter_ / 15.f));
	flyer_transformation.rotate(180 - 180 * std::cos(2 * M_PI * internal_counter_ / 60.f), 0, 0, 1);

	body_transformation.translate(0, 0, 0.5 - 0.5 * std::cos((2 * M_PI / 30) * internal_counter_));
	for (int i = 0; i < 5; i++)
	{
		polygons_[i]->after_base_model_ = body_transformation;
	}
	for (int i = 5; i < polygons_.size(); i++)
	{
		polygons_[i]->after_base_model_ = flyer_transformation;
	}
}

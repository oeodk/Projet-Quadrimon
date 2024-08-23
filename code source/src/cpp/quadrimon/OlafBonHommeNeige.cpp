#include "quadrimon/OlafBonHommeNeige.h"

OlafBonHommeNeige::OlafBonHommeNeige(E_Player::e_Player trainer)
	: Quadrimon(trainer)
{
	name_ = E_QuadrimonName::OLAF_LE_BONHOMME_DE_NEIGE;
	type_ = E_QuadrimonType::WATER;
	base_type_ = E_QuadrimonType::WATER;
	damage_ = 150;
	life_point_ = 500;


	polygons_.reserve(6);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createSphere(1., 20, polygons_[0]->vertices_, polygons_[0]->indices_);
	polygons_[0]->base_model_.translate(0, 0, 2);
	polygons_[0]->color_.set(1, 1, 1);
	polygons_[0]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createSphere(0.8, 20, polygons_[1]->vertices_, polygons_[1]->indices_);
	polygons_[1]->base_model_.translate(0, 0, 3.5);
	polygons_[1]->color_.set(1, 1, 1);
	polygons_[1]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createSphere(0.6, 20, polygons_[2]->vertices_, polygons_[2]->indices_);
	polygons_[2]->base_model_.translate(0, 0, 4.7);
	polygons_[2]->color_.set(1, 1, 1);
	polygons_[2]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(1.2, 0.3, 20, polygons_[3]->vertices_, polygons_[3]->indices_);
	polygons_[3]->loadTexture("./assets/textures/quadrimon/chapeau.png");
	polygons_[3]->base_model_.translate(0, 0, 5.8);
	polygons_[3]->color_.set(1, 1, 1);
	polygons_[3]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.2, 0.4, 20, polygons_[4]->vertices_, polygons_[4]->indices_);
	polygons_[4]->base_model_.translate(0, 0, 5.2);
	polygons_[4]->color_.set(0.001, 0.001, 0.001);
	polygons_[4]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCone(0.9, 0.15, 20, polygons_[5]->vertices_, polygons_[5]->indices_);
	polygons_[5]->base_model_.translate(0.8, 0, 4.7);
	polygons_[5]->base_model_.rotate(90, 0, 1, 0);
	polygons_[5]->color_.set(0.7, 0.3, 0);
	polygons_[5]->initializeBuffers();

	for (int i = 0; i < polygons_.size(); i++)
	{
		polygons_[i]->material_.specular.set(0, 0, 0);
	}

	attack_polygons_.reserve(2);
	//attack_polygons_.reserve(number_of_flocons_ + 1);
	attack_polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCone(5, 1, 20, attack_polygons_[0]->vertices_, attack_polygons_[0]->indices_);
	attack_polygons_[0]->before_base_model_.rotate(180, 0, 1, 0);
	attack_polygons_[0]->base_model_.translate(14, 0, 10);
	attack_polygons_[0]->color_.set(1, 1, 1);
	attack_polygons_[0]->before_base_model_.scale(0);
	attack_polygons_[0]->loadTexture("./assets/textures/quadrimon/glace_surface.png");
	attack_polygons_[0]->material_.shininess = 1;
	attack_polygons_[0]->material_.ambient.set(13, 13, 13);
	attack_polygons_[0]->initializeBuffers();;

	for (int i = 1; i < number_of_flocons_ + 1; i++)
	{
		attack_polygons_.push_back(new OpenGlPolygon(&player_side_model_));
		createSphere(0.1, 3, attack_polygons_[i]->vertices_, attack_polygons_[i]->indices_);
		attack_polygons_[i]->color_.set(1, 1, 1);
		attack_polygons_[i]->material_.diffuse.set(10, 10, 10);
		attack_polygons_[i]->material_.specular.set(10, 10, 10);
		attack_polygons_[i]->material_.ambient.set(10, 10, 10);
		attack_polygons_[i]->base_model_.translate(14 + (((rand() % 50) - 25) / 10.f), ((rand() % 50) - 25) / 10.f, -((rand() % 120) / 10.f));
		attack_polygons_[i]->initializeBuffers();
	}
	setPolygonScaleToZero();
	initDisplayedPolygon();
}

void OlafBonHommeNeige::waitingAnimation()
{
	QMatrix4x4 transformation;
	transformation.translate(0, 0, 1 + sin((2 * M_PI / 30) * internal_counter_));
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_ = transformation;
	}
}

void OlafBonHommeNeige::attackingAnimation()
{
	for (int i = 1; i < number_of_flocons_ + 1; i++)
		attack_polygons_[i]->after_base_model_.translate(0, 0, 0.36);

	if (internal_counter_ < 36)
	{
		if (internal_counter_ < 15)
		{
			if (internal_counter_ == 0)
			{
				//for (int i = 0; i < 2; i++)
				for (int i = 0; i < number_of_flocons_ + 1; i++)
					displayed_polygons_.push_back(attack_polygons_[i]);
				animation_is_finished_ = false;
				//new_camera_POV_=true;
				refresh_displayed_polygons_ = true;
			}
			attack_polygons_[0]->before_base_model_.setToIdentity();
			attack_polygons_[0]->before_base_model_.rotate(180, 0, 1, 0);
			attack_polygons_[0]->before_base_model_.scale(1, 1, internal_counter_ / 15.f);
			attack_polygons_[0]->after_base_model_.setToIdentity();
			attack_polygons_[0]->after_base_model_.translate(0, 0, internal_counter_ / 6.f);
		}
		else
		{
			if (internal_counter_ < 25)
			{

				attack_polygons_[0]->after_base_model_.setToIdentity();
				attack_polygons_[0]->after_base_model_.translate(0, 0, 2);
			}
			else if (internal_counter_ < 28)
			{
				attack_polygons_[0]->after_base_model_.setToIdentity();
				attack_polygons_[0]->after_base_model_.translate(0, 0, 2 - 9 * ((internal_counter_ - 25) / 3.f));
			}
			else
			{
				attack_polygons_[0]->after_base_model_.setToIdentity();
				attack_polygons_[0]->after_base_model_.translate(0, 0, -5);
			}
		}
	}
	else
	{
		refresh_displayed_polygons_ = true;
		new_camera_POV_ = false;
		displayed_polygons_.clear();
		initDisplayedPolygon();
		animation_is_finished_ = true;
		attack_polygons_.back()->before_base_model_.setToIdentity();
		attack_polygons_[0]->before_base_model_.rotate(180, 0, 1, 0);
		attack_polygons_[0]->before_base_model_.scale(0);
		for (int i = 1; i < number_of_flocons_ + 1; i++)
			attack_polygons_[i]->after_base_model_.setToIdentity();
	}
}


void OlafBonHommeNeige::resetPolygonsModels()
{
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_.setToIdentity();
	}
}

void OlafBonHommeNeige::setCenterPos(float t) {
	if (trainer_ == E_Player::PLAYER_1)
		center_position_.set(0, 7.f + (rand() % 10) / 200.f , 3.5f + 1.3f * (t / 17.f) + (rand() % 10) / 200.f);

	else
		center_position_.set(0, -7.f + (rand() % 10) / 200.f , 3.5f + 1.3f * (t / 17.f) + (rand() % 10) / 200.f);
}

void OlafBonHommeNeige::setCameraPos(unsigned int t) {
	if (trainer_ == E_Player::PLAYER_1)
		camera_position_ = bdm::Vector3f(0, -1.5f - (t / 17.f), 2.5f);

	else
		camera_position_ = bdm::Vector3f(0, 1.5f + (t / 17.f), 2.5f);
}




void OlafBonHommeNeige::takingDamageAnimation()
{
	if (internal_counter_ < 15)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		for (auto& polygon : polygons_)
		{
			polygon->color_.x += 5 * std::sin((2 * M_PI / 30) * internal_counter_);
		}
	}
	else
	{
		polygons_[0]->color_.set(1, 1, 1);
		polygons_[1]->color_.set(1, 1, 1);
		polygons_[2]->color_.set(1, 1, 1);
		polygons_[3]->color_.set(1, 1, 1);
		polygons_[4]->color_.set(0.001, 0.001, 0.001);
		polygons_[5]->color_.set(0.7, 0.3, 0);

		animation_is_finished_ = true;
	}
}


void OlafBonHommeNeige::dyingAnimation()
{
	QMatrix4x4 fondu;
	QMatrix4x4 carotte;
	QMatrix4x4 chapeau;
	if (internal_counter_ < 22)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		if (internal_counter_ < 11)
			fondu.scale(1, 1 ,(11.f - internal_counter_) / 11.f);
		else 
		{
			fondu.scale(1, 1, 0.f);
			chapeau.translate(0, 0, -5.1f*(internal_counter_ - 11.f) / 11.f);
			carotte.translate(0, 0, -4.6f*(internal_counter_ - 11.f) / 11.f);
		}

	}
	else
	{
		fondu.scale(0.f);
		chapeau.translate(0, 0, -5.1f);
		carotte.translate(0, 0, -4.6f);
		if (internal_counter_ > 29)
		{
			animation_is_finished_ = true;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (i < 3)
			polygons_[i]->after_base_model_ = fondu;
		else if (i < 5)
			polygons_[i]->after_base_model_ = chapeau;
		else
			polygons_[i]->after_base_model_ = carotte;
	}
}

void OlafBonHommeNeige::deathSwitchingAnimation()
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
		/*for (auto& polygon : polygons_)
		{
			polygon->material_.specular.set(0.25, 0.25, 0.25);
			polygon->material_.ambient.set(0.2, 0.2, 0.2);
			polygon->material_.diffuse.set(1, 1, 1);
		}*/
		for (auto& polygon : displayed_polygons_)
		{
			polygon->after_base_model_.setToIdentity();
			polygon->after_base_model_.scale(0);
		}
		animation_is_finished_ = true;
	}
}
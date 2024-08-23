#include "quadrimon/MecaPyramideGizeh.h"

MecaPyramideGizeh::MecaPyramideGizeh(E_Player::e_Player trainer)
	: Quadrimon(trainer)
{
	name_ = E_QuadrimonName::MECA_PYRAMIDE_GIZEH;
	type_ = E_QuadrimonType::FIRE;
	base_type_ = E_QuadrimonType::FIRE;
	damage_ = 400;
	life_point_ = 200;

	polygons_.reserve(10);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createPyramid(3.0, 2, 4, polygons_[0]->vertices_, polygons_[0]->indices_);
	polygons_[0]->base_model_.translate(0, 0, 4.5);
	polygons_[0]->loadTexture("./assets/textures/quadrimon/pyramydeGIGABASE3.png");
	polygons_[0]->has_transparent_texture_ = true;
	polygons_[0]->initializeBuffers();

	polygons_.push_back(new BiTextureOpenGlPolygon(&player_side_model_));
	createPyramid(0.9, 0.7, 4, polygons_[1]->vertices_, polygons_[1]->indices_);
	polygons_[1]->base_model_.translate(0, 0, 5.6);
	polygons_[1]->loadTexture("./assets/textures/quadrimon/OR.png");
	((BiTextureOpenGlPolygon*)polygons_[1])->loadSecondTexture("./assets/textures/quadrimon/illuminatiGIGA2.png");
	polygons_[1]->material_.ambient.set(0.24725, 0.1995, 0.0745);
	polygons_[1]->material_.diffuse.set(0.75164, 0.60648, 0.22648);
	polygons_[1]->material_.specular.set(0.628281, 0.555802, 0.366065);
	polygons_[1]->material_.shininess=2;

	polygons_[1]->initializeBuffers();




	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.9, 0.2, 10, polygons_[2]->vertices_, polygons_[2]->indices_);
	polygons_[2]->base_model_.rotate(180, 0, 1, 0);
	polygons_[2]->base_model_.translate(1, 0, -2.5);
	polygons_[2]->loadTexture("./assets/textures/quadrimon/propulseur.png");
	polygons_[2]->has_transparent_texture_ = true;
	polygons_[2]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.9, 0.2, 10, polygons_[3]->vertices_, polygons_[3]->indices_);
	polygons_[3]->base_model_.rotate(180, 0, 1, 0);
	polygons_[3]->base_model_.translate(-1, 0, -2.5);
	polygons_[3]->loadTexture("./assets/textures/quadrimon/propulseur.png");
	polygons_[3]->has_transparent_texture_ = true;
	polygons_[3]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.9, 0.2, 10, polygons_[4]->vertices_, polygons_[4]->indices_);
	polygons_[4]->base_model_.rotate(180, 0, 1, 0);
	polygons_[4]->base_model_.translate(0, 1, -2.5);
	polygons_[4]->loadTexture("./assets/textures/quadrimon/propulseur.png");
	polygons_[4]->has_transparent_texture_ = true;
	polygons_[4]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.9, 0.2, 10, polygons_[5]->vertices_, polygons_[5]->indices_);
	polygons_[5]->base_model_.rotate(180, 0, 1, 0);
	polygons_[5]->base_model_.translate(0, -1, -2.5);
	polygons_[5]->loadTexture("./assets/textures/quadrimon/propulseur.png");
	polygons_[5]->has_transparent_texture_ = true;
	polygons_[5]->initializeBuffers();


	bdm::Vector3f color(43.f, 241.f, 241.f);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.9, 0.15, 10, polygons_[6]->vertices_, polygons_[6]->indices_);
	polygons_[6]->base_model_.rotate(180, 0, 1, 0);
	polygons_[6]->base_model_.translate(1, 0, -2.4);
	polygons_[6]->material_.ambient.set(color);
	polygons_[6]->material_.specular.set(1,1,1);
	polygons_[6]->material_.diffuse.set(0, 0, 0);
	polygons_[6]->material_.shininess= 20;
	polygons_[6]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.9, 0.15, 10, polygons_[7]->vertices_, polygons_[7]->indices_);
	polygons_[7]->base_model_.rotate(180, 0, 1, 0);
	polygons_[7]->base_model_.translate(-1, 0, -2.4);
	polygons_[7]->material_.ambient.set(color);
	polygons_[7]->material_.specular.set(1, 1, 1);
	polygons_[7]->material_.diffuse.set(0,0,0);
	polygons_[7]->material_.shininess = 20;
	polygons_[7]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.9, 0.15, 10, polygons_[8]->vertices_, polygons_[8]->indices_);
	polygons_[8]->base_model_.rotate(180, 0, 1, 0);
	polygons_[8]->base_model_.translate(0, 1, -2.4);
	polygons_[8]->material_.ambient.set(color);
	polygons_[8]->material_.specular.set(1, 1, 1);
	polygons_[8]->material_.diffuse.set(0,0,0);
	polygons_[8]->material_.shininess = 20;
	polygons_[8]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.9, 0.15, 10, polygons_[9]->vertices_, polygons_[9]->indices_);
	polygons_[9]->base_model_.rotate(180, 0, 1, 0);
	polygons_[9]->base_model_.translate(0, -1, -2.4);
	polygons_[9]->material_.ambient.set(color);
	polygons_[9]->material_.specular.set(1, 1, 1);
	polygons_[9]->material_.diffuse.set(0,0,0);
	polygons_[9]->material_.shininess = 20;
	polygons_[9]->initializeBuffers();

	for (int i = 0; i < 6; i++)
	{
		if (i!=1)
			polygons_[i]->material_.specular.set(0, 0, 0);
	}




	attack_polygons_.reserve(1);

	attack_polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(5.0, 0.02, 4, attack_polygons_[0]->vertices_, attack_polygons_[0]->indices_);
	attack_polygons_[0]->base_model_.rotate(90, 0, 1, 0);
	attack_polygons_[0]->base_model_.translate(-2.9, 0, 2.5);
	attack_polygons_[0]->initializeBuffers();
	attack_polygons_[0]->material_.diffuse.set(255, 0, 0);
	attack_polygons_[0]->material_.specular.set(255, 0, 0);
	attack_polygons_[0]->material_.ambient.set(100, 100, 100);
	attack_polygons_[0]->color_.set(1, 0.3, 0, 0.99);
	attack_polygons_[0]->before_base_model_.scale(0, 0, 0);

	setPolygonScaleToZero();
	initDisplayedPolygon();
}


void MecaPyramideGizeh::attackingAnimation()
{
	QMatrix4x4 illuminati;
	QMatrix4x4 base;
	if (internal_counter_ < 61)
	{
		base.rotate(45, 0, 0, 1);
		base.translate(0, 0, -2.5);
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
			displayed_polygons_.push_back(attack_polygons_.back());
			refresh_displayed_polygons_ = true;
			new_camera_POV_ = true;
			attack_polygons_.back()->after_base_model_.setToIdentity();
			attack_polygons_.back()->before_base_model_.setToIdentity();
			attack_polygons_.back()->before_base_model_.scale(0);

		}
		else
		{
			refresh_displayed_polygons_ = true;
			if (internal_counter_ <= 23)
			{
				if (internal_counter_ <= 11) {
					polygons_[1]->before_base_model_.setToIdentity();
					polygons_[1]->before_base_model_.scale(1 + ((internal_counter_ - 1) / 50.f));
				}
				else {
					polygons_[1]->before_base_model_.setToIdentity();
					polygons_[1]->before_base_model_.scale(1 + ((23 - internal_counter_) / 50.f));
				}
				((BiTextureOpenGlPolygon*)polygons_[1])->blend_factor_ = internal_counter_ / 23.f;
				illuminati.rotate(45 + (90 * (internal_counter_ / 23.f)), 0, 0, 1);
				illuminati.translate(0, 0, -2.5);
			}
			else if (internal_counter_ <= 39)
			{
				illuminati.rotate(135, 0, 0, 1);
				illuminati.translate(0, 0, -2.5);
			}
			else if (internal_counter_ <= 50)
			{
				attack_polygons_.back()->before_base_model_.setToIdentity();
				attack_polygons_.back()->before_base_model_.scale((-39 + internal_counter_) / 2.f);
				attack_polygons_.back()->after_base_model_.setToIdentity();
				attack_polygons_.back()->after_base_model_.translate(-2 + (12 * ((internal_counter_ - 40) / 8.5f)), 0, 0);
				attack_polygons_.back()->material_.ambient.set(100 + (internal_counter_ - 39) * 20, 100 + (internal_counter_ - 39) * 20, 100 + (internal_counter_ - 39) * 20);
				illuminati.rotate(135, 0, 0, 1);
				illuminati.translate(0, 0, -2.5);
			}
			else
			{
				attack_polygons_.back()->before_base_model_.setToIdentity();
				attack_polygons_.back()->before_base_model_.scale((60 - internal_counter_) / 2.f);
				attack_polygons_.back()->after_base_model_.setToIdentity();
				attack_polygons_.back()->after_base_model_.translate(-2 + (12 * ((internal_counter_ - 40) / 8.5f)), 0, 0);
				attack_polygons_.back()->material_.ambient.set(300 - (internal_counter_ - 50) * 20, 300 - (internal_counter_ - 50) * 20, 300 - (internal_counter_ - 50) * 20);
				illuminati.rotate(135, 0, 0, 1);
				illuminati.translate(0, 0, -2.5);
			}
		}
	}
	else
	{
		refresh_displayed_polygons_ = true;
		displayed_polygons_.clear();
		initDisplayedPolygon();
		animation_is_finished_ = true;
		new_camera_POV_ = false;
		((BiTextureOpenGlPolygon*)polygons_[1])->blend_factor_ = 0.f;
	}
	setCenterPos((float)internal_counter_);
	setCameraPos(internal_counter_);
	polygons_[1]->after_base_model_ = illuminati;
	for (int i = 0; i < 10; i++) {
		if (i != 1)
			polygons_[i]->after_base_model_ = base;
	}
}

void MecaPyramideGizeh::setCenterPos(float t) {
	if (trainer_ == E_Player::PLAYER_1)
		center_position_.set(0, -7.f + (t / 34.f), 2.5f + (t / 60.f));
	else
		center_position_.set(0, 7.f - (t / 34.f), 2.5f + (t / 60.f));
}

void MecaPyramideGizeh::setCameraPos(unsigned int t) {
	if (trainer_ == E_Player::PLAYER_1)
		camera_position_.set(4 * cos(((t + 30.f) / 60.f) * M_PI), -8 + 4.5 * sin(((t + 23.f) / 60.f) * M_PI), 2.5 + (t / 34.f));
	else
		camera_position_.set(4 * cos(((t + 30.f) / 60.f) * M_PI), 8 - 4.5 * sin(((t + 23.f) / 60.f) * M_PI), 2.5 + (t / 34.f));
}



void MecaPyramideGizeh::appearingAnimation()
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

void MecaPyramideGizeh::dyingAnimation()
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

void MecaPyramideGizeh::switchingAnimation()
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


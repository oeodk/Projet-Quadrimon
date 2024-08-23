#include "quadrimon/SoleilOpenGL.h"

static constexpr float PLANET_DIST[8] = { 0.95 , 1.2 , 1.45, 1.70, 1.95, 2.2, 2.7, 3.2 };
static constexpr float PLANET_SIZE[8] = { 0.05 , 0.055 , 0.06, 0.065, 0.07, 0.075, 0.12, 0.15 };
static constexpr const char* PLANET_TEXTURE_PATH[8] = { "","","","","","" ,"","" };
static const bdm::Vector3f PLANET_COLOR[8] = { bdm::Vector3f(200, 248, 242) / 255,
											bdm::Vector3f(255, 255, 242) / 255,
											bdm::Vector3f(11, 92, 227) / 255,
											bdm::Vector3f(247, 115, 12) / 255,
											bdm::Vector3f(253, 199, 145) / 255,
											bdm::Vector3f(200, 196, 251) / 255,
											bdm::Vector3f(198, 241, 245) / 255,
											bdm::Vector3f(57, 182, 247) / 255 };
SoleilOpenGL::SoleilOpenGL(E_Player::e_Player trainer)
	: Quadrimon(trainer)
{
	other_counter_ = 0;

	name_ = E_QuadrimonName::SOLEIL_DU_TD_OPENGL;
	type_ = E_QuadrimonType::FIRE;
	base_type_ = E_QuadrimonType::FIRE;
	damage_ = 150;
	life_point_ = 400;

	polygons_.reserve(17);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createSphere(0.5, 20, polygons_[0]->vertices_, polygons_[0]->indices_);
	polygons_[0]->base_model_.translate(0, 0, 4.);
	polygons_[0]->material_.ambient.set(15, 15, 15);
	polygons_[0]->loadTexture("./assets/textures/quadrimon/soleil.png");
	polygons_[0]->initializeBuffers();

	for (int i = 0; i < 8; i++)
	{
		polygons_.push_back(new OpenGlPolygon(&player_side_model_));
		createSphere(PLANET_SIZE[i], 20, polygons_.back()->vertices_, polygons_.back()->indices_);
		polygons_.back()->base_model_.translate(0, PLANET_DIST[i], 4.);
		polygons_.back()->color_.set(PLANET_COLOR[i]);
		polygons_.back()->color_.t = 0.99;
		polygons_.back()->initializeBuffers();
	}

	// orbit
	for (int i = 0; i < 8; i++)
	{
		polygons_.push_back(new OpenGlPolygon(&player_side_model_));
		createCircle(PLANET_DIST[i], 100, polygons_.back()->vertices_, polygons_.back()->indices_);
		polygons_.back()->base_model_.translate(0, 0, 4);
		polygons_.back()->material_.ambient.set(1, 1, 1);
		polygons_.back()->material_.diffuse.set(0, 0, 0);
		polygons_.back()->opengl_primitive_ = GL_LINES;
		polygons_.back()->initializeBuffers();
	}


	for (int i = 0; i < polygons_.size(); i++)
	{
		polygons_[i]->material_.specular.set(0, 0, 0);
	}

	setPolygonScaleToZero();
	initDisplayedPolygon();
}

void SoleilOpenGL::takingDamageAnimation()
{
	if (internal_counter_ < 15)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		for (int i = 0; i < 8; i++)
		{
			polygons_[i + 1]->color_.x += 5 * std::sin((2 * M_PI / 30) * internal_counter_);
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			polygons_[i + 1]->color_.set(PLANET_COLOR[i]);
			polygons_[i + 1]->color_.t = 0.99;
		}

		animation_is_finished_ = true;
	}
}

static constexpr float PLANET_ROTATION_SPEED[8] = { 10.f , 30.f , 50, 80, 100, 120, 140, 160 };
static const bdm::Vector3f ORBIT_ROTATION_AXIS[8] = { bdm::Vector3f(1, 0, 0),
													 bdm::Vector3f(-1, 1, 0),
													 bdm::Vector3f(0,-1, 1),
													 bdm::Vector3f(0, 1, 0),
													 bdm::Vector3f(1, 0,-1),
													 bdm::Vector3f(1,-1, 0),
													 bdm::Vector3f(0, 1, 1),
													 bdm::Vector3f(-1, 0,-1) };
static constexpr float ORBIT_ROTATION_SPEED[8] = { 50.f, 50.f ,50.f ,50.f ,50.f ,50.f ,50.f ,50.f };

void SoleilOpenGL::waitingAnimation()
{
	for (int i = 0; i < 8; i++)
	{
		polygons_[i + 1]->before_base_model_.setToIdentity();
		polygons_[i + 1]->before_base_model_.translate(0, -PLANET_DIST[i], 0);
		polygons_[i + 1]->before_base_model_.rotate(360 * (other_counter_ / ORBIT_ROTATION_SPEED[i]), ORBIT_ROTATION_AXIS[i].x, ORBIT_ROTATION_AXIS[i].y, ORBIT_ROTATION_AXIS[i].z);
		polygons_[i + 1]->before_base_model_.rotate(360 * (other_counter_ / PLANET_ROTATION_SPEED[i]), 0, 0, 1);
		polygons_[i + 1]->before_base_model_.translate(0, PLANET_DIST[i], 0);
		polygons_[i + 9]->before_base_model_.setToIdentity();
		polygons_[i + 9]->before_base_model_.rotate(360 * (other_counter_ / ORBIT_ROTATION_SPEED[i]), ORBIT_ROTATION_AXIS[i].x, ORBIT_ROTATION_AXIS[i].y, ORBIT_ROTATION_AXIS[i].z);
	}
	other_counter_++;
}

void SoleilOpenGL::dyingAnimation()
{
	if (internal_counter_ < 30)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		polygons_[0]->color_.x += 1.5;
	}
	else
	{
		displayed_polygons_.clear();
		displayed_polygons_.push_back(polygons_[0]);
		polygons_[0]->color_.set(0, 0, 0);
		refresh_displayed_polygons_ = true;
		animation_is_finished_ = true;
	}
}

void SoleilOpenGL::attackingAnimation()
{
	constexpr int PLANET_SHOT_DELAY[8] = { 40, 43, 46, 49, 52, 55, 58, 61 };
	if (internal_counter_ < 63)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
			refresh_displayed_polygons_ = true;
		}
		for (int i = 0; i < 8; i++)
		{
			polygons_[i + 1]->after_base_model_.setToIdentity();
			if (internal_counter_ < PLANET_SHOT_DELAY[i] && internal_counter_ > PLANET_SHOT_DELAY[i] - 40)
			{
				polygons_[i + 1]->after_base_model_.translate(14 * sin(2 * M_PI * (internal_counter_ - (PLANET_SHOT_DELAY[i] - 40)) / 80.f), 0, 0);
			}
		}
	}
	else
	{
		refresh_displayed_polygons_ = true;
		displayed_polygons_.clear();
		initDisplayedPolygon();
		animation_is_finished_ = true;
		for (int i = 0; i < 8; i++)
		{
			polygons_[i + 1]->after_base_model_.setToIdentity();
		}
	}
	other_counter_++;
	for (int i = 0; i < 8; i++)
	{
		polygons_[i + 1]->before_base_model_.setToIdentity();
		polygons_[i + 1]->before_base_model_.translate(0, -PLANET_DIST[i], 0);
		polygons_[i + 1]->before_base_model_.rotate(360 * (other_counter_ / ORBIT_ROTATION_SPEED[i]), ORBIT_ROTATION_AXIS[i].x, ORBIT_ROTATION_AXIS[i].y, ORBIT_ROTATION_AXIS[i].z);
		polygons_[i + 1]->before_base_model_.rotate(360 * (other_counter_ / PLANET_ROTATION_SPEED[i]), 0, 0, 1);
		polygons_[i + 1]->before_base_model_.translate(0, PLANET_DIST[i], 0);
		polygons_[i + 9]->before_base_model_.setToIdentity();
		polygons_[i + 9]->before_base_model_.rotate(360 * (other_counter_ / ORBIT_ROTATION_SPEED[i]), ORBIT_ROTATION_AXIS[i].x, ORBIT_ROTATION_AXIS[i].y, ORBIT_ROTATION_AXIS[i].z);
	}
	other_counter_++;
}

#include "quadrimon/GlaceFraise.h"
#include "data_struct/Vertex.h"


GlaceFraise::GlaceFraise(E_Player::e_Player trainer)
	: Quadrimon(trainer)
{
	name_ = E_QuadrimonName::GLACE_A_LA_FRASE;
	type_ = E_QuadrimonType::WATER;
	base_type_ = E_QuadrimonType::WATER;
	damage_ = 100;
	life_point_ = 600;


	polygons_.reserve(6);

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCone(3.0, 1, 10, polygons_[0]->vertices_, polygons_[0]->indices_);
	polygons_[0]->base_model_.translate(0, 0, 3.5);
	polygons_[0]->base_model_.rotate(180, 0, 1, 0);
	polygons_[0]->loadTexture("./assets/textures/quadrimon/cone.png");
	polygons_[0]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(0.7, 1.1, 10, polygons_[1]->vertices_, polygons_[1]->indices_);
	polygons_[1]->base_model_.translate(0, 0, 5);
	polygons_[1]->loadTexture("./assets/textures/quadrimon/cone.png");
	polygons_[1]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createSphere(1.2, 10, polygons_[2]->vertices_, polygons_[2]->indices_);
	polygons_[2]->base_model_.translate(0, 0, 5.8);
	polygons_[2]->loadTexture("./assets/textures/quadrimon/glacage.png");
	polygons_[2]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(1, 0.1, 10, polygons_[3]->vertices_, polygons_[3]->indices_);
	polygons_[3]->base_model_.translate(0.5, 0.5, 6.8);
	polygons_[3]->base_model_.rotate(25, 0, 1, 1);
	polygons_[3]->loadTexture("./assets/textures/quadrimon/paille.png");
	polygons_[3]->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	polygons_[4]->vertices_.reserve(10);
	polygons_[4]->indices_.reserve(18);

	polygons_[4]->vertices_.push_back(Vertex(bdm::Vector3f(0.f, 0.f, 0.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0, 0)));
	polygons_[4]->vertices_.push_back(Vertex(bdm::Vector3f(0.1f, 0.2f, 0.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0, 0)));
	polygons_[4]->vertices_.push_back(Vertex(bdm::Vector3f(-0.1f, 0.2f, 0.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0, 0)));
	polygons_[4]->vertices_.push_back(Vertex(bdm::Vector3f(0.0f, 0.4f, 0.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0, 0)));

	polygons_[4]->vertices_.push_back(Vertex(bdm::Vector3f(0.2f, -0.05f, 0.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0, 0)));
	polygons_[4]->vertices_.push_back(Vertex(bdm::Vector3f(0.1f, -0.2f, 0.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0, 0)));
	polygons_[4]->vertices_.push_back(Vertex(bdm::Vector3f(0.2f, -0.25f, 0.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0, 0)));

	polygons_[4]->vertices_.push_back(Vertex(bdm::Vector3f(-0.2f, -0.05f, 0.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0, 0)));
	polygons_[4]->vertices_.push_back(Vertex(bdm::Vector3f(-0.1f, -0.2f, 0.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0, 0)));
	polygons_[4]->vertices_.push_back(Vertex(bdm::Vector3f(-0.2f, -0.25f, 0.f), bdm::Vector3f(0, 0, 1), bdm::Vector2f(0, 0)));

	polygons_[4]->indices_.push_back(0);
	polygons_[4]->indices_.push_back(1);
	polygons_[4]->indices_.push_back(2);
	polygons_[4]->indices_.push_back(1);
	polygons_[4]->indices_.push_back(2);
	polygons_[4]->indices_.push_back(3);

	polygons_[4]->indices_.push_back(0);
	polygons_[4]->indices_.push_back(4);
	polygons_[4]->indices_.push_back(5);
	polygons_[4]->indices_.push_back(4);
	polygons_[4]->indices_.push_back(5);
	polygons_[4]->indices_.push_back(6);

	polygons_[4]->indices_.push_back(0);
	polygons_[4]->indices_.push_back(7);
	polygons_[4]->indices_.push_back(8);
	polygons_[4]->indices_.push_back(7);
	polygons_[4]->indices_.push_back(8);
	polygons_[4]->indices_.push_back(9);

	polygons_[4]->before_base_model_.rotate(50, 1, 1, 0);
	polygons_[4]->base_model_.translate(0.70f, -0.70f, 6.5);

	polygons_[4]->color_.set(0.14f, 0.48f, 0.22f);
	polygons_[4]->initializeBuffers();

	for (int i = 0; i < polygons_.size() - 1; i++)
	{
		polygons_[i]->material_.specular.set(0, 0, 0);
	}


	attack_polygons_.reserve(number_of_confettis);
	for (int i = 0; i < number_of_confettis; i++)
	{
		attack_polygons_.push_back(new OpenGlPolygon(&player_side_model_));
		createRectangle(0.2, 0.2, attack_polygons_[i]->vertices_, attack_polygons_[i]->indices_);
		attack_polygons_[i]->color_.set(colors_R_[i % 6], colors_G_[i % 6], colors_B_[i % 6]);

		axes_rotations_confettis_[i] = ((rand() % 60) - 30);
		trajectoires_confettis_X_[i] = ((rand() % 100) - 50) / 1000.f;
		trajectoires_confettis_Y_[i] = (((rand() % 20)) / 100.f) + 0.6f;
		trajectoires_confettis_START_X_[i] = ((rand() % 100) - 50) / 100.f;
		trajectoires_confettis_START_Z_[i] = (rand() % 10) + 2.5f;
		attack_polygons_[i]->before_base_model_.rotate(axes_rotations_confettis_[i], 0, 0, 1);
		attack_polygons_[i]->initializeBuffers();
	}
	setPolygonScaleToZero();
	initDisplayedPolygon();
}

void GlaceFraise::waitingAnimation()
{
	QMatrix4x4 transformation;
	transformation.translate(0, 0, sin((2 * M_PI / 30) * internal_counter_));
	transformation.rotate(360 * (internal_counter_ / 60.f), 0, 0, 1);
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_ = transformation;
	}
}

void GlaceFraise::attackingAnimation() {
	constexpr float FIRST_PHASE_TIME = 6.f;
	constexpr float SECOND_PHASE_TIME = 21.f;
	constexpr float THIRD_PHASE_TIME = 41.f;
	constexpr float FOURTH_PHASE_TIME = 56.f;
	constexpr float LAST_PHASE_TIME = 62.f;
	QMatrix4x4 cone, ball, cylinder, plane, tube;
	if (internal_counter_ < LAST_PHASE_TIME)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;

		}
		if (internal_counter_ == SECOND_PHASE_TIME)
		{
			for (int i = 0; i < number_of_confettis; i++)
			{
				displayed_polygons_.push_back(attack_polygons_[i]);
			}
			refresh_displayed_polygons_ = true;
		}
		if (internal_counter_ == THIRD_PHASE_TIME)
		{
			refresh_displayed_polygons_ = true;
			displayed_polygons_.clear();
			initDisplayedPolygon();
		}
		if (internal_counter_ < FIRST_PHASE_TIME)
		{
			plane.translate(0, 0, internal_counter_ / 4.f);
			tube.translate(0, 0, internal_counter_ / 4.f);
			ball.translate(0, 0, internal_counter_ / 4.f);
		}
		else if (internal_counter_ < SECOND_PHASE_TIME)
		{
			cone.rotate(90 * ((internal_counter_ - FIRST_PHASE_TIME) / 15.f), 0, 1, 0);
			cylinder.rotate(90 * ((internal_counter_ - FIRST_PHASE_TIME) / 15.f), 0, 1, 0);
			cone.translate(-5.f * ((internal_counter_ - FIRST_PHASE_TIME) / 15.f), 0, -5.f * ((internal_counter_ - FIRST_PHASE_TIME) / 15.f));
			cylinder.translate(-5.f * ((internal_counter_ - FIRST_PHASE_TIME) / 15.f), 0, -5.f * ((internal_counter_ - FIRST_PHASE_TIME) / 15.f));

			plane.translate(0, 0, 1.5f);
			tube.translate(0, 0, 1.5f);
			ball.translate(0, 0, 1.5f);
		}
		else if (internal_counter_ < THIRD_PHASE_TIME)
		{
			if (internal_counter_ - SECOND_PHASE_TIME < 10)
			{
				cone.translate(-(25 - (((internal_counter_ - SECOND_PHASE_TIME) - 5) * ((internal_counter_ - SECOND_PHASE_TIME) - 5))) / 20.f, 0, 0);
				cylinder.translate(-(25 - (((internal_counter_ - SECOND_PHASE_TIME) - 5) * ((internal_counter_ - SECOND_PHASE_TIME) - 5))) / 20.f, 0, 0);
			}
			for (int i = 0; i < number_of_confettis; i++) {
				attack_polygons_[i]->base_model_.setToIdentity();
				attack_polygons_[i]->base_model_.rotate(-(internal_counter_ - SECOND_PHASE_TIME) * vitesse_rotation_, 0, 1, 0);
				attack_polygons_[i]->after_base_model_.setToIdentity();
				attack_polygons_[i]->after_base_model_.translate(pow((3 * (internal_counter_ - 20) - 20), trajectoires_confettis_Y_[i]), trajectoires_confettis_START_X_[i] + trajectoires_confettis_X_[i] * (3 * (internal_counter_ - 20) - 20), trajectoires_confettis_START_Z_[i] - 0.005 * ((3 * (internal_counter_ - 20) - 20) * (3 * (internal_counter_ - 20) - 20)));
			}

			cone.rotate(90, 0, 1, 0);
			cylinder.rotate(90, 0, 1, 0);
			cone.translate(-5.f, 0, -5.f);
			cylinder.translate(-5.f, 0, -5.f);

			plane.translate(0, 0, 1.5f);
			tube.translate(0, 0, 1.5f);
			ball.translate(0, 0, 1.5f);

		}
		else if (internal_counter_ < FOURTH_PHASE_TIME)
		{
			cone.rotate(90 * ((FOURTH_PHASE_TIME - (float)internal_counter_) / 15.f), 0, 1, 0);
			cylinder.rotate(90 * ((FOURTH_PHASE_TIME - (float)internal_counter_) / 15.f), 0, 1, 0);
			cone.translate(-5.f * ((FOURTH_PHASE_TIME - (float)internal_counter_) / 15.f), 0, -5.f * ((FOURTH_PHASE_TIME - (float)internal_counter_) / 15.f));
			cylinder.translate(-5.f * ((FOURTH_PHASE_TIME - (float)internal_counter_) / 15.f), 0, -5.f * ((FOURTH_PHASE_TIME - (float)internal_counter_) / 15.f));

			plane.translate(0, 0, 1.5f);
			tube.translate(0, 0, 1.5f);
			ball.translate(0, 0, 1.5f);
		}
		else {
			plane.translate(0, 0, (LAST_PHASE_TIME - internal_counter_) / 4.f);
			tube.translate(0, 0, (LAST_PHASE_TIME - internal_counter_) / 4.f);
			ball.translate(0, 0, (LAST_PHASE_TIME - internal_counter_) / 4.f);
		}
	}
	else
	{
		animation_is_finished_ = true;
	}

	polygons_[0]->after_base_model_ = cone;
	polygons_[1]->after_base_model_ = cylinder;
	polygons_[2]->after_base_model_ = ball;
	polygons_[3]->after_base_model_ = tube;
	polygons_[4]->after_base_model_ = plane;

}

void GlaceFraise::resetPolygonsModels()
{
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_.setToIdentity();
	}
}

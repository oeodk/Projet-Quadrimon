#include "quadrimon/CylindrusTexture.h"

static constexpr float HEIGHT = 4;
static constexpr float WIDTH = 8;
static constexpr int SECTION = 10;
static constexpr float HEIGHT_SECTION = HEIGHT / SECTION;
static constexpr float WIDTH_SECTION = WIDTH / SECTION;
static constexpr float HEIGHT_START = -HEIGHT / 2.f;
static constexpr float WIDTH_START = -WIDTH / 2.f;
static constexpr float INCLINASON = 30.f;
static constexpr float BASE_HEIGHT = 4;
static constexpr unsigned int PARTICLE_NUM = 30;
static constexpr unsigned int PARTICLE_PACK = 4;


CylindrusTexture::CylindrusTexture(E_Player::e_Player trainer)
	: Quadrimon(trainer)
{
	name_ = E_QuadrimonName::CYLINDRUS_LE_TEXTURE;
	type_ = E_QuadrimonType::WATER;
	base_type_ = E_QuadrimonType::WATER;
	damage_ = 50;
	life_point_ = 700;

	polygons_.push_back(new DynamicOpenGlPolygon(&player_side_model_));
	
	polygons_.back()->vertices_.reserve((SECTION + 1) * (SECTION + 1));
	base_wing_vert_.reserve((SECTION + 1) * (SECTION + 1));
	polygons_.back()->indices_.reserve(6 * SECTION * SECTION);
	// y = 0.1x²
	for (int i = 0; i < SECTION + 1; i++)
	{
		for (int j = 0; j < SECTION + 1; j++)
		{
			const bdm::Vector3f position(0.1 * (WIDTH_START + i * WIDTH_SECTION) * (WIDTH_START + i * WIDTH_SECTION), WIDTH_START + i * WIDTH_SECTION, HEIGHT_START + j * HEIGHT_SECTION);
			bdm::Vector3f z_axis_normal(0, 0, 1);
			if (position.y < 0)
			{
				z_axis_normal.z = -1;
			}
			bdm::Vector3f normals(bdm::crossProduct(bdm::Vector3f(-position.y * (0.2), -position.y, 0), z_axis_normal));
			if (position.y == 0)
			{
				normals.set(-1, 0, 0);
			}
			normals.normalize();
			base_wing_vert_.push_back(SmallVertex(position, normals));
			polygons_.back()->vertices_.push_back(Vertex(position, normals, bdm::Vector2f(j / static_cast<float>(SECTION), i / static_cast<float>(SECTION))));
		}
	}
	for (int i = 0; i < SECTION; i++)
	{
		for (int j = 0; j < SECTION; j++)
		{
			int current = i * (SECTION + 1) + j;
			int next = current + (SECTION + 1);
			polygons_.back()->indices_.push_back(current);
			polygons_.back()->indices_.push_back(next);
			polygons_.back()->indices_.push_back(current + 1);

			polygons_.back()->indices_.push_back(next);
			polygons_.back()->indices_.push_back(next + 1);
			polygons_.back()->indices_.push_back(current + 1);
		}
	}

	polygons_.back()->initializeBuffers();
	polygons_.back()->base_model_.translate(0, 0, BASE_HEIGHT);
	polygons_.back()->base_model_.rotate(INCLINASON, 0, 1, 0);
	polygons_.back()->loadTexture("./assets/textures/quadrimon/cynlindrus_text.png");


	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(HEIGHT - 1, 0.75, 20, polygons_.back()->vertices_, polygons_.back()->indices_);
	polygons_.back()->base_model_.translate(0.01, 0, BASE_HEIGHT);
	polygons_.back()->base_model_.rotate(INCLINASON, 0, 1, 0);
	polygons_.back()->base_model_.translate(0.75, 0, 0);
	polygons_.back()->color_.set(0, 0, 1);
	polygons_.back()->opengl_primitive_ = GL_LINE_LOOP;
	polygons_.back()->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(HEIGHT - 2, 0.5, 20, polygons_.back()->vertices_, polygons_.back()->indices_, 0.5);
	polygons_.back()->base_model_.translate(0.2, 0, BASE_HEIGHT);
	polygons_.back()->base_model_.rotate(INCLINASON, 0, 1, 0);
	polygons_.back()->base_model_.translate(2, 3.7, 0);
	polygons_.back()->base_model_.rotate(150, 0, 0, 1);
	polygons_.back()->loadTexture("./assets/textures/quadrimon/cynlindrus_lines.png");

	polygons_.back()->initializeBuffers();

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	createCylinder(HEIGHT - 2, 0.5, 20, polygons_.back()->vertices_, polygons_.back()->indices_, 0.5);
	polygons_.back()->base_model_.translate(0.2, 0, BASE_HEIGHT);
	polygons_.back()->base_model_.rotate(INCLINASON, 0, 1, 0);
	polygons_.back()->base_model_.translate(2, -3.7, 0);
	polygons_.back()->loadTexture("./assets/textures/quadrimon/cynlindrus_checker.png");

	polygons_.back()->base_model_.rotate(30, 0, 0, 1);

	polygons_.back()->initializeBuffers();
	constexpr float COLOR_VALUE = 75;
	const std::array<bdm::Vector4f, 4> colors = { bdm::Vector4f(0, COLOR_VALUE, COLOR_VALUE, 0.1),bdm::Vector4f(COLOR_VALUE, 0, COLOR_VALUE, 0.1) ,bdm::Vector4f(COLOR_VALUE, COLOR_VALUE, 0, 0.1) ,bdm::Vector4f(0, 0, COLOR_VALUE, 0.1) };
	for (int k = 0; k < 4; k++)
	{
		attack_polygons_.push_back(new DynamicOpenGlPolygon(&player_side_model_));
		attack_polygons_.back()->material_.diffuse.set(0, 0, 0);
		attack_polygons_.back()->material_.ambient.set(1, 1, 1);
		attack_polygons_.back()->color_.set(colors[k]);
		attack_polygons_.back()->vertices_.reserve(PARTICLE_NUM * PARTICLE_PACK);
		attack_polygons_.back()->indices_.reserve(PARTICLE_NUM * PARTICLE_PACK);
		particle_theta_angle_[k].reserve(PARTICLE_NUM * PARTICLE_PACK);
		particle_phi_angle_[k].reserve(PARTICLE_NUM * PARTICLE_PACK);
		for (int i = 0; i < PARTICLE_PACK; i++)
		{
			for (int j = 0; j < PARTICLE_NUM; j++)
			{
				attack_polygons_.back()->vertices_.push_back(Vertex(0, 0.7 * (1 - 2 * (i % 2)), 0));
				attack_polygons_.back()->indices_.push_back(PARTICLE_NUM * i + j);
				particle_theta_angle_[k].push_back(M_PI * (rand() % 50 - 25) / 180.f);//vertical dispersion
				particle_phi_angle_[k].push_back(M_PI * (rand() % 90 - 45) / 180.f);//horizontal dispersion
			}
		}
		attack_polygons_.back()->base_model_.translate(0, 0, BASE_HEIGHT - 0.5);
		attack_polygons_.back()->opengl_primitive_ = GL_POINTS;
		attack_polygons_.back()->initializeBuffers();
	}
	setPolygonScaleToZero();
	initDisplayedPolygon();
}

void CylindrusTexture::resetPolygonsModels()
{
	Quadrimon::resetPolygonsModels();
	for (int i = 0; i < polygons_[0]->vertices_.size(); i++)
	{
		polygons_[0]->vertices_[i].position = base_wing_vert_[i].position;
		polygons_[0]->vertices_[i].normal = base_wing_vert_[i].normal;
	}
	dynamic_cast<DynamicOpenGlPolygon*>(polygons_[0])->refresh = true;
}

void CylindrusTexture::waitingAnimation()
{
	constexpr float PI_2 = 2 *  M_PI;
	constexpr float DURRATION = 30.f;
	flapWings(PI_2, DURRATION);
	
	const float MOD = 2 * std::sin(PI_2 * (internal_counter_ / DURRATION));
	polygons_[2]->before_base_model_.setToIdentity();
	polygons_[2]->before_base_model_.translate(MOD * COS_ANGLE_P2_, MOD * SIN_ANGLE_P2_, 0);
	polygons_[2]->before_base_model_.rotate(360 * std::sin(PI_2 * (internal_counter_ / DURRATION)), 0, 0, 1);
	polygons_[3]->before_base_model_.setToIdentity();
	polygons_[3]->before_base_model_.translate(MOD * COS_ANGLE_P3_, MOD * SIN_ANGLE_P3_, 0);
	polygons_[3]->before_base_model_.rotate(360 * std::sin(PI_2 * (internal_counter_ / DURRATION)), 0, 0, 1);
	QMatrix4x4 transformation;
	transformation.translate(0, 0, MOD / 2.f);
	for (auto& polygon : polygons_)
	{
		polygon->after_base_model_ = transformation;
	}
}

void CylindrusTexture::flapWings(const float& PI_2, const float& DURRATION)
{
	for (int i = 0; i < SECTION + 1; i++)
	{
		const float dep = std::pow(((WIDTH_START + i * WIDTH_SECTION) / 4.f), 2) * std::sin(PI_2 * (internal_counter_ / DURRATION));

		for (int j = 0; j < SECTION + 1; j++)
		{
			// y = 0.1x² + (x/4)² * sin(2PI * (t / 45));
			polygons_[0]->vertices_[i * (SECTION + 1) + j].position.x = base_wing_vert_[i * (SECTION + 1) + j].position.x + 2 * dep;
			bdm::Vector3f z_axis_normal(0, 0, 1);
			const bdm::Vector3f& position = polygons_[0]->vertices_[i * (SECTION + 1) + j].position;
			if (position.y < 0)
			{
				z_axis_normal.z = -1;
			}
			bdm::Vector3f normals(bdm::crossProduct(bdm::Vector3f(-position.y * (0.2) + (position.y / 8.f) * std::sin(PI_2 * (internal_counter_ / DURRATION)), -position.y, 0), z_axis_normal));
			if (position.y == 0)
			{
				normals.set(-1, 0, 0);
			}
			normals.normalize();
			polygons_[0]->vertices_[i * (SECTION + 1) + j].normal.set(normals);
		}
	}
	dynamic_cast<DynamicOpenGlPolygon*>(polygons_[0])->refresh = true;
}

void CylindrusTexture::attackingAnimation()
{
	constexpr float FIRST_PHASE_TIME = 5.f;
	constexpr float SECOND_PHASE_TIME = 60.f;
	if (internal_counter_ < FIRST_PHASE_TIME)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		const float CURRENT_RATIO = internal_counter_ / FIRST_PHASE_TIME;
		QMatrix4x4 transformation;
		transformation.rotate(-INCLINASON * CURRENT_RATIO, 0, 1, 0);
		for (auto& polygon : polygons_)
		{
			polygon->after_base_model_ = transformation;
		}
		polygons_[2]->before_base_model_.setToIdentity();
		polygons_[2]->after_base_model_.translate(0, -3 * CURRENT_RATIO, 0);
		polygons_[2]->before_base_model_.rotate(-60 * CURRENT_RATIO, 0, 0, 1);
		polygons_[3]->before_base_model_.setToIdentity();
		polygons_[3]->after_base_model_.translate(0, 3 * CURRENT_RATIO, 0);
		polygons_[3]->before_base_model_.rotate(60 * CURRENT_RATIO, 0, 0, 1);
	}
	else
	{
		if (internal_counter_ < FIRST_PHASE_TIME + SECOND_PHASE_TIME)
		{
			if (internal_counter_ == FIRST_PHASE_TIME)
			{
				QMatrix4x4 transformation;
				transformation.rotate(-INCLINASON, 0, 1, 0);
				for (auto& polygon : polygons_)
				{
					polygon->after_base_model_ = transformation;
				}
				polygons_[2]->before_base_model_.setToIdentity();
				polygons_[2]->after_base_model_.translate(0, -3, 0);
				polygons_[2]->before_base_model_.rotate(-60, 0, 0, 1);
				polygons_[3]->before_base_model_.setToIdentity();
				polygons_[3]->after_base_model_.translate(0, 3, 0);
				polygons_[3]->before_base_model_.rotate(60, 0, 0, 1);
				for (int k = 0; k < 4; k++)
				{
					for (int i = 0; i < PARTICLE_PACK; i++)
					{
						for (int j = 0; j < PARTICLE_NUM; j++)
						{
							attack_polygons_[k]->vertices_[i * PARTICLE_NUM + j].position.set(0, 0.7 * (1 - 2 * (i % 2)), 0);
						}
					}
					displayed_polygons_.push_back(attack_polygons_[k]);
				}
				refresh_displayed_polygons_ = true;
			}
			constexpr float PI_2 = 2 * M_PI;
			constexpr float DURRATION = 5.f;
			constexpr float STEP = 0.5f;
			for (int k = 0; k < 4; k++)
			{
				for (int i = 0; i < 30; i++)
				{
					if (i < (internal_counter_ - FIRST_PHASE_TIME) + 1)
					{
						for (int j = 0; j < PARTICLE_PACK; j++)
						{
							if (i < (internal_counter_ - FIRST_PHASE_TIME) - SECOND_PHASE_TIME / 2.f)
							{
								attack_polygons_[k]->vertices_[i + j * PARTICLE_NUM].position.z = -5;
							}
							else
							{
								attack_polygons_[k]->vertices_[i + j * PARTICLE_NUM].position.x = attack_polygons_[k]->vertices_[i + j * PARTICLE_NUM].position.x + STEP * cos(particle_theta_angle_[k][i + j * PARTICLE_NUM]);
								attack_polygons_[k]->vertices_[i + j * PARTICLE_NUM].position.y = attack_polygons_[k]->vertices_[i + j * PARTICLE_NUM].position.y + STEP * sin(particle_theta_angle_[k][i + j * PARTICLE_NUM]) * sin(particle_phi_angle_[k][i + j * PARTICLE_NUM]);
								attack_polygons_[k]->vertices_[i + j * PARTICLE_NUM].position.z = attack_polygons_[k]->vertices_[i + j * PARTICLE_NUM].position.z + STEP * sin(particle_theta_angle_[k][i + j * PARTICLE_NUM]) * cos(particle_phi_angle_[k][i + j * PARTICLE_NUM]);
							}
						}
					}
				}
				dynamic_cast<DynamicOpenGlPolygon*>(attack_polygons_[k])->refresh = true;
			}
			flapWings(PI_2, DURRATION);
		}
		else
		{
			if (internal_counter_ < 2 * FIRST_PHASE_TIME + SECOND_PHASE_TIME + 1)
			{
				if (internal_counter_ == FIRST_PHASE_TIME + SECOND_PHASE_TIME)
				{
					displayed_polygons_.clear();
					initDisplayedPolygon();
					refresh_displayed_polygons_ = true;
					for (int i = 0; i < polygons_[0]->vertices_.size(); i++)
					{
						polygons_[0]->vertices_[i].position = base_wing_vert_[i].position;
						polygons_[0]->vertices_[i].normal = base_wing_vert_[i].normal;
					}
					dynamic_cast<DynamicOpenGlPolygon*>(polygons_[0])->refresh = true;
				}
				QMatrix4x4 transformation;
				const float CURRENT_RATIO = 1 - ((internal_counter_ - (FIRST_PHASE_TIME + SECOND_PHASE_TIME)) / FIRST_PHASE_TIME);
				transformation.rotate(-INCLINASON * CURRENT_RATIO, 0, 1, 0);
				for (auto& polygon : polygons_)
				{
					polygon->after_base_model_ = transformation;
				}
				polygons_[2]->before_base_model_.setToIdentity();
				polygons_[2]->after_base_model_.translate(0, -3 * CURRENT_RATIO, 0);
				polygons_[2]->before_base_model_.rotate(-60 * CURRENT_RATIO, 0, 0, 1);
				polygons_[3]->before_base_model_.setToIdentity();
				polygons_[3]->after_base_model_.translate(0, 3 * CURRENT_RATIO, 0);
				polygons_[3]->before_base_model_.rotate(60 * CURRENT_RATIO, 0, 0, 1);
			}
			else
			{
				animation_is_finished_ = true;
			}
		}
	}
}

void CylindrusTexture::takingDamageAnimation()
{
	if (internal_counter_ < 15)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		for (int i = 0; i < polygons_.size(); i++)
		{
			polygons_[i]->color_.set(1 + 5 * std::sin((2 * M_PI / 30) * internal_counter_), 1, 1);
		}
		polygons_[1]->color_.set(1 + 5 * std::sin((2 * M_PI / 30) * internal_counter_), 0, 1);
	}
	else
	{
		for (int i = 0; i < polygons_.size(); i++)
		{
			polygons_[i]->color_.set(1, 1, 1);
		}
		polygons_[1]->color_.set(0, 0, 1);
		animation_is_finished_ = true;
	}
}

void CylindrusTexture::dyingAnimation()
{
	if (internal_counter_ < 45)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
			primitive_displayed_ = false;
			for(int i = 0;i<polygons_.size();i++)
			{
				polygons_[i]->material_.ambient.set(1, 1, 1);
			}

		}
		switch (internal_counter_ / 15)
		{
		case 0:
			if ((internal_counter_ - 15) % 5 == 0)
			{
				invertPrimitives();
			}
			break;
		case 1:
			if ((internal_counter_ - 15) % 3 == 0)
			{
				invertPrimitives();
			}
			break;
		case 2:
			invertPrimitives();
			break;
		}
		if (internal_counter_ > 29)
		{
			QMatrix4x4 transformation;
			transformation.scale(1 - (internal_counter_ - 30) / 15.f);
			for (auto& polygon : polygons_)
			{
				polygon->after_base_model_ = transformation;
			}
		}
	}
	else
	{
		if (internal_counter_ == 45)
		{
			polygons_[0]->opengl_primitive_ = GL_POINTS;
			polygons_[1]->opengl_primitive_ = GL_POINTS;
			polygons_[2]->opengl_primitive_ = GL_POINTS;
			polygons_[3]->opengl_primitive_ = GL_POINTS;
			QMatrix4x4 transformation;
			transformation.scale(0);
			for (auto& polygon : polygons_)
			{
				polygon->after_base_model_ = transformation;
			}
		}
		animation_is_finished_ = true;
	}
}


void CylindrusTexture::invertPrimitives()
{
	if (primitive_displayed_)
	{
		polygons_[0]->opengl_primitive_ = GL_LINES;
		polygons_[1]->opengl_primitive_ = GL_TRIANGLES;
		polygons_[2]->opengl_primitive_ = GL_LINES;
		polygons_[3]->opengl_primitive_ = GL_LINES;
	}
	else
	{
		polygons_[0]->opengl_primitive_ = GL_TRIANGLES;
		polygons_[1]->opengl_primitive_ = GL_LINES;
		polygons_[2]->opengl_primitive_ = GL_TRIANGLES;
		polygons_[3]->opengl_primitive_ = GL_TRIANGLES;
	}
	polygons_[0]->color_ += 10;
	polygons_[1]->color_.z += 10;
	polygons_[2]->color_ += 10;
	polygons_[3]->color_ += 10;
	primitive_displayed_ = !primitive_displayed_;
}
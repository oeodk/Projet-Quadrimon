#include "quadrimon/SaladierMystique.h"
#include "Game.h"

SaladierMystique::SaladierMystique(E_Player::e_Player trainer)
	: Quadrimon(trainer)
{
	cloned_quadrimon_ = nullptr;
	name_ = E_QuadrimonName::SALADIER_MYSTIQUE;
	type_ = E_QuadrimonType::GRASS;
	base_type_ = E_QuadrimonType::GRASS;
	damage_ = 100;
	life_point_ = 800;

	reverse_transformation_ = 0;
	constexpr int SEGMENT = 20;
	constexpr float PROPORTION = 0.5;

	polygons_.push_back(new OpenGlPolygon(&player_side_model_));
	polygons_[0]->vertices_.reserve(2 * ((SEGMENT + 1) * int(SEGMENT * PROPORTION + 1)));
	polygons_[0]->indices_.reserve(2 * (6 * SEGMENT * int(SEGMENT * PROPORTION)) + SEGMENT * 12);
	createSphere(2.25, SEGMENT, polygons_[0]->vertices_, polygons_[0]->indices_, PROPORTION);
	std::vector<Vertex> tmp_vertices;
	std::vector<unsigned int> tmp_indices;
	createSphere(2, SEGMENT, tmp_vertices, tmp_indices, PROPORTION);
	polygons_[0]->vertices_.insert(polygons_[0]->vertices_.end(), std::make_move_iterator(tmp_vertices.begin()), std::make_move_iterator(tmp_vertices.end()));
	const int VERTICES_SIZE = tmp_vertices.size();
	const int VERTICES_FINAL_SIZE = polygons_[0]->vertices_.size();
	for (int i = 0; i < tmp_indices.size(); i++)
	{
		polygons_[0]->indices_.push_back(VERTICES_SIZE + tmp_indices[i]);
	}
	constexpr int OTHER_HALF = int(SEGMENT * PROPORTION + 1);
	for (int i = 0; i < SEGMENT + 1 ; i++)
	{	
		for (int j = 0; j < 2; j++)
		{
			polygons_[0]->indices_.push_back(j * (VERTICES_SIZE - 1) + (1 - 2 * j) * int(SEGMENT * PROPORTION + 1) * i);
			polygons_[0]->indices_.push_back(j * (VERTICES_SIZE - 1) + (1 - 2 * j) * int(SEGMENT * PROPORTION + 1) * (i + 1));
			polygons_[0]->indices_.push_back(j * (VERTICES_FINAL_SIZE - 1) + (1 - j) * VERTICES_SIZE + (1 - 2 * j) * int(SEGMENT * PROPORTION + 1) * i);

			polygons_[0]->indices_.push_back(j * (VERTICES_SIZE - 1) + (1 - 2 * j) * int(SEGMENT * PROPORTION + 1) * (i + 1));
			polygons_[0]->indices_.push_back(j * (VERTICES_FINAL_SIZE - 1) + (1 - j) * VERTICES_SIZE + (1 - 2 * j) * int(SEGMENT * PROPORTION + 1) * i);
			polygons_[0]->indices_.push_back(j * (VERTICES_FINAL_SIZE - 1) + (1 - j) * VERTICES_SIZE + (1 - 2 * j) * int(SEGMENT * PROPORTION + 1) * (i + 1));
		}
	}
		
	polygons_[0]->initializeBuffers();
	polygons_[0]->color_.set(0.8, 0.8, 0.8, 0.6);
	polygons_[0]->base_model_.translate(0, 0, 2.5);
	polygons_[0]->base_model_.rotate(-90, 1, 0, 0);
	polygons_[0]->base_model_.rotate(-15, 1, 0, 0);

	setPolygonScaleToZero();
	initDisplayedPolygon();
}

SaladierMystique::~SaladierMystique()
{
	if (cloned_quadrimon_ != nullptr)
	{
		delete cloned_quadrimon_;
	}
}


void SaladierMystique::refreshDisplayFromClone()
{
	displayed_polygons_.clear();
	std::vector<OpenGlPolygon*>* clone_polygon = cloned_quadrimon_->getPolygons();
	for (int i = 0; i < clone_polygon->size(); i++)
	{
		displayed_polygons_.push_back(clone_polygon->at(i));
	}
	refresh_displayed_polygons_ = true;
}

void SaladierMystique::takingDamageAnimation()
{
	if (internal_counter_ < 15)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		polygons_[0]->color_.set(1 + std::sin((2 * M_PI / 30) * internal_counter_), 0.8, 0.8, 0.6);
	}
	else
	{
		polygons_[0]->color_.set(0.8, 0.8, 0.8, 0.6);
		animation_is_finished_ = true;
	}

}

void SaladierMystique::attackingAnimation()
{
	if (cloned_quadrimon_ != nullptr)
	{
		if (cloned_quadrimon_->getName() != E_QuadrimonName::SALADIER_MYSTIQUE)
		{
			constexpr int TRANSFORMATION_DURATION = 30;
			if (internal_counter_ < TRANSFORMATION_DURATION)
			{
				if (internal_counter_ == 0)
				{
					animation_is_finished_ = false;
					displayed_polygons_.clear();
					displayed_polygons_.push_back(attack_polygons_[0]);
					refresh_displayed_polygons_ = true;
					reverse_transformation_ = 0;
				}
				for (int i = 0; i < attack_polygons_[0]->vertices_.size(); i++)
				{
					const float factor = internal_counter_ / float(TRANSFORMATION_DURATION);
					attack_polygons_[0]->vertices_[i] = (target_vert_[i] * factor + start_vert_[i] * (1 - factor));
				}
				dynamic_cast<DynamicOpenGlPolygon*>(attack_polygons_[0])->refresh = true;
			}
			else
			{
				if (internal_counter_ == TRANSFORMATION_DURATION)
				{
					refreshDisplayFromClone();
					cloned_quadrimon_->setState(E_QuadrimonState::ATTACKING);
				}
				cloned_quadrimon_->update();
				if (cloned_quadrimon_->getRefreshDisplayedPolygons())
				{
					refreshDisplayFromClone();
				}
				if (cloned_quadrimon_->animationIsFinished())
				{
					if (reverse_transformation_ == 0)
					{
						cloned_quadrimon_->setState(E_QuadrimonState::WAITING);
						displayed_polygons_.clear();
						displayed_polygons_.push_back(attack_polygons_[1]);
						refresh_displayed_polygons_ = true;
					}
					for (int i = 0; i < attack_polygons_[1]->vertices_.size(); i++)
					{
						const float factor = reverse_transformation_ / float(TRANSFORMATION_DURATION);
						attack_polygons_[1]->vertices_[i] = (target_vert_[i] * (1 - factor) + start_vert_[i] * factor);
					}
					dynamic_cast<DynamicOpenGlPolygon*>(attack_polygons_[1])->refresh = true;

					reverse_transformation_++;
					if(reverse_transformation_ == TRANSFORMATION_DURATION)
					{
						animation_is_finished_ = true;
						displayed_polygons_.clear();
						initDisplayedPolygon();
						refresh_displayed_polygons_ = true;
					}
				}
			}
		}
		else
		{
			Quadrimon::attackingAnimation();
		}
	}
	else
	{
		animation_is_finished_ = true;
	}
}

void SaladierMystique::dyingAnimation()
{
	if (internal_counter_ < 15)
	{
		if (internal_counter_ == 0)
		{
			animation_is_finished_ = false;
		}
		polygons_[0]->color_.set(0.8, 0.8, 0.8, 0.5 + 0.5 * std::sin(2 * M_PI * (internal_counter_ / 20.f)));
		polygons_[0]->before_base_model_.setToIdentity();
		if (internal_counter_ < 5)
		{
			polygons_[0]->before_base_model_.scale((10 - internal_counter_) / 10.f);
		}
		else
		{
			polygons_[0]->before_base_model_.scale(0.5 + 2 * ((internal_counter_ - 5) / 10.f));
		}
	}
	else
	{
		animation_is_finished_ = true;
	}
}

void SaladierMystique::update(E_QuadrimonName::e_QuadrimonName opponent_quadrimon)
{
	if (cloned_quadrimon_ == nullptr || cloned_quadrimon_->getName() != opponent_quadrimon)
	{
		if (cloned_quadrimon_ != nullptr)
		{
			delete cloned_quadrimon_;
			target_vert_.clear();
			start_vert_.clear();
		}
		cloned_quadrimon_ = Game::generateQuadrimon(opponent_quadrimon, trainer_);
		if(cloned_quadrimon_->getName() != E_QuadrimonName::SALADIER_MYSTIQUE)
		{
			if (attack_polygons_.size() != 0)
			{
				for (int i = 0; i < attack_polygons_.size(); i++)
				{
					delete attack_polygons_[i];
				}
				attack_polygons_.clear();
			}
			attack_polygons_.push_back(new DynamicOpenGlPolygon(&player_side_model_));
			attack_polygons_.push_back(new DynamicOpenGlPolygon(&player_side_model_));
			attack_polygons_[0]->color_.set(1, 1, 1, 0.6);
			attack_polygons_[1]->color_.set(1, 1, 1, 0.6);
			attack_polygons_[0]->material_.ambient.set(11,11,11);
			attack_polygons_[1]->material_.ambient.set(11,11,11);
			attack_polygons_[0]->material_.diffuse.set(0, 0, 0);
			attack_polygons_[1]->material_.diffuse.set(0, 0, 0);
			int clone_vertex_total = 0;
			int clone_index_total = 0;
			const std::vector<OpenGlPolygon*>* clone_polygon = cloned_quadrimon_->getPolygons();
			for (auto& polygon : *clone_polygon)
			{
				polygon->after_base_model_.setToIdentity();
				clone_vertex_total += polygon->vertices_.size();
				clone_index_total += polygon->indices_.size();
			}
			attack_polygons_[0]->vertices_.reserve(clone_vertex_total);
			attack_polygons_[1]->vertices_.reserve(polygons_[0]->vertices_.size());
			if (clone_vertex_total > polygons_[0]->vertices_.size())
			{
				target_vert_.reserve(clone_vertex_total);
				start_vert_.reserve(clone_vertex_total);
			}
			else
			{
				target_vert_.reserve(polygons_[0]->vertices_.size());
				start_vert_.reserve(polygons_[0]->vertices_.size());
			}
			attack_polygons_[0]->indices_.reserve(clone_index_total); 
			attack_polygons_[1]->indices_.reserve(polygons_[0]->indices_.size());
			
			for (const auto& polygon : *clone_polygon)
			{
				for (int i = 0; i < polygon->vertices_.size(); i++)
				{
					attack_polygons_[0]->vertices_.push_back(Vertex());
					target_vert_.push_back(polygon->base_model_ * polygon->vertices_[i]);
					if (start_vert_.size() < polygons_[0]->vertices_.size())
					{
						start_vert_.push_back(polygons_[0]->base_model_ * polygons_[0]->vertices_[start_vert_.size()]);
					}
					else
					{
						start_vert_.push_back(SmallVertex());
					}
				}
				const int CURRENT_INDEX = attack_polygons_[0]->indices_.size();
				for (int i = 0; i < polygon->indices_.size(); i++)
				{
					attack_polygons_[0]->indices_.push_back(CURRENT_INDEX + polygon->indices_[i]);
				}
			}
			while (target_vert_.size() < polygons_[0]->vertices_.size())
			{
				target_vert_.push_back(Vertex());
				start_vert_.push_back(polygons_[0]->base_model_ * polygons_[0]->vertices_[start_vert_.size()]);
			}
			for (int i = 0; i < polygons_[0]->vertices_.size(); i++)
			{
				attack_polygons_[1]->vertices_.push_back(Vertex());
			}
			for (int i = 0; i < polygons_[0]->indices_.size(); i++)
			{
				attack_polygons_[1]->indices_.push_back(polygons_[0]->indices_[i]);
			}
			attack_polygons_[0]->initializeBuffers();
			attack_polygons_[1]->initializeBuffers();
		}
	}
	Quadrimon::update();
}


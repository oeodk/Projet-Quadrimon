#include "utility/CardDisplay.h"


void CardDisplay::init(const QMatrix4x4* player_model, int side_sign)
{
	card_polygons_ = new OpenGlPolygon(player_model);
	createRectangle(0.3, 0.7, card_polygons_->vertices_, card_polygons_->indices_);
	card_polygons_->initializeBuffers();
	position_.set(side_sign * 0.351, -1, 0.5);
	card_polygons_->after_base_model_.translate(position_);
	card_polygons_->base_model_.rotate(180, 0, 0, 1);
	card_polygons_->base_model_.scale(-1, 1, 1);
	side_sign_ = side_sign;
	card_animation_counter_ = 0;
	display_ = false;
	card_state_ = E_OverlayCardState::HIDDED;
}

void CardDisplay::moveDep()
{
	position_ += dep_;
	card_polygons_->after_base_model_.setToIdentity();
	card_polygons_->after_base_model_.translate(position_);
}


void CardDisplay::update()
{
	switch (card_state_)
	{
	case E_OverlayCardState::APPEARING:
		if (card_animation_counter_ < 10)
		{
			if (card_animation_counter_ == 0)
			{
				position_.y = -1.35;
				dep_.set(0, 0.035, 0);
			}
			moveDep();
		}
		else
		{
			card_state_ = E_OverlayCardState::WAITING;
		}
		break;
	case E_OverlayCardState::PLAYING:
		if (card_animation_counter_ < 20)
		{
			if (card_animation_counter_ == 0)
			{
				dep_ = (bdm::Vector3f(side_sign_ * 0.5, 0, 0.5) - position_) / 10.f;
			}
			if (card_animation_counter_ < 10)
			{
				moveDep();
			}
			else
			{
				card_polygons_->before_base_model_.setToIdentity();
				card_polygons_->before_base_model_.rotate(360 * ((card_animation_counter_ - 10) / 10.f), 0, 1, 0);
			}
		}
		else
		{
			card_polygons_->before_base_model_.setToIdentity();
			card_state_ = E_OverlayCardState::DISAPPEARING;
			card_animation_counter_ = -1;
		}
		break;
	case E_OverlayCardState::SLIDING_SIDE:
		if (card_animation_counter_ < 10)
		{
			if (card_animation_counter_ == 0)
			{
				dep_ = (bdm::Vector3f(side_sign_ * 0.66, -1, 0.5) - position_) / 10.f;
			}
			moveDep();
		}
		else
		{
			card_state_ = E_OverlayCardState::WAITING;
		}
		break;
	case E_OverlayCardState::SLIDING_CENTER:
		if (card_animation_counter_ < 10)
		{
			if (card_animation_counter_ == 0)
			{
				dep_ = (bdm::Vector3f(side_sign_ * 0.351, -1, 0.5) - position_) / 10.f;
			}
			moveDep();
		}
		else
		{
			card_state_ = E_OverlayCardState::WAITING;
		}
		break;
	case E_OverlayCardState::DISAPPEARING:
		if (card_animation_counter_ < 11)
		{
			card_polygons_->color_.t = 1 - (card_animation_counter_ / 10.f);
		}
		else
		{
			card_state_ = E_OverlayCardState::HIDDED;
		}
		break;
	case E_OverlayCardState::DISCARDING:
		if (card_animation_counter_ < 10)
		{
			position_.y -= 0.035;
			card_polygons_->after_base_model_.setToIdentity();
			card_polygons_->after_base_model_.translate(position_);
		}
		else
		{
			card_state_ = E_OverlayCardState::HIDDED;
		}
		break;
	case E_OverlayCardState::HIDDED:
		display_ = false;
		refresh_display_ = true;
		resetCard();
		card_state_ = E_OverlayCardState::E_END;
		break;
	}
	card_animation_counter_++;
}

void CardDisplay::resetCard()
{
	card_polygons_->color_.t = 1;
	card_polygons_->before_base_model_.setToIdentity();
	position_.set(side_sign_ * 0.351, -1, 0.5);
	card_polygons_->after_base_model_.setToIdentity();
	card_polygons_->after_base_model_.translate(position_);
}

void CardDisplay::setImage(const std::string& path)
{
	card_polygons_->loadTexture(path);
	makeAppear();
}

void CardDisplay::makeAppear()
{
	card_animation_counter_ = 0;
	card_state_ = E_OverlayCardState::APPEARING;
	refresh_display_ = true;
	display_ = true;
	resetCard();
}

void CardDisplay::trigger()
{
	card_state_ = E_OverlayCardState::PLAYING;
	card_animation_counter_ = 0;
}

void CardDisplay::discard()
{
	card_state_ = E_OverlayCardState::DISCARDING;
	card_animation_counter_ = 0;
}

void CardDisplay::slideCenter()
{
	card_state_ = E_OverlayCardState::SLIDING_CENTER;
	card_animation_counter_ = 0;
}

void CardDisplay::slideSide()
{
	card_state_ = E_OverlayCardState::SLIDING_SIDE;
	card_animation_counter_ = 0;
}


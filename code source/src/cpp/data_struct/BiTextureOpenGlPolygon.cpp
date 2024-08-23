#include "data_struct/BiTextureOpenGlPolygon.h"

BiTextureOpenGlPolygon::BiTextureOpenGlPolygon(const QMatrix4x4* player_side_model)
	: OpenGlPolygon(player_side_model)
{
	has_second_texture_ = false;
	blend_factor_ = 0;
}

void BiTextureOpenGlPolygon::bindSecondTexture()
{
	if (has_second_texture_)
	{
		glBindTexture(GL_TEXTURE_2D, second_texture_location_);
	}
}

void BiTextureOpenGlPolygon::releaseSecondTexture()
{
	if (has_second_texture_)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void BiTextureOpenGlPolygon::loadSecondTexture(const std::string& filename, int interpolation_type)
{
	if (has_second_texture_ == true)
	{
		glDeleteTextures(1, &second_texture_location_);
	}
	QImage image;
	if (!loadImage(image, filename))
	{
		return;
	}
	has_second_texture_ = true;
	glGenTextures(1, &second_texture_location_);
	loadTexture(image, second_texture_location_, interpolation_type);
}

void BiTextureOpenGlPolygon::deleteSecondTexture()
{
	if (has_second_texture_)
	{
		glDeleteTextures(1, &second_texture_location_);
		has_second_texture_ = false;
	}
}

#include "data_struct/OpenGlPolygon.h"
#include <QOpenGLContext>

OpenGlPolygon::OpenGlPolygon(const QMatrix4x4* player_side_model)
	: player_side_model_(player_side_model)
{
	initializeOpenGLFunctions();
	has_texture_ = false;
	has_transparent_texture_ = false;
	opengl_primitive_ = GL_TRIANGLES;
	after_base_model_.setToIdentity();
	before_base_model_.setToIdentity();
	base_model_.setToIdentity();
	color_.set(1, 1, 1, 1);
}

void OpenGlPolygon::initializeBuffers()
{
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER,vertices_.size() * sizeof(Vertex), vertices_.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &ebo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);

	// Attribute array for the coordinates of the vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
	// Attribute array for the normals of the vertices
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
	// Attribute array for the texture coords of the vertices
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texture_coords));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGlPolygon::bind()
{
	if (has_texture_)
	{
		glBindTexture(GL_TEXTURE_2D, texture_location_);
	}
	glBindVertexArray(vao_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
}
void OpenGlPolygon::release()
{
	if (has_texture_)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OpenGlPolygon::loadTexture(const std::string& filename, int interpolation_type)
{
	if (has_texture_ == true)
	{
		glDeleteTextures(1, &texture_location_);
	}
	QImage image;
	if (!loadImage(image, filename))
	{
		return;
	}
	has_texture_ = true;
	glGenTextures(1, &texture_location_);
	loadTexture(image, texture_location_, interpolation_type);
}

bool OpenGlPolygon::loadImage(QImage& image, const std::string filename)
{
	if (!image.load(filename.c_str()))
	{
		// Gestion de l'erreur si le chargement de l'image a échoué
		qDebug() << "Current folder " + QDir::currentPath();
		qDebug() << "Texture " + filename + " could not load";
		return false;
	}
	return true;
}

void OpenGlPolygon::loadTexture(QImage& image, int text_loc, int interpolation_type)
{
	// Conversion de l'image en format compatible OpenGL
	image = image.convertToFormat(QImage::Format_RGBA8888);

	glBindTexture(GL_TEXTURE_2D, text_loc);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, interpolation_type);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, interpolation_type);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
	glGenerateMipmap(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, 0);
}


void OpenGlPolygon::deleteTexture()
{
	if (has_texture_)
	{
		glDeleteTextures(1, &texture_location_);
		has_texture_ = false;
	}
}

OpenGlPolygon::~OpenGlPolygon()
{
	if (has_texture_)
	{
		glDeleteTextures(1, &texture_location_);
	}
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &ebo_);
	glDeleteVertexArrays(1, &vao_);
}


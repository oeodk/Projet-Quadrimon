#include "data_struct/DynamicOpenGlPolygon.h"

DynamicOpenGlPolygon::DynamicOpenGlPolygon(const QMatrix4x4* player_side_model)
	:OpenGlPolygon(player_side_model)
{
	refresh = true;
}

void DynamicOpenGlPolygon::initializeBuffers()
{
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

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

void DynamicOpenGlPolygon::bind()
{
	if (has_texture_)
	{
		glBindTexture(GL_TEXTURE_2D, texture_location_);
	}
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	if(refresh)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_.size() * sizeof(Vertex), vertices_.data());
		refresh = false;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
}

void DynamicOpenGlPolygon::release()
{
	if (has_texture_)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

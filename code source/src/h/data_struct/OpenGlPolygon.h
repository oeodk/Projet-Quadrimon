#pragma once
#include <qopenglfunctions_3_3_compatibility.h>
#include <QMatrix4x4>
#include <QImage>
#include <QDir>
#include <string>
#include <vector>
#include "data_struct/Material.h"
#include "data_struct/Vector4f.h"
#include "data_struct/Vertex.h"

/*
Ce struct contient toutes les variable nécessaire à la création d'un objet 3D
- Champs : 

Il contient deux vecteurs vertices_ contenant tous les points de l'objet 3D 
	et indices_ contenant_ l'ordre dans lequel utilisé ces points lors du tracé à l'écran

Les variables vao_, vbo_, ebo_ et texture_location_ sont des variables utilisées avec d'OpenGl
	vao_ : permet à OpenGl de savoir ce que contiennent les points des polygons
	vbo_ : est le buffer contenant les points du polygon (position, normales, mappage de la texture)
	ebo_ : est le buffer contenant l'ordre dans lequel utilisé ces points
	texture_location_ : est l'indice du buffer contenant la texture du polygon

Les variables after_base_model_, before_base_model_, base_model_ et player_side_model_ sont les matrices de 
	transformation appliqué au polygon
	base_model_ : représente la transformation appliqué pour positioner le polygon dans le model complet du quadrimon / terrain
	before_base_model_ : représente les transformation appliqués avant la transformation de base
	after_base_model_ : représente les transformation appliqués après la transformation de base
	player_side_model_ : représente les transformation appliqués pour positionner les polygons à droite ou a gauche de l'écran en fonction du joueur

La variable OpenGL_primitive_ représente la primitive utilisé pour dessiner le polygon (GL_TRIANGLES, GL_LINE_STRIP, GL_LINE_LOOP, ...) 
Les variables has_texture_, color_, material_ représente les modifications possible pour l'affichage du polygon
	has_texture_ : permet de savoir si le polygon possède une texture
	has_transparent_texture_ : permet de savoir si la texture du quadrimon a de la transparence 
	color_ : est la couleur du polygon
	material_ : est une struct possédant les valeurs de lumière ambiante, diffuse, spéculaire et la briance du matériaux

Struct réalisée par GONON Lucas
*/

struct OpenGlPolygon : protected QOpenGLFunctions_3_3_Compatibility
{
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	// OpenGl buffers locations
	unsigned int vao_;
	unsigned int vbo_;
	unsigned int ebo_;
	unsigned int texture_location_;
	
	// Transformation matrix applied to the polygon
	QMatrix4x4 after_base_model_;
	QMatrix4x4 before_base_model_;
	// Base transformation of the polygon in the quadrimon 3D model
	QMatrix4x4 base_model_;
	// Transformation applied for placing the polygon in the correct spot of the arena (ex : right p2, left p1)
	const QMatrix4x4* player_side_model_;
	// Primitive used when drawing the polygon (GL_TRIANGLES, GL_LINE_STRIP, GL_LINE_LOOP, ...) 
	int opengl_primitive_;

	bool has_texture_;
	bool has_transparent_texture_;
	bdm::Vector4f color_;
	Material material_;

	OpenGlPolygon(const QMatrix4x4* player_side_model);
	~OpenGlPolygon();

	/*
	R : Cette méthode retourne une matrice de transformation combinant toutes les transformation appliquées au polygon
	S : La matrice de transformation combiné du polygon
	*/
	QMatrix4x4 getCombineModel() { return (*player_side_model_) * after_base_model_ * base_model_ * before_base_model_; }
	
	/*
	R : Créé les buffers OpenGl contenant toute les données du polygon
	*/
	virtual void initializeBuffers();
	
	/*
	R : Lie les buffers du polygon au buffers actif
	*/
	virtual void bind();

	/*
	R : Libère les buffers actif
	*/
	virtual void release();

	/*
	R : Affecte une texture au polygon
	E : filename : le chemin vers la texture
		interpolation_type : la méthode d'interpolation utilisé
	*/
	void loadTexture(const std::string& filename, int interpolation_type = GL_LINEAR);

	/*
	R : Supprime la texture des buffers d'OpenGl
	*/
	void deleteTexture();
	
protected :
	/*
	R : Initialise une QImage a partir du chemin vers l'image
	E : image : l'image à modifier
		filename : le chemin vers l'image
	S : Un booléen valant vrai si l'image à été chargé et faux sinon
	*/
	bool loadImage(QImage& image, const std::string filename);
	/*
	R : Initialise le buffer contenant la texture
	E : image : l'image contenant les données de la texture
		text_loc : l'emplacement de la texture avec OpenGl
		interpolation_type : la méthode d'interpolation utilisé sur la texture
	*/
	void loadTexture(QImage& image, int text_loc, int interpolation_type);
};


#pragma once
#define _USE_MATH_DEFINES 
#include <cmath>
#include <QVector4D>
#include "data_struct/Vector3f.h"

/*
Ce struct représente un vecteur mathématique de 4 valeurs

- Champs :
	x, y, z, t : les 3 valeurs

Struct réalisée par GONON Lucas
*/

namespace bdm
{
	struct Vector4f
	{
		float x, y, z, t;

		Vector4f(float px = 0, float py = 0, float pz = 0, float pt = 0);
		Vector4f(Vector3f v, float pt = 0);
		
		/*
		R : normaliser le vecteur
		*/
		void normalize();

		/*
		R : Permet d'obtenir un pointeur vers le début de la plage de donnée du vecteur
		*/
		const float* data() const { return &x; }
		
		/*
		Setter pour les valeurs du vecteur
		*/
		void set(float vx, float vy, float vz, float pt = 1);
		void set(const Vector4f& v) { set(v.x, v.y, v.z, v.t); };
		
		/*
		Opérateur permettant réalisé l'opération mathématique correspondante
			à chaque valeur du vecteur
		*/
		void operator*=(float value);
		void operator/=(float value);
		void operator+=(float value);
		void operator-=(float value);
		
		/*
		Opérateur permettant réalisé l'opération mathématique correspondante
			entre 2 vecteurs
		*/
		void operator+=(const Vector4f& v);
		void operator-=(const Vector4f& v);

		/*
		Opérateur de cast pour convertir ce vecteur en un vecteur Qt
		*/
		operator QVector4D() { return QVector4D(x, y, z, t); }
	};
	/*
	Opérateur permettant réalisé l'opération mathématique correspondante
		à chaque valeur du vecteur et retournant un nouveau vecteur
	*/
	Vector4f operator*(const Vector4f& v1, float value);
	Vector4f operator/(const Vector4f& v1, float value);
	
	/*
	Opérateur permettant réalisé l'opération mathématique correspondante
		à chaque valeur du vecteur et retournant un nouveau vecteur
	*/
	Vector4f operator+(const Vector4f& v1, const Vector4f& v2);
	Vector4f operator-(const Vector4f& v1, const Vector4f& v2);
}

#pragma once
#define _USE_MATH_DEFINES 
#include <cmath>
#include <QVector4D>
#include "data_struct/Vector3f.h"

/*
Ce struct repr�sente un vecteur math�matique de 4 valeurs

- Champs :
	x, y, z, t : les 3 valeurs

Struct r�alis�e par GONON Lucas
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
		R : Permet d'obtenir un pointeur vers le d�but de la plage de donn�e du vecteur
		*/
		const float* data() const { return &x; }
		
		/*
		Setter pour les valeurs du vecteur
		*/
		void set(float vx, float vy, float vz, float pt = 1);
		void set(const Vector4f& v) { set(v.x, v.y, v.z, v.t); };
		
		/*
		Op�rateur permettant r�alis� l'op�ration math�matique correspondante
			� chaque valeur du vecteur
		*/
		void operator*=(float value);
		void operator/=(float value);
		void operator+=(float value);
		void operator-=(float value);
		
		/*
		Op�rateur permettant r�alis� l'op�ration math�matique correspondante
			entre 2 vecteurs
		*/
		void operator+=(const Vector4f& v);
		void operator-=(const Vector4f& v);

		/*
		Op�rateur de cast pour convertir ce vecteur en un vecteur Qt
		*/
		operator QVector4D() { return QVector4D(x, y, z, t); }
	};
	/*
	Op�rateur permettant r�alis� l'op�ration math�matique correspondante
		� chaque valeur du vecteur et retournant un nouveau vecteur
	*/
	Vector4f operator*(const Vector4f& v1, float value);
	Vector4f operator/(const Vector4f& v1, float value);
	
	/*
	Op�rateur permettant r�alis� l'op�ration math�matique correspondante
		� chaque valeur du vecteur et retournant un nouveau vecteur
	*/
	Vector4f operator+(const Vector4f& v1, const Vector4f& v2);
	Vector4f operator-(const Vector4f& v1, const Vector4f& v2);
}

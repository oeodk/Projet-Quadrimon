#pragma once
#include <QVector2D>

/*
Ce struct repr�sente un vecteur math�matique de 2 valeurs

- Champs :
	x, y : les 2 valeurs

Struct r�alis�e par GONON Lucas
*/

namespace bdm
{
	struct Vector2f
	{
		float x, y;

		Vector2f(float px = 0, float py = 0);

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
		void set(float vx, float vy);
		void set(const Vector2f& v) { set(v.x, v.y); };
		
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
		void operator+=(const Vector2f& v);
		void operator-=(const Vector2f& v);
		/*
		Op�rateur de cast pour convertir ce vecteur en un vecteur Qt
		*/
		operator QVector2D() { return QVector2D(x, y); }
	};
	/*
	Op�rateur permettant r�alis� l'op�ration math�matique correspondante
		� chaque valeur du vecteur et retournant un nouveau vecteur
	*/
	Vector2f operator*(const Vector2f& v1, float value);
	Vector2f operator/(const Vector2f& v1, float value);
	
	/*
	Op�rateur permettant r�alis� l'op�ration math�matique correspondante
		entre 2 vecteurs et retournant un nouveau vecteur
	*/
	Vector2f operator+(const Vector2f& v1, const Vector2f& v2);
	Vector2f operator-(const Vector2f& v1, const Vector2f& v2);
}


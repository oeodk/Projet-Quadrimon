#pragma once
#include <QVector2D>

/*
Ce struct représente un vecteur mathématique de 2 valeurs

- Champs :
	x, y : les 2 valeurs

Struct réalisée par GONON Lucas
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
		R : Permet d'obtenir un pointeur vers le début de la plage de donnée du vecteur
		*/
		const float* data() const { return &x; }

		/*
		Setter pour les valeurs du vecteur
		*/
		void set(float vx, float vy);
		void set(const Vector2f& v) { set(v.x, v.y); };
		
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
		void operator+=(const Vector2f& v);
		void operator-=(const Vector2f& v);
		/*
		Opérateur de cast pour convertir ce vecteur en un vecteur Qt
		*/
		operator QVector2D() { return QVector2D(x, y); }
	};
	/*
	Opérateur permettant réalisé l'opération mathématique correspondante
		à chaque valeur du vecteur et retournant un nouveau vecteur
	*/
	Vector2f operator*(const Vector2f& v1, float value);
	Vector2f operator/(const Vector2f& v1, float value);
	
	/*
	Opérateur permettant réalisé l'opération mathématique correspondante
		entre 2 vecteurs et retournant un nouveau vecteur
	*/
	Vector2f operator+(const Vector2f& v1, const Vector2f& v2);
	Vector2f operator-(const Vector2f& v1, const Vector2f& v2);
}


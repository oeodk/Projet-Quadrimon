#pragma once
#define _USE_MATH_DEFINES 
#include <cmath>
#include <QMatrix4x4>
#include <QVector3D>

/*
Ce struct représente un vecteur mathématique de 3 valeurs

- Champs :
	x, y, z : les 3 valeurs

Struct réalisée par GONON Lucas
*/


namespace bdm
{
	struct Vector3f
	{
		float x, y, z;

		Vector3f(float px = 0, float py = 0, float pz = 0);

		/*
		R : normaliser le vecteur
		*/
		void normalize();

		/*
		R : inverse les valeurs du vecteur
		*/
		void invert();

		/*
		R : Permet d'obtenir un pointeur vers le début de la plage de donnée du vecteur
		*/
		const float* data() const { return &x; }

		/*
		Setter pour les valeurs du vecteur
		*/
		void set(float vx, float vy, float vz);
		void set(const Vector3f& v) { set(v.x, v.y, v.z); };

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
		void operator+=(const Vector3f& v);
		void operator-=(const Vector3f& v);

		/*
		Opérateur de cast pour convertir ce vecteur en un vecteur Qt
		*/
		operator QVector3D() { return QVector3D(x, y, z); }
	};
	/*
	Opérateur permettant réalisé l'opération mathématique correspondante
		à chaque valeur du vecteur et retournant un nouveau vecteur
	*/
	Vector3f operator*(const Vector3f& v1, float value);
	Vector3f operator/(const Vector3f& v1, float value);

	/*
	Opérateur permettant réalisé l'opération mathématique correspondante
		à chaque valeur du vecteur et retournant un nouveau vecteur
	*/
	Vector3f operator+(const Vector3f& v1, const Vector3f& v2);
	Vector3f operator-(const Vector3f& v1, const Vector3f& v2);

	/*
	R : retourne le résultat du produit entre une matrice et le vecteur
	E : transformation_matrix : la matrice
		v1 : le vecteur
	S : le vecteur résultat
	*/
	Vector3f operator*(const QMatrix4x4& transformation_matrix, const Vector3f& v1);

	/*
	R : Calcul le produit vectoriel entre 2 vecteur
	E : les 2 vecteur
	S : le vecteur résultat
	*/
	Vector3f crossProduct(const Vector3f& v1, const Vector3f& v2);
}


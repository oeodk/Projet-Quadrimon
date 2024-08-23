#pragma once
#include <string>

/*
Cette classe de gérer les modifications appliqué sur des labels

- Champs :
	text_ : text du label a modifier ou chemin vers l'image à charger
	refresh_text_ : permet de savoir si le texte du label doit être modifié
	refresh_image_: permet de savoir si l'images du label doit être modifiée

Classe réalisée par GONON Lucas
*/

class LabelElementChange
{
private :
	std::string text_ = "";
	bool refresh_text_ = true;
	bool refresh_image_ = true;
public :

	/*
	R : permet de modifier le texte du label
	E : text : le nouveau texte
	*/
	void setText(const std::string& text);

	/*
	R : permet de modifier l'image du label
	E : text : le chemin vers la nouvelle images
	*/
	void setImage(const std::string& path);

	/*
	Getter pour text_
	*/
	const std::string& getText();

	/*
	Getter pour refresh_text_
	*/
	bool getRefreshText() const { return refresh_text_; }

	/*
	Getter pour refresh_image_
	*/
	bool getRefreshImage() const { return refresh_image_; }
};


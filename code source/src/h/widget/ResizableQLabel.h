#pragma once
#include <QLabel>
#include <QPixmap>

/*
Cette classe permet d'avoir des labels qui ont un texte qui se redimensionne 

- Champs :
    pixmap_ : l'image du label
    has_image_ : booléen permettant de savoir si le label a une image

Classe réalisée par GONON Lucas
*/

class ResizableQLabel :
    public QLabel
{
private :
    QPixmap pixmap_;
    bool has_image_;
public :
    ResizableQLabel(QWidget* parent = nullptr);
    /*
    Méthode permettant de gérer le redimensionnement des éléments du label
    */
    void resizeEvent(QResizeEvent* event) override;
    void resizeImage() {setPixmap(pixmap_.scaled(width(), height(), Qt::KeepAspectRatio));}
    void resizeText();
    void setImage(const std::string& path);
};


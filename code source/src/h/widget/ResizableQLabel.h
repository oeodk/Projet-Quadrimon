#pragma once
#include <QLabel>
#include <QPixmap>

/*
Cette classe permet d'avoir des labels qui ont un texte qui se redimensionne 

- Champs :
    pixmap_ : l'image du label
    has_image_ : bool�en permettant de savoir si le label a une image

Classe r�alis�e par GONON Lucas
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
    M�thode permettant de g�rer le redimensionnement des �l�ments du label
    */
    void resizeEvent(QResizeEvent* event) override;
    void resizeImage() {setPixmap(pixmap_.scaled(width(), height(), Qt::KeepAspectRatio));}
    void resizeText();
    void setImage(const std::string& path);
};


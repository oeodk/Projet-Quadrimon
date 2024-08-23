#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_quadrimonthegame.h"
#include "game.h"
#include "data_struct/LabelElementChange.h"
#include <QTimer>
#include <QKeyEvent>
#include "utility/Timer.h"

/*
Cette classe gère la fenêtre affiché et les interaction entre game et gamescene

- Champs :
    t_ : Timer utilisé pour faire tourner le jeu à 20 image par seconde
    elapsed_time_ : temps écoulé entre 2 timeout du timer
    the_game_ : La partie
    ui_label_text_ : map permettant de modifier le texte d'un label avec son nom
    ogl_labels_ : vecteur regroupant les labels de l'interface
    general_timer_ : timer utilisé pour crée un appel régulier de updateTriggered
    ui : l'ui
    pixmap_ : pixmap utilisé pour mettre l'image de la caméra dans le label correspondant
    outcome_ : résultat de la partie

Classe réalisée par GONON Lucas
*/
class QuadrimonTheGame : public QMainWindow
{
    Q_OBJECT

public:
    QuadrimonTheGame(QWidget* parent = nullptr);
    ~QuadrimonTheGame();
    
    /*
    Evènement utilisé pour recommencer une nouvelle partie
    */
    void keyPressEvent(QKeyEvent* event);

    /*
    Mis à jour de la partie
    */
    void updateTriggered();

    /*
    R : Actualise les informations de la caméra
    */
    void refreshData();

    /*
    R : Actualise les labels (textes et taille)
    */
    void refreshLabelElement();

    /*
    R : Réinitialise la partie
    */
    void resetGame();
private slots:
    /*
    R : initialise la partie une fois que le contexte OpenGl est crée
    */
    void initGame();
private:
    Timer t_;
    float elapsed_time_;
#ifdef DEBUG
    Timer test_t_;
    int thing_to_generate_ = 0;
    bool player_targeted_ = 0;
#endif
    Game the_game_;
    std::map<std::string, LabelElementChange> ui_label_text_;
    std::vector<ResizableQLabel*> ogl_labels_;
    QTimer general_timer_;
    Ui::QuadrimonTheGameClass ui;
    QPixmap pixmap_;
    int outcome_;
};

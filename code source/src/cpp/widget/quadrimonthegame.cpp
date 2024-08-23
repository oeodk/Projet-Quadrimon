#include "widget/quadrimonthegame.h"
#include <qcoreapplication.h>

#include <array>

QuadrimonTheGame::QuadrimonTheGame(QWidget* parent)
    : QMainWindow(parent)
{
    elapsed_time_ = 0;
    ui.setupUi(this);
    ogl_labels_.reserve(13);

    ogl_labels_.push_back(ui.atk_p1);
    ogl_labels_.push_back(ui.atk_p2);
    ogl_labels_.push_back(ui.historic);
    ogl_labels_.push_back(ui.pv_p1);
    ogl_labels_.push_back(ui.pv_p2);
    ogl_labels_.push_back(ui.quadrimonName_p1);
    ogl_labels_.push_back(ui.quadrimonName_p2);
    ogl_labels_.push_back(ui.terrainLast_p1);
    ogl_labels_.push_back(ui.terrainLast_p2);
    ogl_labels_.push_back(ui.terrainName_p1);
    ogl_labels_.push_back(ui.terrainName_p2);
    ogl_labels_.push_back(ui.type_p1);
    ogl_labels_.push_back(ui.type_p2);
    ogl_labels_.push_back(ui.quadrimon_pv_1_p1);
    ogl_labels_.push_back(ui.quadrimon_pv_2_p1);
    ogl_labels_.push_back(ui.quadrimon_pv_1_p2);
    ogl_labels_.push_back(ui.quadrimon_pv_2_p2);
    ogl_labels_.push_back(ui.quadrimon_sprite_1_p1);
    ogl_labels_.push_back(ui.quadrimon_sprite_2_p1);
    ogl_labels_.push_back(ui.quadrimon_sprite_1_p2);
    ogl_labels_.push_back(ui.quadrimon_sprite_2_p2);

    for (auto& label : ogl_labels_)
    {
        ui_label_text_.insert({ label->objectName().toStdString(), LabelElementChange() });
    }
    the_game_.setUiLabelText(&ui_label_text_);
    the_game_.setScenePolygons(ui.OGL->getPolygons());
    the_game_.setSceneShadowPolygons(ui.OGL->getShadowPolygons());
    the_game_.setSceneOverlayPolygons(ui.OGL->getOverlayPolygons());

    outcome_ = 0;

    connect(ui.OGL, SIGNAL(initGlFinished()), this, SLOT(initGame()));
    // Connexion du timer
    general_timer_.start(1);
}

QuadrimonTheGame::~QuadrimonTheGame()
{

}

void QuadrimonTheGame::keyPressEvent(QKeyEvent* event)
{
    if (outcome_ != 0)
    {
        resetGame();
        outcome_ = 0;
    }

#ifdef DEBUG
    ui.OGL->makeCurrent();
    if (event->key() > 48 && event->key() < 58)
    {
        thing_to_generate_ = event->key() - 49;
        qDebug() << E_QuadrimonName::QUADRIMON_NAME_STRING_MAP.at(E_QuadrimonName::e_QuadrimonName(thing_to_generate_)) + " / " + E_TerrainName::TERRAIN_NAME_STRING_MAP.at(E_TerrainName::e_TerrainName(thing_to_generate_));
    }

    switch (event->key())
    {
    case Qt::Key_0:
        player_targeted_ = !player_targeted_;
        qDebug() << "Player : " + std::to_string(player_targeted_ + 1);
        break;
    case Qt::Key_Plus:
        the_game_.setScannedCard(thing_to_generate_, player_targeted_, true);
        break;
    case Qt::Key_Minus:
        the_game_.setScannedCard(thing_to_generate_, player_targeted_, false);
        break;
    default:
        // Ignorer l'evenement
        event->ignore();
        return;
    }
#endif
    event->accept();

}

void QuadrimonTheGame::updateTriggered()
{
    constexpr float FRAMERATE = 1 / 20.f;
    t_.stop();
    elapsed_time_ += t_.getTime();
    t_.start();

    if (elapsed_time_ > FRAMERATE)
    {
#ifdef DEBUG
        test_t_.stop();
        qDebug() << std::to_string(1 / test_t_.getTime()) + " real fps";
        test_t_.start();
#endif
        elapsed_time_ = 0;
        if (outcome_ == 0)
        {
            ui.OGL->makeCurrent();
            outcome_ = the_game_.update();
            QImage* camera_img = the_game_.getInImage();
            // Check if image loading was successful
            if (camera_img->isNull()) {
                qDebug() << "Failed to load image";
                return; // or handle the error appropriately
            }

            pixmap_ = QPixmap::fromImage(*camera_img);
            if (auto label = qobject_cast<QLabel*>(ui.camera))
            {
                label->setPixmap(pixmap_);
                label->setScaledContents(true);

                label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            }
            else {
                qDebug() << "ui.camera is not a QLabel";
            }
            refreshLabelElement();
            refreshData();
            ui.OGL->updateScene();
            ui.OGL->update();
        }
        else
        {
            ui_label_text_.at("historic").setText(" Victoire du joueur " + std::to_string(outcome_) + "! \n Appuyez sur une touche pour lancer une nouvelle partie ");
            refreshLabelElement();
            refreshData();
            ui.OGL->updateScene();
            ui.OGL->update();
        }
    }
}

void QuadrimonTheGame::refreshLabelElement()
{
    for (auto& label : ogl_labels_)
    {
        const std::string label_name = label->objectName().toStdString();
        if (ui_label_text_.at(label_name).getRefreshText())
        {
            label->setText(ui_label_text_.at(label_name).getText().c_str());
            label->resizeText();
        }
        if (ui_label_text_.at(label_name).getRefreshImage())
        {
            label->setImage(ui_label_text_.at(label_name).getText().c_str());
        }
    }
}

void QuadrimonTheGame::resetGame()
{
    the_game_.resetGame();
    the_game_.setSceneOverlayPolygons(ui.OGL->getOverlayPolygons());
    for (auto& label : ogl_labels_)
    {
        label->setText("");
        label->resizeText();
        label->setPixmap(QPixmap());
    }
}

/*
The game must be initialized here because the quadrimons polygons need a valid openGL context
The context used is created in initializeGl of ui.OGL
*/
void QuadrimonTheGame::initGame()
{
    the_game_.initGame();
    connect(&general_timer_, &QTimer::timeout, this,  [&] {updateTriggered(); });

}


void QuadrimonTheGame::refreshData()
{
    the_game_.downSpecificCameraPOV();
    the_game_.getSpecificCamPos();
    ui.OGL->setCameraPosition(the_game_.getCamPos());
    ui.OGL->setCenterPosition(the_game_.getCenterPos());
    ui.OGL->setSpecificPOV(the_game_.getSpecificCameraPOV());
}
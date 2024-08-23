QT       += core gui widgets opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/cpp/Game.cpp \
    src/cpp/data_struct/BiTextureOpenGlPolygon.cpp \
    src/cpp/data_struct/DynamicOpenGlPolygon.cpp \
    src/cpp/data_struct/LabelElementChange.cpp \
    src/cpp/data_struct/Material.cpp \
    src/cpp/data_struct/OpenGlPolygon.cpp \
    src/cpp/data_struct/SmallVertex.cpp \
    src/cpp/data_struct/Vector2f.cpp \
    src/cpp/data_struct/Vector3f.cpp \
    src/cpp/data_struct/Vector4f.cpp \
    src/cpp/data_struct/Vertex.cpp \
    src/cpp/function/complexe_polygon.cpp \
    src/cpp/function/utility.cpp \
    src/cpp/main.cpp \
    src/cpp/quadrimon/CylindrusTexture.cpp \
    src/cpp/quadrimon/FlambyDeeseUltimeCreation.cpp \
    src/cpp/quadrimon/GlaceFraise.cpp \
    src/cpp/quadrimon/KhoneRoiDemonDemoniaqueSupreme.cpp \
    src/cpp/quadrimon/MecaPyramideGizeh.cpp \
    src/cpp/quadrimon/MenuDonutVegan.cpp \
    src/cpp/quadrimon/OlafBonHommeNeige.cpp \
    src/cpp/quadrimon/Quadrimon.cpp \
    src/cpp/quadrimon/SaladierMystique.cpp \
    src/cpp/quadrimon/SoleilOpenGL.cpp \
    src/cpp/terrain/ChatGPT.cpp \
    src/cpp/terrain/EmptyTerrain.cpp \
    src/cpp/terrain/Foret.cpp \
    src/cpp/terrain/Grotte.cpp \
    src/cpp/terrain/Infirmerie.cpp \
    src/cpp/terrain/Marai.cpp \
    src/cpp/terrain/Ouragan.cpp \
    src/cpp/terrain/Plage.cpp \
    src/cpp/terrain/Terrain.cpp \
    src/cpp/terrain/Toiles.cpp \
    src/cpp/terrain/Volcan.cpp \
    src/cpp/utility/CardDisplay.cpp \
    src/cpp/utility/CardReader.cpp \
    src/cpp/utility/SceneOverlay.cpp \
    src/cpp/utility/Timer.cpp \
    src/cpp/widget/ResizableQLabel.cpp \
    src/cpp/widget/gamescene.cpp \
    src/cpp/widget/quadrimonthegame.cpp

HEADERS += \
    src/h/Game.h \
    src/h/data_struct/BiTextureOpenGlPolygon.h \
    src/h/data_struct/DynamicOpenGlPolygon.h \
    src/h/data_struct/LabelElementChange.h \
    src/h/data_struct/Material.h \
    src/h/data_struct/OpenGlPolygon.h \
    src/h/data_struct/SmallVertex.h \
    src/h/data_struct/Vector2f.h \
    src/h/data_struct/Vector3f.h \
    src/h/data_struct/Vector4f.h \
    src/h/data_struct/Vertex.h \
    src/h/enum/E_GameState.h \
    src/h/enum/E_OverlayCardState.h \
    src/h/enum/E_Player.h \
    src/h/enum/E_QuadrimonName.h \
    src/h/enum/E_QuadrimonState.h \
    src/h/enum/E_QuadrimonType.h \
    src/h/enum/E_TerrainName.h \
    src/h/function/complexe_polygon.h \
    src/h/function/utility.h \
    src/h/quadrimon/CylindrusTexture.h \
    src/h/quadrimon/FlambyDeeseUltimeCreation.h \
    src/h/quadrimon/GlaceFraise.h \
    src/h/quadrimon/KhoneRoiDemonDemoniaqueSupreme.h \
    src/h/quadrimon/MecaPyramideGizeh.h \
    src/h/quadrimon/MenuDonutVegan.h \
    src/h/quadrimon/OlafBonHommeNeige.h \
    src/h/quadrimon/Quadrimon.h \
    src/h/quadrimon/SaladierMystique.h \
    src/h/quadrimon/SoleilOpenGL.h \
    src/h/terrain/ChatGPT.h \
    src/h/terrain/EmptyTerrain.h \
    src/h/terrain/Foret.h \
    src/h/terrain/Grotte.h \
    src/h/terrain/Infirmerie.h \
    src/h/terrain/Marai.h \
    src/h/terrain/Ouragan.h \
    src/h/terrain/Plage.h \
    src/h/terrain/Terrain.h \
    src/h/terrain/Toiles.h \
    src/h/terrain/Volcan.h \
    src/h/utility/CardDisplay.h \
    src/h/utility/CardReader.h \
    src/h/utility/SceneOverlay.h \
    src/h/utility/Timer.h \
    src/h/widget/ResizableQLabel.h \
    src/h/widget/gamescene.h \
    src/h/widget/quadrimonthegame.h

FORMS += \
    quadrimonthegame.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH +=./src/h

INCLUDEPATH +=.\openCV\include

LIBS +=-L$$PWD\openCV\lib\ -lopencv_core490 \
     -lopencv_highgui490 \
     -lopencv_imgproc490 \
     -lopencv_imgcodecs490 \
     -lopencv_videoio490 \
     -lopencv_features2d490 \
     -lopencv_calib3d490

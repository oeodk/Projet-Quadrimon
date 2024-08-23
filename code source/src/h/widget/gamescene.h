#pragma once
#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_compatibility.h>
#include <map>
#include "data_struct/OpenGlPolygon.h"
#include "data_struct/BiTextureOpenGlPolygon.h"

#include "quadrimon/CylindrusTexture.h"
#include "quadrimon/GlaceFraise.h"
#include "quadrimon/OlafBonHommeNeige.h"
#include "quadrimon/SoleilOpenGL.h"
#include "quadrimon/MecaPyramideGizeh.h"
#include "quadrimon/KhoneRoiDemonDemoniaqueSupreme.h"
#include "quadrimon/FlambyDeeseUltimeCreation.h"
#include "quadrimon/MenuDonutVegan.h"
#include "quadrimon/SaladierMystique.h"

/*
Cette classe de gérer l'affichage de la scene 3D

Cette classe contient un Struct permettant d'effectuer l'effet de Bloom 
(Algorithme utilisé : https://learnopengl.com/Guest-Articles/2022/Phys.-Based-Bloom)

- Champs :
    
Les champs polygons_, shadow_polygons_ et overlay_polygons_ permette de stocker les polygons à utiliser au cours des différentes
    étapes du rendue
    
    polygons_ : Polygon composant la scène 3D affichée
    shadow_polygons_ : Polygon projetant une ombre
    overlay_polygons_ : Polygon affichés "par dessus" le reste du rendu

Pour réaliser l'affichage plusieurs shaders sont utilisés et stocké dans les champs suivant 
    main_shader_program_ : Programme principal permettant l'affichage de la scène complète, 
        la sortie de ce programme est une texture représentant ce qui serai censé être affiché à l'écran
    shadow_shader_program_ : Programme effectuant le rendue de la scène du point de vue de la source de lumière
        pour générer la carte de profondeur utilisé par le main_shader_program_ pour afficher les ombres
        (Algorithme utilisé : https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping)
    bloom_shader_program_ : Programme utilisé pour générer la texture de bloom
    display_shader_program_ : Programme utilisé pour combiner la texture du rendu de la scène avec la texture de bloom 
        pour ensuite l'afficher à l'écran
    overlay_shader_program_ : Programme utilisé pour afficher des élément après toutes les étapes précédentes

Les champs suivant permettent la gestion de la caméra et de la matrice vue/projection
    camera_position_ : position de la caméra
    center_position_ : point que regarde la caméra
    view_ : matrice de vue associée à la caméra
    projection_ : matrice de projection utilisée
    projection_view_ : produit de la matrice de projection par la matrice de vue (stocké pour éviter de la recalculer en permanence)
    POV_ : booléen permettant de savoir si la position de la caméra est géré automatiquement

    light_position_ : position de la lumière

les champs main_uniforms_location_, shadow_uniforms_location_, bloom_uniforms_location_ et overlay_uniforms_location_
    sont des maps permettant de gérer les uniforms (variables envoyé au shaders) des shaders correspondant
   
    main_fbo_ : FrameBuffer utilisé pour le rendu principal de la scène
        (Un frame buffer object est une structure possédant les données des pixels affichés à l'écran, ces données peuvent être 
         dans une textures ou un render buffer object (buffer spécialisé pour des rendu non affiché à l'écran)
    main_rbo_ : renderBuffer utilisé par main_fbo_ pour stocker la carte de profondeur de la scène
    main_texture_ : texture utilisée par le main_fbo_ pour stocked ce qui est censé être affiché à l'écran
    width_, height_ : largeur et hauteur de main_texture_;
    display_rectangle_ : données de la position et du mappage de texture du rectangle utilisée pour afficher la texture (main_texture_ + bloom_texture_)
    rectangle_vao_, rectangle_vbo_ : buffer utilisés pour afficher le rectangle ci-dessus

    attachment_ : emplacement des sorties de texture du main shader
    bloom_texture_ : texture utilisés pour l'effet de bloom

    bloom_mips_, bloom_fbo_, attachments_bloom_ : variables utilisés pour l'effet de bloom

    shadow_map_fbo_ : frameBuffer utilisé pour le rendue des ombres
    SHADOW_MAP_WIDTH_, SHADOW_MAP_HEIGHT_ : largeur et hauteur de la texture utilisée pour les ombres
    shadow_map_text_ : texture contenant les ombres de la scène
    clamp_color_ : valeurs maximales de depth pour la texture des ombres

    orthogonal_projection_, light_view_, light_projection_ : informations sur la lumière utilisé pour le calcul des ombres

    GAMMA_ : valeur utilisé pour la correction de gamma appliqué
    internal_counter_ : conteur pour le mouvement de la caméra

Classe réalisée par GONON Lucas
*/

struct BloomMip
{
    // Taille de la texture
    bdm::Vector2f size;
    // Taille entière de la texture
    bdm::Vector2f int_size;
    // Texture OpenGL
    unsigned int texture;
};

class GameScene :
    public QOpenGLWidget, protected QOpenGLFunctions_3_3_Compatibility
{
    Q_OBJECT
private :
    std::vector<OpenGlPolygon*> polygons_;
    std::vector<OpenGlPolygon*> shadow_polygons_;
    std::vector<OpenGlPolygon*> overlay_polygons_;

    unsigned int main_shader_program_;
    unsigned int shadow_shader_program_;
    unsigned int bloom_shader_program_;
    unsigned int display_shader_program_;
    unsigned int overlay_shader_program_;

    bdm::Vector3f camera_position_;
    bdm::Vector3f center_position_;
    QMatrix4x4 view_;
    QMatrix4x4 projection_;
    QMatrix4x4 projection_view_;
    //gestion exceptionnelle de la caméra
    bool POV_;
    
    bdm::Vector3f light_position_;

    std::map<std::string, int> main_uniforms_location_;
    std::map<std::string, int> shadow_uniforms_location_;
    std::map<std::string, int> bloom_uniforms_location_;
    std::map<std::string, int> overlay_uniforms_location_;

    unsigned int main_fbo_;
    unsigned int main_rbo_;
    unsigned int main_texture_;
    int width_, height_;

    float display_rectangle_[24] =
    {
        //  Coords   // texCoords
         1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f,

         1.0f,  1.0f,  1.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f
    };
    unsigned int rectangle_vao_, rectangle_vbo_;

    unsigned int attachment_[2];
    unsigned int bloom_texture_;

    std::array< BloomMip, 6> bloom_mips_;
    unsigned int bloom_fbo_;
    unsigned int attachments_bloom_[1] = { GL_COLOR_ATTACHMENT0 };

    unsigned int shadow_map_fbo_;
    static constexpr unsigned int SHADOW_MAP_WIDTH_ = 1024;
    static constexpr unsigned int SHADOW_MAP_HEIGHT_ = 1024;
    unsigned int shadow_map_text_;
    float clamp_color_[4] = { 1.f, 1.f, 1.f, 1.f };

    QMatrix4x4 orthogonal_projection_, light_view_, light_projection_;

    static constexpr float GAMMA_ = 2.2f;

    unsigned int internal_counter_;

    /*
    R : Charge un shader 
    E : program : le shader programme à chargé
        vertex_shader_path : le chemin vers le vertex shader à charger
        frag_shader_path : le chemin vers le fragment shader à charger
    */
    void loadShader(GLuint& program, const std::string& vertex_shader_path, const std::string& frag_shader_path);

    /*
    R : Charge le texte d'un fichier
    E : filename : le chemin vers ce fichier
    */
    std::string loadShaderSource(const std::string& filename);

    /*
    R : permet de déterminer la mise à l'échelle appliqué a l'écran
    S : le facteur d'échalle
    */
    float getScreenScaleFactor();
protected :
    void initializeGL() override;
    void paintGL() override;

    /*
    R : Méthodes permettant d'afficher la scène, les ombres et le rendu final à l'écran
    */
    void drawPolygons();
    void drawShadow();
    void drawOnScreen();
public :
    GameScene(QWidget* parent = nullptr);

    /*
    R : Permet l'animation de la caméra
    */
    void updateScene();

    /*
    Setter pour GameScene
    */
    std::vector<OpenGlPolygon*>* getPolygons() { return &polygons_; }
    std::vector<OpenGlPolygon*>* getShadowPolygons() { return &shadow_polygons_; }
    std::vector<OpenGlPolygon*>* getOverlayPolygons() { return &overlay_polygons_; }

    //gestion exceptionnelle de la caméra
    void setCameraPosition(bdm::Vector3f cam_pos) { camera_position_ = cam_pos; }
    void setCenterPosition(bdm::Vector3f center_pos) { center_position_ = center_pos; }
    void setSpecificPOV(bool POV) { POV_ = POV; }
signals:
    /*
    Signal pour signaler que le contexte OpenGl est crée et que game peut être initialisé
    */
    void initGlFinished();
};


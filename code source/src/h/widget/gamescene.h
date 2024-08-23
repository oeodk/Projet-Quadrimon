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
Cette classe de g�rer l'affichage de la scene 3D

Cette classe contient un Struct permettant d'effectuer l'effet de Bloom 
(Algorithme utilis� : https://learnopengl.com/Guest-Articles/2022/Phys.-Based-Bloom)

- Champs :
    
Les champs polygons_, shadow_polygons_ et overlay_polygons_ permette de stocker les polygons � utiliser au cours des diff�rentes
    �tapes du rendue
    
    polygons_ : Polygon composant la sc�ne 3D affich�e
    shadow_polygons_ : Polygon projetant une ombre
    overlay_polygons_ : Polygon affich�s "par dessus" le reste du rendu

Pour r�aliser l'affichage plusieurs shaders sont utilis�s et stock� dans les champs suivant 
    main_shader_program_ : Programme principal permettant l'affichage de la sc�ne compl�te, 
        la sortie de ce programme est une texture repr�sentant ce qui serai cens� �tre affich� � l'�cran
    shadow_shader_program_ : Programme effectuant le rendue de la sc�ne du point de vue de la source de lumi�re
        pour g�n�rer la carte de profondeur utilis� par le main_shader_program_ pour afficher les ombres
        (Algorithme utilis� : https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping)
    bloom_shader_program_ : Programme utilis� pour g�n�rer la texture de bloom
    display_shader_program_ : Programme utilis� pour combiner la texture du rendu de la sc�ne avec la texture de bloom 
        pour ensuite l'afficher � l'�cran
    overlay_shader_program_ : Programme utilis� pour afficher des �l�ment apr�s toutes les �tapes pr�c�dentes

Les champs suivant permettent la gestion de la cam�ra et de la matrice vue/projection
    camera_position_ : position de la cam�ra
    center_position_ : point que regarde la cam�ra
    view_ : matrice de vue associ�e � la cam�ra
    projection_ : matrice de projection utilis�e
    projection_view_ : produit de la matrice de projection par la matrice de vue (stock� pour �viter de la recalculer en permanence)
    POV_ : bool�en permettant de savoir si la position de la cam�ra est g�r� automatiquement

    light_position_ : position de la lumi�re

les champs main_uniforms_location_, shadow_uniforms_location_, bloom_uniforms_location_ et overlay_uniforms_location_
    sont des maps permettant de g�rer les uniforms (variables envoy� au shaders) des shaders correspondant
   
    main_fbo_ : FrameBuffer utilis� pour le rendu principal de la sc�ne
        (Un frame buffer object est une structure poss�dant les donn�es des pixels affich�s � l'�cran, ces donn�es peuvent �tre 
         dans une textures ou un render buffer object (buffer sp�cialis� pour des rendu non affich� � l'�cran)
    main_rbo_ : renderBuffer utilis� par main_fbo_ pour stocker la carte de profondeur de la sc�ne
    main_texture_ : texture utilis�e par le main_fbo_ pour stocked ce qui est cens� �tre affich� � l'�cran
    width_, height_ : largeur et hauteur de main_texture_;
    display_rectangle_ : donn�es de la position et du mappage de texture du rectangle utilis�e pour afficher la texture (main_texture_ + bloom_texture_)
    rectangle_vao_, rectangle_vbo_ : buffer utilis�s pour afficher le rectangle ci-dessus

    attachment_ : emplacement des sorties de texture du main shader
    bloom_texture_ : texture utilis�s pour l'effet de bloom

    bloom_mips_, bloom_fbo_, attachments_bloom_ : variables utilis�s pour l'effet de bloom

    shadow_map_fbo_ : frameBuffer utilis� pour le rendue des ombres
    SHADOW_MAP_WIDTH_, SHADOW_MAP_HEIGHT_ : largeur et hauteur de la texture utilis�e pour les ombres
    shadow_map_text_ : texture contenant les ombres de la sc�ne
    clamp_color_ : valeurs maximales de depth pour la texture des ombres

    orthogonal_projection_, light_view_, light_projection_ : informations sur la lumi�re utilis� pour le calcul des ombres

    GAMMA_ : valeur utilis� pour la correction de gamma appliqu�
    internal_counter_ : conteur pour le mouvement de la cam�ra

Classe r�alis�e par GONON Lucas
*/

struct BloomMip
{
    // Taille de la texture
    bdm::Vector2f size;
    // Taille enti�re de la texture
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
    //gestion exceptionnelle de la cam�ra
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
    E : program : le shader programme � charg�
        vertex_shader_path : le chemin vers le vertex shader � charger
        frag_shader_path : le chemin vers le fragment shader � charger
    */
    void loadShader(GLuint& program, const std::string& vertex_shader_path, const std::string& frag_shader_path);

    /*
    R : Charge le texte d'un fichier
    E : filename : le chemin vers ce fichier
    */
    std::string loadShaderSource(const std::string& filename);

    /*
    R : permet de d�terminer la mise � l'�chelle appliqu� a l'�cran
    S : le facteur d'�challe
    */
    float getScreenScaleFactor();
protected :
    void initializeGL() override;
    void paintGL() override;

    /*
    R : M�thodes permettant d'afficher la sc�ne, les ombres et le rendu final � l'�cran
    */
    void drawPolygons();
    void drawShadow();
    void drawOnScreen();
public :
    GameScene(QWidget* parent = nullptr);

    /*
    R : Permet l'animation de la cam�ra
    */
    void updateScene();

    /*
    Setter pour GameScene
    */
    std::vector<OpenGlPolygon*>* getPolygons() { return &polygons_; }
    std::vector<OpenGlPolygon*>* getShadowPolygons() { return &shadow_polygons_; }
    std::vector<OpenGlPolygon*>* getOverlayPolygons() { return &overlay_polygons_; }

    //gestion exceptionnelle de la cam�ra
    void setCameraPosition(bdm::Vector3f cam_pos) { camera_position_ = cam_pos; }
    void setCenterPosition(bdm::Vector3f center_pos) { center_position_ = center_pos; }
    void setSpecificPOV(bool POV) { POV_ = POV; }
signals:
    /*
    Signal pour signaler que le contexte OpenGl est cr�e et que game peut �tre initialis�
    */
    void initGlFinished();
};


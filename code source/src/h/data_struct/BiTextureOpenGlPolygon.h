#pragma once
#include "data_struct/OpenGlPolygon.h"

/*
Ce struct permet d'avoir un polygon poss�dant deux textures  

- Champs : 
    second_texture_location_ : est l'indice du buffer contenant la seconde texture du polygon
    has_second_texture_ : permet de savoir si le polygon poss�de une seconde texture
    blend_factor_ : le taux d'affichage des textures : (1 - blend_factor) * texture_1  + blend_factor * texture_2

Struct r�alis�e par GONON Lucas
*/
struct BiTextureOpenGlPolygon :
    public OpenGlPolygon
{
    unsigned int second_texture_location_;
    bool has_second_texture_;
    float blend_factor_;

    BiTextureOpenGlPolygon(const QMatrix4x4* player_side_model);

    /*
    R : Lie les buffers du polygon au buffers actif
    */
    void bindSecondTexture();
    
    /*
    R : Lib�re les buffers actif
    */
    void releaseSecondTexture();

    /*
    R : Charge la seconde texture
    E : filename : le chemin vers la texture
        interpolation_type : la m�thode d'interpolation utilis�
    */
    void loadSecondTexture(const std::string& filename, int interpolation_type = GL_LINEAR);

    /*
    R : Supprime la seconde texture des buffers d'OpenGl
    */
    void deleteSecondTexture();
};


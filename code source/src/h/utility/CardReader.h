#pragma once
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/photo.hpp>
#include <QImage>
#include <enum/E_QuadrimonName.h>
#include <enum/E_TerrainName.h>
#include <enum/E_Player.h>
#include <future>
#include <utility>

/*
Cette classe g�re interaction avec la cam�ra
Une struct permettant de lier une carte avec un nombre de bon match lors de la reconnaissance

Des threads sont utilis�s pour permettre un traitement rapide de l'image, le traitement de chaque carte est 
	r�alis� en parall�le car les op�rations concern�es sont ind�pendant entre elles

- Champs :
	
Cette classe poss�de des constantes :
	CARD_NUMBER : le nombre de carte (quadrimon + terrain)
	CONSECUTIVE_THRESHOLD : le nombre de fois qu'une carte doit �tre scann� d'affil� pour valider la carte scann�e
	RATIO : une constante pour manipuler la taille des cadres du retour cam�ra

Les variables in_image_start_left_p1_, in_image_start_left_p2_, in_image_start_top_, in_image_start_height_ et in_image_start_width_
	sont trait� comme des constantes et correspondent au position des cadres sur le retour cam�ra (ces variable ne 
	sont pas d�clar� comme des constantes car elles d�pendes de la r�solution de la cam�ra)

Les variables orb_ et matcher_ permette de calculer les keypoints de l'image et de les appareiller, ces variables sont 
	statique pour pouvoir �tre utilis�es par les diff�rents threads

	cap_ : variable permettant de r�cup�rer des images de la cam�ra
	in_image_ : image r�cup�r� via la cam�ra
	out_image_ : image du retour cam�ra

Les variables quadrimon_scanned_ et terrain_scanned_ correspondent au cartes quadrimon / terrain d�tect� pour chaque joueur

	descriptors_ : vecteur contenant les descripteurs de chacune des cartes
	img_tested_ : images ne contenant que les parties dans les cadres (utilis� dans le traitement)
	img_gray_ : image d'entr�e convertie en niveau de gris
	threads_ : tableau permettant de g�rer l'ex�cution des threads de matching
	treatment_threads_ : tableau permettant de g�rer l'ex�cution des threads joueur 1 / joueur 2
	matchs_ : tableau poss�dant le nombre de match entre chaque carte et l'image scann�e
	best_matchs_info_ : cartes les plus probable d'avoir �t� scann�e pour chaque joueur
	last_detected_card_ : derni�re carte scann�e pour chaque joueur 
	consecutive_card_ : nombre de fois que la m�me carte a �t� scann�e pour chaque joueur

Struct r�alis�e par GONON Lucas
*/

struct IntIndPair
{
	unsigned int indice = 0;
	int value = 0;
};

class CardReader
{
private:
	constexpr static unsigned int CARD_NUMBER = 18;
#ifdef DEBUG
	static constexpr int CONSECUTIVE_THRESHOLD = 6;
#else
	static constexpr int CONSECUTIVE_THRESHOLD = 20;
#endif // DEBUG
	static constexpr float RATIO = 1;
	int in_image_start_left_p1_;
	int in_image_start_left_p2_;

	int in_image_start_top_;
	int in_image_start_height_;
	int in_image_start_width_;

	inline static cv::Ptr<cv::ORB> orb_;
	inline static cv::BFMatcher matcher_;
	cv::VideoCapture cap_;

	cv::Mat in_image_;
	QImage out_image_;
	std::array<E_QuadrimonName::e_QuadrimonName, 2> quadrimon_scanned_;
	std::array<E_TerrainName::e_TerrainName, 2> terrain_scanned_;

	std::array<cv::Mat, CARD_NUMBER> descriptors_;

	std::array<cv::Mat, 2> img_tested_;
	cv::Mat img_gray_;

	std::array<std::array<std::future<void>, CARD_NUMBER>, 2> threads_;
	std::array<std::future<void>, 2> treatment_threads_;
	std::array<std::array<int, CARD_NUMBER>, 2> matchs_ = {};
	std::array<IntIndPair, 2> best_matchs_info_;
	
	int last_detected_card_[2] = { -1,-1 };
	unsigned int consecutive_card_[2] = {};

	/*
	R : Fonction appel� dans un thread comparant les 18 cartes � l'image de la cam�ra
	E : 
	*/
	static void treatImage(const cv::Mat& image_tested, std::array<std::future<void>, CARD_NUMBER>& threads, const std::array<cv::Mat, CARD_NUMBER>& descriptors, std::array<int, CARD_NUMBER>& matchs, IntIndPair& best_match);
	static void matching(const cv::Mat& ref_descriptor, const cv::Mat& tested_descriptor, int* match_value);
public :
	CardReader();

	/*
	R : R�cup�re l'image de la cam�ra et d�tecte si une carte a �t� scann�es
	*/
	void analyseCameraImage();

	/*
	R : Fournie l'image de retour cam�ra
	S : Le retour cam�ra
	*/
	QImage* getInImage();

	/*
	R : Permet de r�cup�rer les cartes scann�es par l'utilisateur pour chaque joueur
	E : player : le joueur concern�
	S : le nom des cartes scann�s pour le joueur voulut
	*/
	std::tuple<E_QuadrimonName::e_QuadrimonName, E_TerrainName::e_TerrainName> getPlayerCards(E_Player::e_Player player);

	/*
	R : Permet de r�cup�rer la carte quadrimon scann�e par l'utilisateur pour chaque joueur
	E : player : le joueur concern�
	S : le nom de la carte quadrimon scann� pour le joueur voulut
	*/
	E_QuadrimonName::e_QuadrimonName getPlayerQuadrimon(E_Player::e_Player player);

	/*
	R : Permet de r�cup�rer la carte terrain scann�e par l'utilisateur pour chaque joueur
	E : player : le joueur concern�
	S : le nom de la carte terrain scann� pour le joueur voulut
	*/
	E_TerrainName::e_TerrainName getPlayerTerrain(E_Player::e_Player player);

#ifdef DEBUG
	/*
	Fonction de debug pour forcer un scan de carte
	*/
	void setCardScanned(int card_value, bool player, bool quadrimon);
#endif // DEBUG
};


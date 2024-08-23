#include "utility/CardReader.h"
#include <qDebug>

CardReader::CardReader()
{
	for (int i = 0; i < 2; i++)
	{
		quadrimon_scanned_[i] = E_QuadrimonName::E_END;
		terrain_scanned_[i] = E_TerrainName::E_END;
	}
	cap_.open(0);
	cap_.set(cv::CAP_PROP_FRAME_WIDTH, 10000);
	cap_.set(cv::CAP_PROP_FRAME_HEIGHT, 10000);
	constexpr int CAM_WIDTH = 800;
	const int CAM_HEIGHT = (CAM_WIDTH / float(cap_.get(cv::CAP_PROP_FRAME_WIDTH))) * cap_.get(cv::CAP_PROP_FRAME_HEIGHT);
	cap_.set(cv::CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
	cap_.set(cv::CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);

	orb_ = cv::ORB::create();
	std::array<cv::Mat, CARD_NUMBER> images;
	std::array<std::vector<cv::KeyPoint>, CARD_NUMBER> keypoints;

	images[0] = cv::imread("./assets/cards/quadrimon/cylindrus.png", cv::IMREAD_GRAYSCALE);
	images[1] = cv::imread("./assets/cards/quadrimon/glace_fraise.png", cv::IMREAD_GRAYSCALE);
	images[2] = cv::imread("./assets/cards/quadrimon/olaf.png", cv::IMREAD_GRAYSCALE);
	images[3] = cv::imread("./assets/cards/quadrimon/soleil_opengl.png", cv::IMREAD_GRAYSCALE);
	images[4] = cv::imread("./assets/cards/quadrimon/meca_pyramide.png", cv::IMREAD_GRAYSCALE);
	images[5] = cv::imread("./assets/cards/quadrimon/khone.png", cv::IMREAD_GRAYSCALE);
	images[6] = cv::imread("./assets/cards/quadrimon/flamby.png", cv::IMREAD_GRAYSCALE);
	images[7] = cv::imread("./assets/cards/quadrimon/donut_vegan.png", cv::IMREAD_GRAYSCALE);
	images[8] = cv::imread("./assets/cards/quadrimon/saladier_mystique.png", cv::IMREAD_GRAYSCALE);
	
	images[9] = cv::imread("./assets/cards/terrain/ouragan.png", cv::IMREAD_GRAYSCALE);
	images[10] = cv::imread("./assets/cards/terrain/marai.png", cv::IMREAD_GRAYSCALE);
	images[11] = cv::imread("./assets/cards/terrain/chatgpt.png", cv::IMREAD_GRAYSCALE);
	images[12] = cv::imread("./assets/cards/terrain/toile_araignee.png", cv::IMREAD_GRAYSCALE);
	images[13] = cv::imread("./assets/cards/terrain/grotte.png", cv::IMREAD_GRAYSCALE);
	images[14] = cv::imread("./assets/cards/terrain/infirmerie.png", cv::IMREAD_GRAYSCALE);
	images[15] = cv::imread("./assets/cards/terrain/volcan.png", cv::IMREAD_GRAYSCALE);
	images[16] =cv:: imread("./assets/cards/terrain/foret.png", cv::IMREAD_GRAYSCALE);
	images[17] = cv::imread("./assets/cards/terrain/plage.png", cv::IMREAD_GRAYSCALE);

	for (int i = 0; i < images.size(); i++)
	{
		orb_->detectAndCompute(images[i], cv::noArray(), keypoints[i], descriptors_[i]);
	}
	matcher_ = cv::BFMatcher(cv::NORM_HAMMING);

	cap_.read(in_image_);
	in_image_start_left_p1_ = in_image_.size().width * 0.1 / RATIO;
	in_image_start_left_p2_ = in_image_.size().width * 0.65 / RATIO;

	in_image_start_height_ = (in_image_.size().width * 0.25 / RATIO) * 1.4;
	in_image_start_top_ = in_image_.size().height * 0.5 / RATIO - in_image_start_height_ * 0.5;
	in_image_start_width_ = in_image_.size().width * 0.25 / RATIO;
}

QImage* CardReader::getInImage()
{
	cv::rectangle(in_image_, cv::Rect(in_image_start_left_p1_, in_image_start_top_, in_image_start_width_, in_image_start_height_), CV_RGB(0, 0, 0), 5);
	cv::rectangle(in_image_, cv::Rect(in_image_start_left_p1_, in_image_start_top_, in_image_start_width_, in_image_start_height_ * 0.33), CV_RGB(0, 0, 0), 5);
	cv::rectangle(in_image_, cv::Rect(in_image_start_left_p1_ + in_image_start_width_ * 0.05, in_image_start_top_ + in_image_start_height_ * 0.34, in_image_start_width_ * 0.9, in_image_start_height_ * 0.61), CV_RGB(0, 0, 0), 5);

	cv::rectangle(in_image_, cv::Rect(in_image_start_left_p2_, in_image_start_top_, in_image_start_width_, in_image_start_height_), CV_RGB(0, 0, 0), 5);
	cv::rectangle(in_image_, cv::Rect(in_image_start_left_p2_, in_image_start_top_, in_image_start_width_, in_image_start_height_ * 0.33), CV_RGB(0, 0, 0), 5);
	cv::rectangle(in_image_, cv::Rect(in_image_start_left_p2_ + in_image_start_width_ * 0.05, in_image_start_top_ + in_image_start_height_ * 0.34, in_image_start_width_ * 0.9, in_image_start_height_ * 0.61), CV_RGB(0, 0, 0), 5);
	cv::flip(in_image_, in_image_, 1);
	cv::cvtColor(in_image_, in_image_, cv::COLOR_BGR2RGB);
	

	out_image_ = QImage((const unsigned char*)(in_image_.data), in_image_.cols, in_image_.rows, QImage::Format_RGB888);

	return &out_image_;
}

void CardReader::analyseCameraImage()
{
	cap_.read(in_image_);
	cv::cvtColor(in_image_, img_gray_, cv::COLOR_BGR2GRAY);
	img_tested_[0] = img_gray_(cv::Range(in_image_start_top_, in_image_start_top_ + in_image_start_height_), cv::Range(in_image_start_left_p1_, in_image_start_left_p1_ + in_image_start_width_));
	img_tested_[1] = img_gray_(cv::Range(in_image_start_top_, in_image_start_top_ + in_image_start_height_), cv::Range(in_image_start_left_p2_, in_image_start_left_p2_ + in_image_start_width_));
	for (int i = 0; i < 2; i++)
	{
		treatment_threads_[i] = std::async(std::launch::async, &treatImage, std::cref(img_tested_[i]), std::ref(threads_[i]), std::cref(descriptors_), std::ref(matchs_[i]), std::ref(best_matchs_info_[i]));
	}
	for (int i = 0; i < 2; i++)
	{
		treatment_threads_[i].wait();
	}
	for (int i = 0; i < 2; i++)
	{
		if (best_matchs_info_[i].value != 0)
		{
			if (last_detected_card_[i] == -1 || last_detected_card_[i] == best_matchs_info_[i].indice)
			{
				last_detected_card_[i] = best_matchs_info_[i].indice;
				consecutive_card_[i] += 2;
			}
			else
			{
				last_detected_card_[i] = -1;
				consecutive_card_[i] = 0;
			}
		}
		else
		{
			if (consecutive_card_[i] > 0)
			{
				consecutive_card_[i]--;
			}
			else
			{
				last_detected_card_[i] = -1;
				consecutive_card_[i] = 0;
			}
		}
		if (consecutive_card_[i] > CONSECUTIVE_THRESHOLD)
		{
			last_detected_card_[i] = -1;
			consecutive_card_[i] = 0;
			if (best_matchs_info_[i].indice < E_QuadrimonName::E_END)
			{
				// Cast of the card index to a QuadrimonName enum
				quadrimon_scanned_[i] = E_QuadrimonName::e_QuadrimonName(best_matchs_info_[i].indice);
#ifdef DEBUG
				qDebug() << std::to_string(quadrimon_scanned_[i]) + " scanned quadrimon";
#endif
			}
			else
			{
				// Cast of the card index to a TerrainName enum, the value of the quadrimon number is substracted to 
				//have card index that start at 0
				terrain_scanned_[i] = E_TerrainName::e_TerrainName(best_matchs_info_[i].indice - E_QuadrimonName::E_END);
#ifdef DEBUG
				qDebug() << std::to_string(quadrimon_scanned_[i]) + " scanned terrain";
#endif
			}
		}
	}
}

std::tuple<E_QuadrimonName::e_QuadrimonName, E_TerrainName::e_TerrainName> CardReader::getPlayerCards(E_Player::e_Player player)
{
	if (player < E_Player::E_END)
	{
		E_QuadrimonName::e_QuadrimonName quadrimon = quadrimon_scanned_[1 - player];
		quadrimon_scanned_[1 - player] = E_QuadrimonName::E_END;
		E_TerrainName::e_TerrainName terrain = terrain_scanned_[1 - player];
		terrain_scanned_[1 - player] = E_TerrainName::E_END;
		return { quadrimon, terrain };
	}
	return { E_QuadrimonName::E_END, E_TerrainName::E_END };
}

E_QuadrimonName::e_QuadrimonName CardReader::getPlayerQuadrimon(E_Player::e_Player player)
{
	if (player < E_Player::E_END)
	{
		E_QuadrimonName::e_QuadrimonName quadrimon = quadrimon_scanned_[1 - player];
		quadrimon_scanned_[1 - player] = E_QuadrimonName::E_END;
		return quadrimon;
	}
	return E_QuadrimonName::E_END;
}

E_TerrainName::e_TerrainName CardReader::getPlayerTerrain(E_Player::e_Player player)
{
	if (player < E_Player::E_END)
	{
		E_TerrainName::e_TerrainName terrain = terrain_scanned_[1 - player];
		terrain_scanned_[1 - player] = E_TerrainName::E_END;
		return terrain;
	}
	return E_TerrainName::E_END;
}

#ifdef DEBUG
void CardReader::setCardScanned(int card_value, bool player, bool quadrimon)
{
	if (quadrimon)
	{
		quadrimon_scanned_[1 - player] = E_QuadrimonName::e_QuadrimonName(card_value);
	}
	else
	{
		terrain_scanned_[1 - player] = E_TerrainName::e_TerrainName(card_value);
	}
}
#endif

void CardReader::matching(const cv::Mat& ref_descriptor, const cv::Mat& tested_descriptor, int* match_value)
{
	std::vector<cv::DMatch> good_matches;
	std::vector<std::vector<cv::DMatch>> knn_matches;

	matcher_.knnMatch(ref_descriptor, tested_descriptor, knn_matches, 2);

	// Filter matches using Lowe's ratio test
	if (knn_matches.size() != 0 && knn_matches[0].size() > 1)
	{
		constexpr float ratio_thresh = 0.7;
		for (size_t i = 0; i < knn_matches.size(); i++) {
			if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance) {
				good_matches.push_back(knn_matches[i][0]);
			}
		}
		if (good_matches.size() > 30)
		{
			*match_value = good_matches.size();
		}
	}
}

void CardReader::treatImage(const cv::Mat& image_tested, std::array<std::future<void>, CARD_NUMBER>& threads, const std::array<cv::Mat, CARD_NUMBER>& descriptors, std::array<int, CARD_NUMBER>& matchs, IntIndPair& best_match)
{
	std::vector<cv::KeyPoint> keypoints_tested;
	cv::Mat descriptors_tested;

	orb_->detectAndCompute(image_tested, cv::noArray(), keypoints_tested, descriptors_tested);
	//Match descriptors using brute-force matcher
	bool cont = true;
	best_match.value = 0;
	if (!descriptors_tested.empty())
	{
		for (int i = 0; i < CARD_NUMBER; i++)
		{
			threads[i] = std::async(std::launch::async, &matching, std::cref(descriptors[i]), std::cref(descriptors_tested), &(matchs[i]));//std::thread(&matching, std::cref(descriptors[i]), std::cref(descriptors_tested), &(matchs[i]));

		}
		for (int i = 0; i < CARD_NUMBER; i++)
		{
			threads[i].wait();
			if (matchs[i] > best_match.value)
			{
				best_match.value = matchs[i];
				best_match.indice = i;
			}
			matchs[i] = 0;
		}
	}
}
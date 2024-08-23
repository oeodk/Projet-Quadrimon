#include "data_struct/LabelElementChange.h"

void LabelElementChange::setText(const std::string& text)
{
	text_ = text;
	refresh_text_ = true;
}

void LabelElementChange::setImage(const std::string& path)
{
	text_ = path;
	refresh_image_ = true;
}

const std::string& LabelElementChange::getText()
{
	refresh_text_ = false;
	refresh_image_ = false;
	return text_;
}

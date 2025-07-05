
#include "SpiritViewModel.h"

//methods

bool SpiritViewModel::initialize()
{
	char buffer[FL_PATH_MAX];
	fl_getcwd(buffer, FL_PATH_MAX);
	std::string str(buffer);
	if (str.back() != '/' && str.back() != '\\')
		str += '/';
	str += "code/assets/";
	m_player = std::make_unique<Fl_PNG_Image>((str + "player.png").c_str());
	if (m_player->fail())
		return false;

	m_snow = std::make_unique<Fl_PNG_Image>((str + "snow.png").c_str());
	if (m_snow->fail())
		return false;

	m_stone = std::make_unique<Fl_PNG_Image>((str + "stone.png").c_str());
	if (m_stone->fail())
		return false;
	return true;
}


#include "SpiritViewModel.h"

//methods

bool SpiritViewModel::initialize()
{
	char buffer[FL_PATH_MAX];
	fl_getcwd(buffer, FL_PATH_MAX);
	std::string str(buffer);
	if (str.back() != '/' && str.back() != '\\')
		str += '/';
	str += "assets/";
	m_player = std::make_unique<RotatableCharacter>(0,0,100,90,(str + "player.png").c_str());
	if (m_player->fail())
		return false;

	//合成了一下变成宽99了
	m_player_penguin = std::make_unique<RotatableCharacter>(0,0,99,90,(str + "player_penguin.png").c_str());
	if (m_player_penguin->fail())
		return false;

	m_snow = std::make_unique<Fl_PNG_Image>((str + "snow.png").c_str());
	if (m_snow->fail())
		return false;

	m_stone = std::make_unique<Fl_PNG_Image>((str + "stone.png").c_str());
	if (m_stone->fail())
		return false;

	m_penguin = std::make_unique<Fl_PNG_Image>((str + "penguin.png").c_str());
	if (m_penguin->fail())
		return false;

	m_background = std::make_unique<Fl_PNG_Image>((str + "background.png").c_str());
	if (m_background->fail())
		return false;

	m_start_image = std::make_unique<Fl_PNG_Image>((str + "background.png").c_str());
	if (m_start_image->fail())
	return false;
	return true;
}

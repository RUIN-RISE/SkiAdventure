
#include "../GameViewModel.h"

//开始游戏/重开游戏
std::function<bool()> GameViewModel::get_start_command()
{
	return [this]()->bool
		{
			return this->start_game();
		};
}


#include "../GameViewModel.h"

//开始游戏/重开游戏
std::function<bool(int)> GameViewModel::get_start_command()
{
	return [this](int R)->bool
		{
			return this->start_game(R);
		};
}

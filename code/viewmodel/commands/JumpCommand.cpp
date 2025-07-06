
#include "../GameViewModel.h"

//不在空中则起跳，否则空翻，逆时针旋转
std::function<void()> GameViewModel::get_jump_command()
{
	return [this]()->void
		{
			this->jump();
		};
}


#include "../GameViewModel.h"

std::function<void()> GameViewModel::get_jump_command()
{
	return [this]()->void
		{
			this->jump();
		};
}

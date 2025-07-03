
#include "../GameViewModel.h"

std::function<void(int)> GameViewModel::get_next_step_command()
{
	return [this](int turn)->void
		{
			this->next_step(turn);
		};
}

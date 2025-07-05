
#include "../common/property_ids.h"

#include "GameViewModel.h"

// GameViewModel::GameViewModel()
// {

// }

//methods

void GameViewModel::next_step(int turn)
{
	// std::cerr << "next_step" << std::endl;
	this->plm.update_game(&this->FullCurve);
	fire(PROP_ID_MAP);
}

void GameViewModel::jump(){
	this->plm.jump(&this->FullCurve);
}

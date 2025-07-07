
#include "../common/property_ids.h"

#include "GameViewModel.h"

GameViewModel::GameViewModel()
{
	GameStatus = 0 ;
}

//methods

void GameViewModel::next_step(int turn)
{
	// std::cerr << "next_step" << std::endl;
	if(GameStatus == 0) return ;
	this->plm.update_game(&this->FullCurve);
	this->pgm.update_penguin(&this->FullCurve,&this->plm);
	fire(PROP_ID_MAP);
}

void GameViewModel::jump(){
	if(GameStatus == 0) return ;
	this->plm.jump(&this->FullCurve);
}

bool GameViewModel::start_game(){
	if(GameStatus == 1) return false ;
	GameStatus = 1;
	this->plm.reset();
	this->FullCurve.reset();
	this->pgm.reset(&this->FullCurve,0);
	return true ;
}

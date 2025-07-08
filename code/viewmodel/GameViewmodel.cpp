
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
	if(GameStatus == 1){
		this->plm.update_game(&this->FullCurve);
		this->pgm.update_penguin(&this->FullCurve,&this->plm);		
	}
	this->FullCurve.update_slide(this->plm.getPosition().x);
	if(this->plm.game_end())
		GameStatus = 2; // 结束
	fire(PROP_ID_MAP);
}

void GameViewModel::jump(){
	if(GameStatus != 1) return ;
	this->plm.jump(&this->FullCurve);
}

bool GameViewModel::start_game(int R){
	if(GameStatus == 1) return false ;
	if(GameStatus == 2 && R == 0) return false ;
	GameStatus = 1;
	this->plm.reset();
	this->FullCurve.reset();
	this->pgm.reset(&this->FullCurve,0);
	return true ;
}

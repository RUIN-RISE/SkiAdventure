
#include "../common/property_ids.h"

#include "GameViewModel.h"

// GameViewModel::GameViewModel()
// {

// }

//methods

void GameViewModel::next_step(int turn)
{
	this->plm.update_onCurve(&this->FullCurve);
	fire(PROP_ID_MAP);
}

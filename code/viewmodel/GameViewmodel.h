#ifndef __GAME_VIEW_MODEL_H__
#define __GAME_VIEW_MODEL_H__

#include "../common/frame.h"
#include "../model/Model.h"


class GameViewModel : public PropertyTrigger
{
public:
	GameViewModel() = default;
	GameViewModel(const GameViewModel&) = delete;
	~GameViewModel() noexcept
	{
	}

	GameViewModel& operator=(const GameViewModel&) = delete;

//properties
	const Curve& getVisibleCurve() const noexcept{
		return FullCurve;
	}
	Vector getPlayerPosition() const {
		return plm.getPosition();
	}

//commands
	std::function<void(int)> get_next_step_command();

//methods
	void next_step(int turn);

private:
//properties
	SnowCurve FullCurve;
	PlayerModel plm;
};

#endif

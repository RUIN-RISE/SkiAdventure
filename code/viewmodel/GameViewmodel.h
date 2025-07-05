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
	const Curve* getVisibleCurve() const noexcept{
		return &FullCurve;
	}
	const Vector* getPlayerPosition() const {
		return &plm.getPosition();
	}
	const PhysicsEntity* getPlayerInstance() const {
		return &plm;
	}

	const double* getStonePosition() const {
		return &FullCurve.get_stone();
	}

//commands
	std::function<void(int)> get_next_step_command();
	std::function<void()> get_jump_command();

//methods
	void next_step(int turn);
	void jump();

private:
//properties
	SnowCurve FullCurve;
	PlayerModel plm;
};

#endif

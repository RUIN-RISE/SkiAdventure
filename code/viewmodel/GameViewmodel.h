#ifndef __GAME_VIEW_MODEL_H__
#define __GAME_VIEW_MODEL_H__

#include "../common/frame.h"
#include "../model/Model.h"
#include "../model/Penguin.h"

class GameViewModel : public PropertyTrigger
{
public:
	GameViewModel();
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
	const PhysicsEntity* getPenguinInstance() const {
		return &pgm;
	}

	const double* getStonePosition() const {
		return &FullCurve.get_stone();
	}
	const double* getSlidePosition() const {
		return &FullCurve.get_slide();
	}
	const bool* getPenguinOn() const {
		return &plm.get_penguin();
	}
	const int* getGameStatus() const {
		return &GameStatus;
	}

//commands
	std::function<void(int)> get_next_step_command();
	std::function<void()> get_jump_command();
	std::function<bool(int)> get_start_command();

//methods
	void next_step(int turn);
	void jump();
	bool start_game(int R);

private:
//properties
	SnowCurve FullCurve;
	PlayerModel plm;
	PenguinModel pgm;
	int GameStatus; // 0->stop(wait to start)
};

#endif

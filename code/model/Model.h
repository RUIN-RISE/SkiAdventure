#include "../common/Curve.h"
#include "../common/PhysicsEntity.h"
#include "../common/Timer.h"

class SnowCurve : public Curve{
	public:
		const double &get_stone() const {
			return stone ;
		}
		void set_stone(const double &s) {
			stone = s;
		}
		SnowCurve(): Curve(
			std::vector<Vector>{
				Vector(2000,-400),
				Vector(500,-300),
				Vector(1000,-200),
				Vector(500,-500),
				Vector(2000,-400),
				Vector(500,-800),
			}
		), stone(-2000){
			srand(time(0));
		}
	private:
		double stone; // the x of stone
};

class PlayerModel : public PhysicsEntity{
	public:
		PlayerModel():PhysicsEntity(
			Vector(0,0),
			Vector(1000,0),
			Vector(0,-2000),
			0,
			true
		){
			// setOnCurve(true);
			dizzy = false ;
		}
		void update_game(SnowCurve *SC);
		void jump(SnowCurve *SC);
	private:
		void update_onCurve(SnowCurve *SC);
		void update_offCurve(SnowCurve *SC);
		void get_dizzy();
		Timer dizzy_time;
		bool dizzy;
};

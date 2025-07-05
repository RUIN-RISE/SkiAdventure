#include "../common/Curve.h"
#include "../common/PhysicsEntity.h"

class SnowCurve : public Curve{
	public:
		const double &get_stone() const {
			return stone ;
		}
		void set_stone(const double &s) {
			stone = s;
		}
		SnowCurve(){
			stone = -2000; // 开局不要有石头
			srand(time(0));
		}
	private:
		double stone; // the x of stone
};

class PlayerModel : public PhysicsEntity{
	public:
		PlayerModel():PhysicsEntity(
			Vector(0,0),
			Vector(500,0),
			Vector(0,-1000),
			0,
			true
		){
			// setOnCurve(true);
		}
		void update_player(SnowCurve *SC);
		void jump();
	private:
		void update_onCurve(SnowCurve *SC);
		void update_offCurve(SnowCurve *SC);
};

#include "../common/Curve.h"
#include "../common/PhysicsEntity.h"

class SnowCurve : public Curve{

};

class PlayerModel : public PhysicsEntity{
	public:
		PlayerModel():PhysicsEntity(
			Vector(0,0),
			Vector(1000,0),
			Vector(0,-500),
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

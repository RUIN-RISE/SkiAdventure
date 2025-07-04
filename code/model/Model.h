#include "../common/Curve.h"
#include "../common/PhysicsEntity.h"

class SnowCurve : public Curve{

};

class PlayerModel : public PhysicsEntity{
	public:
		PlayerModel():PhysicsEntity(
			Vector(0,0),
			Vector(100,0),
			Vector(0,-100),
			true
		){
			// setOnCurve(true);
		}
		void update_onCurve(SnowCurve *SC);
};

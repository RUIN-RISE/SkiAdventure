#include "../common/Curve.h"
#include "../common/PhysicsEntity.h"

class SnowCurve : public Curve{

};

class PlayerModel : public PhysicsEntity{
	public:
		PlayerModel(){
			setOnCurve(true);
		}
		void update_onCurve(SnowCurve *SC);
};

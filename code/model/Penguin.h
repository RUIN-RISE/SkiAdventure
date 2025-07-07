#ifndef __Penguin_H
#define __Penguin_H

#include "../common/PhysicsEntity.h"
#include "Model.h"

class PenguinModel : public PhysicsEntity {
	public:
		PenguinModel():PhysicsEntity(
			Vector(-5000,0),
			Vector(1000,0),
			Vector(0,-2000),
			0,
			true
		){

		}
		void update_penguin(SnowCurve *SC,double px);
		void update_onCurve(SnowCurve *SC);
		void reset(SnowCurve *SC,double px);
};

#endif

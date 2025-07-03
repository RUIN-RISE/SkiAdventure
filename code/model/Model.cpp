#include "Model.h"

void PlayerModel::update_onCurve(SnowCurve *SC){
	double ox = this->getPosition().x; // old x
	this->update(deltaTime);
	
	double nx = this->getPosition().x; // new x
	Vector CurvePos(nx,SC->evaluate(nx));
	this->setPosition(CurvePos);

	double k = SC->derivative(ox); //scope of old x
	Vector unit_scope = Vector(1,k)/sqrt(1+k*k);
	Vector CurveVel = unit_scope*(this->getVelocity()*unit_scope);
	this->setVelocity(CurveVel);
}

#include "Model.h"

void PlayerModel::update_player(SnowCurve *SC){
	std::cerr << "Update_player : oncurve : " << isOnCurve() << std::endl ;
	std::cerr << "Velocity : " << this->getVelocity().x << " " << this->getVelocity().y << std::endl ;
	if(isOnCurve()) update_onCurve(SC);
	else update_offCurve(SC);
}

void PlayerModel::update_onCurve(SnowCurve *SC){
	// std::cerr << "Old Player Position : " << this->getPosition().x << ' ' << this->getPosition().y << std::endl;
	double ox = this->getPosition().x; // old x
	this->update(deltaTime);

	double nx = this->getPosition().x; // new x
	Vector CurvePos(nx,SC->evaluate(nx));
	// std::cerr << "New Player Position : " << nx << ' ' << SC->evaluate(nx) << std::endl;
	this->setPosition(CurvePos);

	Vector unit_scope = SC->tangent(ox);
	unit_scope.normalize();
	Vector CurveVel = unit_scope*(this->getVelocity()*unit_scope);
	this->setVelocity(CurveVel - unit_scope * 10); // friction
}

void PlayerModel::update_offCurve(SnowCurve *SC){
	double ox = this->getPosition().x;
	this->update(deltaTime);

	double nx = this->getPosition().x;
	Vector CurvePos(nx,SC->evaluate(nx));

	if(this->getPosition().y <= CurvePos.y){
		setOnCurve(true) ;

		this->setPosition(CurvePos);

		/*
		下一帧再更新速度
		double k = SC->derivative(ox); //scope of old x
		Vector unit_scope = Vector(1,k)/sqrt(1+k*k);
		Vector CurveVel = unit_scope*(this->getVelocity()*unit_scope);
		this->setVelocity(CurveVel);
		*/
	}

}

void PlayerModel::jump(SnowCurve *SC){
	if(isOnCurve() == false){
		std::cerr << "Jump in air" << std::endl ;
		return ;
	}
	setOnCurve(false);
	Vector ov = this->getVelocity();
	double ox = this->getPosition().x;
	Vector normal = SC->tangent(ox).orthogonal();
	ov += normal * 500;
	this->setVelocity(ov);
}

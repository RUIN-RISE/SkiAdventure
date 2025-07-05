#include "Model.h"

const int offset = 1000 ;
const double alpha = 0.99 ;
const double Vec_lim_in_air = 1500 ;

void PlayerModel::update_player(SnowCurve *SC){
	std::cerr << "Update_player : oncurve : " << isOnCurve() << std::endl ;
	std::cerr << "Velocity : " << this->getVelocity().x << " " << this->getVelocity().y << std::endl ;
	if(SC->get_stone() < this->getPosition().x - offset){
		SC->set_stone(this->getPosition().x + offset + (rand()%(offset * 2)));
	}
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

	double k = SC->derivative(ox); //scope of old x
	Vector unit_scope = Vector(1,k)/sqrt(1+k*k);
	Vector CurveVel = unit_scope*(this->getVelocity()*unit_scope);
	this->setVelocity(CurveVel);
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
	if(this->getVelocity().x >= Vec_lim_in_air){
		Vector NexVel = this->getVelocity();
		NexVel.x *= alpha ;
		this->setVelocity(NexVel);
	}
}

void PlayerModel::jump(){
	if(isOnCurve() == false){
		std::cerr << "Jump in air" << std::endl ;
		return ;
	}
	setOnCurve(false);
	Vector ov = this->getVelocity();
	ov.y = 30 ;
	this->setVelocity(ov);
}

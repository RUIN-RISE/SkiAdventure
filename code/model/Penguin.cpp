#include "Penguin.h"

const int offset = 2000 ;
const double penguin_alpha = 0.8;
const double eps = 50.0 ;

void PenguinModel::update_penguin(SnowCurve *SC,PlayerModel *plm){
	double px = plm->getPosition().x;
	double x =  this->getPosition().x;
	if(dist(plm->getPosition(),this->getPosition()) <= eps && plm->is_dizzy() == false){
		std::cerr << "Caught Penguin";
		plm->set_penguin(true);
		this->reset(SC,px);
	}

	if(x <= px - offset || x >= px + offset) this->reset(SC,px);
	this->update_onCurve(SC);
}

void PenguinModel::update_onCurve(SnowCurve *SC){
	// std::cerr << "Old Penguin Position : " << this->getPosition().x << ' ' << this->getPosition().y << std::endl;
	double ox = this->getPosition().x; // old x
	this->update(deltaTime,penguin_alpha); // 有必要给 penguin 减速，否则追不上

	double nx = this->getPosition().x; // new x
	Vector CurvePos(nx,SC->evaluate(nx));
	// std::cerr << "New Penguin Position : " << nx << ' ' << SC->evaluate(nx) << std::endl;
	this->setPosition(CurvePos);

	Vector unit_scope = SC->tangent(ox);
	unit_scope.normalize();
	Vector CurveVel = unit_scope*(this->getVelocity()*unit_scope);
	this->setVelocity(CurveVel - unit_scope * 2); // friction
}

void PenguinModel::reset(SnowCurve *SC,double px){
	double nx = px + offset + (rand() % offset);
	Vector CurvePos(nx,SC->evaluate(nx));
	this->setPosition(CurvePos);
	this->setVelocity(Vector(1000,0));
}

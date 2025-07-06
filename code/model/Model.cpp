#include "Model.h"

const int offset = 1500 ;
const double alpha = 0.99 ;
const double Vec_lim_in_air = 3500 ;

const double eps = 50.0 ;
const double DizzyTime = 2.0 ;

double dist(const Vector &a,const Vector &b){
	double ax = a.x,ay = a.y;
	double bx = b.x,by = b.y;
	return sqrt((ax-bx)*(ax-bx) + (ay-by)*(ay-by));
}

void PlayerModel::get_dizzy(){
	dizzy_time.reset() ;
	dizzy = true ;
	this->setVelocity(Vector(1000,0));
	this->setAngle(Angle());
}

void PlayerModel::update_game(SnowCurve *SC){
	std::cerr << "Update_player : oncurve : " << isOnCurve() << std::endl ;
	std::cerr << "Velocity : " << this->getVelocity().x << " " << this->getVelocity().y << std::endl ;
	std::cerr << "Angle : " << this->getAngle().deg() << " " << this->getVelocity().y << std::endl ;
	double px = this->getPosition().x;
	double sx = SC->get_stone();
	
	if(sx < px - offset){
		SC->set_stone(px + offset + (rand()%(offset * 2)));
		sx = SC->get_stone();
	}

	//Check if fall against stone
	if(dist(this->getPosition(),Vector(sx,SC->evaluate(sx))) <= eps){
		SC->set_stone(sx + offset * 2 + (rand()%(offset * 2)));
		sx = SC->get_stone();
		this->get_dizzy();
		this->setPosition(Vector(px,SC->evaluate(px)));
	}
	if(dizzy && dizzy_time.elapsed() > DizzyTime){
		dizzy = false ;
	}
	if(dizzy == false){
		if(isOnCurve()) update_onCurve(SC);
		else update_offCurve(SC);
	}
	else {
		std::cerr << "dizzy_time : " << dizzy_time.elapsed() << std::endl ;
	}
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
	this->setVelocity(CurveVel - unit_scope * 5); // friction
}

const double delta_theta = 8.0 ;
const double eps_theta = 1.0 ; // rad

void PlayerModel::update_offCurve(SnowCurve *SC){
	double ox = this->getPosition().x;
	this->update(deltaTime);

	double nx = this->getPosition().x;
	Vector CurvePos(nx,SC->evaluate(nx));

	if(this->getPosition().y <= CurvePos.y){
		setOnCurve(true) ;

		this->setPosition(CurvePos);
		//检查落地角度，判断是否晕眩
		Angle angle = this->getAngle();
		Angle SC_angle = SC->tangent(nx).angle();
		Angle horizon = Angle();
		
		if(!angle.is_between((SC_angle-eps_theta).rad(),(SC_angle+eps_theta).rad())
			&& !angle.is_between((horizon-eps_theta).rad(),(horizon+eps_theta).rad())
		){
			this->get_dizzy();
		}
		std::cerr << "Dizzy Check! angle , SC_angle : " << angle.deg() << ' ' << SC_angle.deg() << std::endl ;


		this->setAngle(Angle());

		/*
		下一帧再更新速度
		*/
	}
	else{
		Angle angle = this->getAngle();
		if(angle.deg() >= 180.0){
			angle += Angle::from_degree(delta_theta / 3) ;
			if(angle.deg() < 180) angle = Angle();
		}
		else{
			angle -= Angle::from_degree(delta_theta / 3) ;
			if(angle.deg() > 180) angle = Angle();
		}
		this->setAngle(angle);
	}
}

void PlayerModel::jump(SnowCurve *SC){
	if(dizzy) return ;
	if(isOnCurve() == false){
		std::cerr << "Jump in air" << std::endl ;
		
		Angle angle = this->getAngle() ;
		angle += Angle::from_degree(delta_theta) ;
		this->setAngle(angle);
		
		return ;
	}
	setOnCurve(false);
	Vector ov = this->getVelocity();
	double ox = this->getPosition().x;
	Vector normal = SC->tangent(ox).orthogonal();
	ov += normal * 800;
	this->setVelocity(ov);
}

void PlayerModel::reset(){
	this->setPosition(Vector(0,0));
	this->setVelocity(Vector(1000,0));
	this->setOnCurve(true);
	this->dizzy = false ;
}

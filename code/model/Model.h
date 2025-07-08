#ifndef __Model__H
#define __Model__H

#include "../common/Curve.h"
#include "../common/PhysicsEntity.h"
#include "../common/Timer.h"

const double vec_lim_x = 5000;

class SnowCurve : public Curve{
	public:
		SnowCurve(): Curve(
			std::vector<Vector>{
				Vector(2000,-400),
				Vector(500,-300),
				Vector(1000,-200),
				Vector(500,-500),
				Vector(2000,-400),
				Vector(500,-800),
			}
		), stone(-2000){
			srand(time(0));
			slide = -3000 ;
		}
		
		const double &get_stone() const {
			return stone ;
		}
		void set_stone(const double &s) {
			stone = s;
		}

		const double &get_slide() const {
			return slide ;
		}

		void reset(){
			stone = -2000 ;
			slide = -3000 ;
		}
		void update_slide(double px);
	private:
		double stone; // the x of stone
		double slide; // 雪崩的 x 坐标
};

class PlayerModel : public PhysicsEntity{
	public:
		PlayerModel():PhysicsEntity(
			Vector(0,0),
			Vector(1000,0),
			Vector(0,-2000),
			Angle(-0.75), //与初始位置雪坡相切
			true
		){
			// setOnCurve(true);
			dizzy = false ;
			Penguin_ = false ;
			end = false ;
		}
		void update_game(SnowCurve *SC);
		void jump(SnowCurve *SC);
		void reset();

		void set_penguin(bool p);
		const bool &get_penguin() const {
			return Penguin_ ;
		}

		bool is_dizzy() const {
			return dizzy ;
		}
		bool game_end() const {
			return end ;
		}

	private:
		void update_onCurve(SnowCurve *SC);
		void update_offCurve(SnowCurve *SC);
		void get_dizzy();

		void speed_bonus(){
			Vector curVel = this->getVelocity() ;
			curVel += Vector(1000,0);

			//限速，否则速度太快渲染不动（
			if(curVel.x >= vec_lim_x)
				curVel.x = vec_lim_x;
			this->setVelocity(curVel);
		}
		void speed_penalty(){
			Vector curVel = this->getVelocity() ;
			curVel *= 0.8;
			this->setVelocity(curVel);
		}

		Timer dizzy_time;
		bool dizzy;
		bool Penguin_ ;

		int cycles;
		bool end ;
};

#endif

#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "Vector.h"
#include "bump_system.h"
class player
{
public:
	player(double x, double y, double z) : position(x,y,z), forward(-1.0, 0.0, 0.0){
		speed = 0.002;
		HP = 100;
		zoom = false;
		score = 0;
		theta = 0.001;
		move_state[0] = move_state[1] = move_state[2] = move_state[3] = false;
	}

	void move();

	void set_move_state(int bit, bool mode){
		move_state[bit] = mode;
	}

	Vector get_forward(){
		return forward;
	}

	Vector get_position(){
		return position;
	}

	void set_forward(Vector v){
		forward = v;
	}

	void set_position(Vector v){
		position = v;
	}

	int get_HP(){
		return HP;
	}

	int get_score(){
		return score;
	}

	void change_zoom(){
		zoom = !zoom;
	}

	bool get_zoom(){
		return zoom;
	}

private:
	bool move_state[4];// front: 0, back: 1, left: 2, right: 3
	bool zoom;
	int HP;
	int score;
	double speed;
	double theta;
	Vector forward;
	Vector position;
};
#endif


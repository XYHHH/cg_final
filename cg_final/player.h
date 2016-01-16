#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "Vector.h"
#include "rigidObj.h"
#include "bullet.h"
#include "bump_system.h"
class player: public rigidObj
{
public:
	player(double x, double y, double z) {
		position = Vector(x,y,z);
		forward = Vector(-1.0, 0.0, 0.0);
		radius = 0.1;
		height = 1;
		speed = 0.002;
		HP = 100;
		zoom = false;
		score = 0;
		theta = 0.001;
		gravity = 0.0002;
		vertical_speed = 0;
		move_state[0] = move_state[1] = move_state[2] = move_state[3] = roam = false;
	}

	void move();

	void set_move_state(int bit, bool mode){ move_state[bit] = mode;}

	void change_roam(){ roam = !roam; vertical_speed = 0; }

	int get_HP(){ return HP; }

	int get_score(){ return score; }

	void change_zoom(){ zoom = !zoom; }

	bool get_zoom(){ return zoom; }

	bullet* shoot();

	virtual void drop();
private:
	bool move_state[4];// front: 0, back: 1, left: 2, right: 3
	bool roam;
	bool zoom;
	int HP;
	int score;
	double speed;
	double theta;

};
#endif


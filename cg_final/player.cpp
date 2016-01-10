#include "player.h"

void player::move(){ // front: 0, back: 1, left: 2, right: 3
	double rate = sqrt((forward.x * forward.x) + (forward.y * forward.y));
	double delta;
	if (move_state[0]){
		delta = forward.x / rate * speed;
		if (BUMP_SYSTEM::check_bump(this,0,delta))
			position.x += delta;
		delta = forward.y / rate * speed;
		if (BUMP_SYSTEM::check_bump(this,1,delta))
			position.y += delta;
	}
	if (move_state[1]){
		delta = forward.x / rate * speed;
		if (BUMP_SYSTEM::check_bump(this,0,delta))
			position.x += delta;
		delta = -(forward.y / rate * speed);
		if (BUMP_SYSTEM::check_bump(this,1,delta))
			position.y += delta;
	}
	if (move_state[2]){
		delta = -(forward.y / rate * speed);
		if (BUMP_SYSTEM::check_bump(this, 0, delta))
			position.x += delta;
		delta = forward.x / rate * speed;
		if (BUMP_SYSTEM::check_bump(this, 1, delta))
			position.y += delta;
	}
	if (move_state[3]){
		delta = forward.y / rate * speed;
		if (BUMP_SYSTEM::check_bump(this, 0, delta))
			position.x += delta;
		delta = -(forward.x / rate * speed);
		if (BUMP_SYSTEM::check_bump(this, 1, delta))
			position.y += delta;
	}
}
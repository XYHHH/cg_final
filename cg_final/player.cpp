#include "player.h"

void player::move(){ // front: 0, back: 1, left: 2, right: 3
	double rate = sqrt((forward.x * forward.x) + (forward.y * forward.y));

	if (move_state[0]){
		if (BUMP_SYSTEM::check_bump()) //TODO, check x forward
			position.x += forward.x / rate * speed;
		if (BUMP_SYSTEM::check_bump()) //TODO, check y forward
			position.y += forward.y / rate * speed;
	}
	if (move_state[1]){
		if (BUMP_SYSTEM::check_bump()) //TODO, check x forward
			position.x += forward.x / rate * speed;
		if (BUMP_SYSTEM::check_bump()) //TODO, check y forward
			position.y -= forward.y / rate * speed;
	}
	if (move_state[2]){
		if (BUMP_SYSTEM::check_bump()) //TODO, check x forward
			position.x -= forward.y / rate * speed;
		if (BUMP_SYSTEM::check_bump()) //TODO, check y forward
			position.y += forward.x / rate * speed;
	}
	if (move_state[3]){
		if (BUMP_SYSTEM::check_bump()) //TODO, check x forward
			position.x += forward.y / rate * speed;
		if (BUMP_SYSTEM::check_bump())
			position.y -= forward.x / rate * speed;
	}
}
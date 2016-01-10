#ifndef BUMP_SYSTEM_H
#define BUMP_SYSTEM_H
#include "player.h"
#include "monster.h"
#include "Vector.h"
#include "rigidObj.h"
#include "map.h"
class BUMP_SYSTEM
{
public:
	BUMP_SYSTEM(){}
	static bool check_bump(rigidObj* obj, int direction, double delta){//direction 0:x, 1:y
		Vector position = obj->get_position();
		double radius = obj->get_radius();
		if (direction == 0){
			int left = mazeMap[int(position.x + delta - radius + 0.5)][int(position.y + 0.5)];
			int right = mazeMap[int(position.x + delta + radius + 0.5)][int(position.y + 0.5)];
			return (left==0) && (right==0);
		}
		else{
			int top = mazeMap[int(position.x + 0.5)][int(position.y + delta + radius + 0.5)];
			int bottom = mazeMap[int(position.x + 0.5)][int(position.y + delta - radius + 0.5)];
			return (top == 0) && (bottom == 0);
		}
	}
	
	static void check_hit(){

	}

};

#endif
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
		double height = obj->get_height();
		if (direction == 0){
			if (position.z < wallHeight + height){
				int left = mazeMap[int(position.x + delta - radius + 0.5)][int(position.y + 0.5)];
				int right = mazeMap[int(position.x + delta + radius + 0.5)][int(position.y + 0.5)];
				return (left == 0) && (right == 0);
			}
			else
				return true;
		}
		else if (direction == 1){
			if (position.z < wallHeight + height){
				int top = mazeMap[int(position.x + 0.5)][int(position.y + delta + radius + 0.5)];
				int bottom = mazeMap[int(position.x + 0.5)][int(position.y + delta - radius + 0.5)];
				return (top == 0) && (bottom == 0);
			}
			else
				return true;
		}
		else{
			int left = mazeMap[int(position.x + delta - radius + 0.5)][int(position.y + 0.5)];
			int right = mazeMap[int(position.x + delta + radius + 0.5)][int(position.y + 0.5)];
			if (left == 0 && right == 0)
				return (position.z + delta > height) && (position.z + delta < wallHeight + 10);
			else
				return (position.z + delta > height + wallHeight) && (position.z + delta < wallHeight + 10);
		}
	}
	
	static void check_hit(){

	}

};

#endif
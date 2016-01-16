#ifndef MONSTER_H
#define MONSTER_H
#include "Vector.h"
#include "rigidObj.h"
class monster: public rigidObj{
public:
	monster(Vector p, Vector f){
		position = p;
		forward = f;
		radius = 0.1;
		height = 1.0;
		gravity = 0.0002;
		vertical_speed = 0;
	}
	void redraw();
private:
	

};

#endif

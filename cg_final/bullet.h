#ifndef BULLET_H
#define BULLET_H

#include "Vector.h"
#include "rigidObj.h"
class bullet : public rigidObj
{
public:
	bullet(Vector p, Vector f) {
		visible = true;
		position = p;
		forward = f;
		speed = 0.01;
		radius = 0.01;
		height = 0.01;
	}
	void move(){ position += (forward * speed); }
	double get_speed(){ return speed; }
	void redraw();
	bool visible;
private:
	double speed;
	double radius;
};

#endif
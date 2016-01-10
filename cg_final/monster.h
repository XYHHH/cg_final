#ifndef MONSTER_H
#define MONSTER_H
#include "Vector.h"

class monster{
public:
	monster();
	void redraw();
private:
	Vector center;
	double rad;
	double height;

};

#endif

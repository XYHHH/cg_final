#ifndef RIGIDOBJ_H
#define RIGIDOBJ_H
#include "Vector.h"

class rigidObj
{
public:
	rigidObj(){}
	rigidObj(Vector p, Vector f, double r, double h):position(p),forward(f),radius(r),height(h){}
	~rigidObj(){}
	Vector get_position(){ return position; }
	Vector get_forward(){ return forward; }
	void set_position(Vector p){ position = p; }
	void set_forward(Vector f){ forward = f; }
	double get_radius(){ return radius; }
	void set_radius(double r){ radius = r; }
	double get_height(){ return height; }
	void set_height(double h){ height = h; }
	virtual void drop(){}
protected:
	Vector position;
	Vector forward;
	double radius;
	double height;
	double gravity;
	double vertical_speed;
};
#endif
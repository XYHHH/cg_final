#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>
class Vector{
public:
	Vector(){}

	Vector(double a, double b, double c):x(a),y(b),z(c){}

	Vector normalize();

	double dot(Vector v);

	Vector operator+(Vector v);

	Vector operator-(Vector v);

	Vector operator*(Vector v);

	double x, y, z;
};
#endif
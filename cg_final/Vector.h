#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>
class Vector{
public:
	Vector(){}

	Vector(double a, double b, double c):x(a),y(b),z(c){}

	Vector(const Vector& v) :x(v.x), y(v.y), z(v.z){}

	Vector normalize();

	double dot(Vector v);

	Vector operator+(Vector v);

	void operator+=(Vector v);

	Vector operator-(Vector v);

	void operator-=(Vector v);

	Vector operator*(Vector v);

	void operator*=(double v);

	Vector operator*(double v);

	void operator=(Vector v);

	bool operator>(Vector v);

	bool operator<(Vector v);

	double x, y, z;
};
#endif
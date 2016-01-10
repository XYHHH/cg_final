#include "Vector.h"
#include <cmath>

Vector Vector::normalize(){
	double n = sqrt(x*x + y*y + z*z);
	return Vector(x / n, y / n, z / n);
}

double Vector::dot(Vector v){
	return x * v.x + y * v.y + z * v.z;
}

Vector Vector::operator+(Vector v){
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(Vector v){
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(Vector v){
	return Vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}
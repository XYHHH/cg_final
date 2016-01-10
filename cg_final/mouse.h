#ifndef MOUSE_H
#define MOUSE_H
#include <GL/glut.h>
#include <cmath>

#include "Vector.h"
#include "player.h"
#define PI 3.14159265358979323846

extern player myPlayer;

void OnMouseClick(int button, int state, int x, int y);

void OnMouseMove(int x, int y);

void FixMouse(int& x, int& y);


#endif

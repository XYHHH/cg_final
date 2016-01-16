#include "mouse.h"
#include <Windows.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include "bump_system.h"
#include "player.h"
#include "bullet.h"

using namespace std;
extern player myPlayer;
extern int windowWidth;
extern int windowHeight;
extern double rotateSpeed;
extern vector<bullet*> bullets;

int lastMouseX = windowWidth / 2;
int lastMouseY = windowHeight / 2;

void FixMouse(int& x, int& y)
{
	
	if (x < windowWidth / 4)
	{
		lastMouseX += windowWidth / 4;
		x += windowWidth / 4;
		SetCursorPos(x, y);
	}
	if (x > windowWidth / 4 * 3)
	{
		lastMouseX -= windowWidth / 4;
		x -= windowWidth / 4;
		SetCursorPos(x, y);
	}
	if (y < windowHeight / 4)
	{
		lastMouseY += windowHeight / 4;
		y += windowHeight / 4;
		SetCursorPos(x, y);
	}
	if (y > windowHeight / 4 * 3)
	{
		lastMouseY -= windowHeight / 4;
		y -= windowHeight / 4;
		SetCursorPos(x, y);
	}
}

void OnMouseMove(int x, int y)
{
	FixMouse(x, y);

	GLdouble horizontalAngle = (GLdouble)(lastMouseX - x) * rotateSpeed / (windowWidth * 2 * PI);
	GLdouble verticalAngle = (GLdouble)(lastMouseY - y) * rotateSpeed / (windowHeight * 2 * PI);
	Vector forward = myPlayer.get_forward();

	double f_x = forward.x * cos(horizontalAngle) - forward.y * sin(horizontalAngle);
	double f_y = forward.x * sin(horizontalAngle) + forward.y * cos(horizontalAngle);
	double f_z = forward.z;

	double v = sqrt(f_x * f_x + f_y * f_y);
	double tmp = (v * cos(verticalAngle) - f_z * sin(verticalAngle)) / v;
	f_x *= tmp;
	f_y *= tmp;
	f_z = v * sin(verticalAngle) + f_z * cos(verticalAngle);

	myPlayer.set_forward(Vector(f_x, f_y, f_z));
	//glutPostRedisplay();
	lastMouseX = x;
	lastMouseY = y;
}

void OnMouseClick(int button, int state, int x, int y)
{
	bullet* p;
	if (state == GLUT_DOWN)
	{
		switch (button){
			case GLUT_LEFT_BUTTON:
				p = myPlayer.shoot();
				bullets.push_back(p);
				break;
			case GLUT_RIGHT_BUTTON:
				myPlayer.change_zoom();
				break;
		}
	}
	glutPostRedisplay();
}

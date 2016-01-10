#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Vector.h"
#include "keyboard.h"
#include "mouse.h"
#include "map.h"
#include "player.h"
#include "UI.h"
using namespace std;

//obj3dmodel myModel;
player myPlayer(2.0,2.0,0.5);
map myMap;
extern int windowWidth;
extern int windowHeight;
extern double viewNear;
extern double viewFar;
extern double viewAngle;

bool gameStart = true;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	if (gameStart){
		Vector position = myPlayer.get_position();
		Vector point = position + myPlayer.get_forward();

		gluLookAt(position.x, position.y, position.z, point.x, point.y, point.z, 0.0, 0.0, 1.0);

		myPlayer.move();
		myMap.redraw();
		showGameUI();
	}
	else{
		showWelcomePage();
	}

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, (GLfloat)w / (GLfloat)h, viewNear, viewFar);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("counter strike");
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//myModel.parse("Resources/monk.obj");
	initUI();

	glutKeyboardFunc(normalKeys);
	glutKeyboardUpFunc(upNormalKeys);

	glutSpecialFunc(specialKeys);
	glutSpecialUpFunc(upSpecialKeys);

	cout << windowWidth << endl;
	cout << windowHeight << endl;
	glutSetCursor(GLUT_CURSOR_NONE);
	SetCursorPos(windowWidth/2, windowHeight/2);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(OnMouseClick);
	glutFullScreen();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}



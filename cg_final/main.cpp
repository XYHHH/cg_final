#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <string>
#include <Windows.h>
#include "texture.h"
#include "Vector.h"
#include "keyboard.h"
#include "mouse.h"
#include "bullet.h"
#include "map.h"
#include "player.h"
#include "OBJ.h"
#include "UI.h"
using namespace std;

//obj3dmodel myModel;
player myPlayer(2.0,2.0,1.0);
Map myMap;
extern int windowWidth;
extern int windowHeight;
extern double viewNear;
extern double viewFar;
extern double viewAngle;
vector<bullet*> bullets;
//OBJ *gun;
bool gameStart = true;

void lightInit()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 10.0, 1.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

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
		/*cout << position.x << position.y << position.z << endl;*/
		gluLookAt(position.x, position.y, position.z, point.x, point.y, point.z, 0.0, 0.0, 1.0);

		//gun->render(1,1,0,0);
		myPlayer.move();
		myMap.redraw();
		BUMP_SYSTEM::check_hit();
		vector<bullet*>::iterator i;
		for (i = bullets.begin(); i != bullets.end(); i++){
			(*i)->move();
			(*i)->redraw();
		}
		showGameUI();
	}
	else{
		showWelcomePage();
	}

	//gluLookAt(3, 3, 3, 0, 0, 0, 0.0, 0.0, 1.0);

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
	initTexture();
	//gun = new OBJ("../cg_final/gun.obj");

	glutKeyboardFunc(normalKeys);
	glutKeyboardUpFunc(upNormalKeys);

	glutSpecialFunc(specialKeys);
	glutSpecialUpFunc(upSpecialKeys);

	//lightInit();
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



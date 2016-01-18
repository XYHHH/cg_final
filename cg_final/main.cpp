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
#include <ctime>
#include <cstdlib>
using namespace std;

player myPlayer(2.0,2.0,1.0);
Map myMap;
extern int windowWidth;
extern int windowHeight;
extern double viewNear;
extern double viewFar;
extern double viewAngle;
vector<bullet*> bullets;
vector<OBJ*> monsters;
OBJ *gun;
//OBJ *drone;
//OBJ *drone1;
bool gameStart = true;

int check_hit_monster(bullet* p){
	int score = 0;
	vector<OBJ*>::iterator i;
	for (i = monsters.begin(); i != monsters.end(); i++)
	{
		if ((*i)->visible){
			Vector center1 = p->get_position();
			Vector center2 = (*i)->get_center();
			Vector diff = center1 - center2;
			double r = (*i)->get_radius();
			if (diff.dot(diff) < r*r){
				(*i)->visible = false;
				p->visible = false;
				score++;
			}
		}
	}
	return score;
}

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
		Vector forward = myPlayer.get_forward();
		/*cout << position.x << position.y << position.z << endl;*/
		gluLookAt(position.x, position.y, position.z, point.x, point.y, point.z, 0.0, 0.0, 1.0);

		myPlayer.move();
		myMap.redraw();
		vector<bullet*>::iterator i;
		for (i = bullets.begin(); i != bullets.end();i++){
			if ((*i)->visible){
				(*i)->move();
				(*i)->redraw();
			}
			if ((*i)->visible && BUMP_SYSTEM::check_hit(*i)){
				(*i)->visible = false;
				cout << "hit wall" << endl;
			}
			if ((*i) -> visible){
				int result = check_hit_monster(*i);
				if (result)
					cout << "hit drone" << endl;
				myPlayer.add_score(result);
			}
		}
		vector<OBJ*>::iterator j;
		for (j = monsters.begin(); j != monsters.end();j++){
			if ((*j)->visible){
				Vector center = (*j)->get_center();
				(*j)->render(center.x, center.y, center.z, 0, 0, 1);
			}
		}
		//drone1->render(5, 1.5, 1.5,0,0,1);
		gun->render(point.x,point.y,point.z,0,0,1);
		//gun->render(point.x,point.y,point.z,forward.x,forward.y,forward.z);
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

void initLight(void)
{
	glShadeModel(GL_FLAT); //选择平面明暗模式或光滑明暗模式
	glEnable(GL_LIGHTING);

	// 光源

	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	//设置并启用光照0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	//启动光源0：
	glEnable(GL_LIGHT0);
	//光的位置：
	GLfloat lightPos[] = { 5.0f, 5.0f, 5.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("counter strike");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	srand(time(0));
	//myModel.parse("Resources/monk.obj");
	initTexture();
	//initLight();
	gun = new OBJ("../cg_final/gun.obj",0.01,0.01,1,0,1,0);
	gun->setScale(0.2);
	//drone = new OBJ("../cg_final/drone.obj", 0, 1, 0, 0, 0, 1);
	//drone1 = new OBJ("../cg_final/drone.obj", 0, 1, 0, 0, 0, 1);
	OBJ* tmp_1;
	OBJ* tmp_2;
	monsters.push_back(tmp_1);
	monsters.push_back(tmp_2);
	vector<OBJ*>::iterator i;
	for (i = monsters.begin(); i != monsters.end(); i++){
		(*i) = new OBJ("../cg_final/drone.obj", 0, 1, 0, 0, 0, 1);
		(*i)->setScale(0.3*rand()/RAND_MAX+0.2);
	}
	monsters[0]->set_center(Vector(1.5, 5, 1));
	monsters[1]->set_center(Vector(5, 1.5, 1));
	//drone->setScale(0.2);
	//drone1->setScale(0.3);
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



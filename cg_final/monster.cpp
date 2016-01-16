#include "monster.h"
#include <GL/glut.h>
void monster::redraw(){
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(0.8f, 0.3f, 0.6f);
	//glutSolidSphere(radius, 32, 32);
	glScalef(1,1,height);
	glutSolidCube(1);
	glPopMatrix();
}
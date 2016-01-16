#include "bullet.h"
#include <GL/glut.h>

void bullet::redraw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(0.2f,0.2f,0.2f);
	glutSolidSphere(radius, 32, 32);
	glPopMatrix();

}
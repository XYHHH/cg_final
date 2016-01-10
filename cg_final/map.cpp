#include "map.h"
#include <GL/glut.h>
void map::redraw(){
	//draw ground
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-5.0f, -5.0f, -0.5f);
	glVertex3f(-5.0f, 14.0f, -0.5f);
	glVertex3f(14.0f, 14.0f, -0.5f);
	glVertex3f(14.0f, -5.0f, -0.5f);
	glEnd();

	//draw sky
	glBegin(GL_QUADS);
	glColor3f(0.6f, 0.6f, 0.6f);
	glVertex3f(-5.0f, -5.0f, 10.5f);
	glVertex3f(-5.0f, 14.0f, 10.5f);
	glVertex3f(14.0f, 14.0f, 10.5f);
	glVertex3f(14.0f, -5.0f, 10.5f);
	glEnd();


	// draw wall
	for (int i = 0; i < 10 * 10; i++){
		if (mazeMap[i] == 1){
			glPushMatrix();
			glScalef(1, 1, 1);
			glTranslatef(i / 10, i % 10, 0);

			//立方体轮廓
			glColor3f(0.0f, 0.0f, 0.0f);
			glLineWidth(1.5f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glutSolidCube(1);

			//实心立方体 
			glColor3f(1.0f, 1.0f, 1.0f);

			glPolygonOffset(-1.5, -1.0f);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glutSolidCube(1);

			glPopMatrix();
		}
	}
}
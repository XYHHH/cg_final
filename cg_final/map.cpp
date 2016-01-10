#include "map.h"
#include "Vector.h"
#include <GL/glut.h>

void map::drawSky(){
	//draw sky
	Vector point1(-5, -5, 0);
	Vector point2(mapLength + 5, mapWidth + 5, wallHeight + 5);

	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.5f, 0.6f);
	glVertex3f(point2.x, point2.y, point2.z);
	glVertex3f(point2.x, point1.y, point2.z);
	glVertex3f(point1.x, point1.y, point2.z);
	glVertex3f(point1.x, point2.y, point2.z);

	glVertex3f(point2.x, point2.y, point2.z);
	glVertex3f(point2.x, point2.y, point1.z);
	glVertex3f(point1.x, point2.y, point1.z);
	glVertex3f(point1.x, point2.y, point2.z);

	glVertex3f(point2.x, point2.y, point2.z);
	glVertex3f(point2.x, point2.y, point1.z);
	glVertex3f(point2.x, point1.y, point1.z);
	glVertex3f(point2.x, point1.y, point2.z);

	glVertex3f(point2.x, point1.y, point1.z);
	glVertex3f(point2.x, point1.y, point2.z);
	glVertex3f(point1.x, point1.y, point2.z);
	glVertex3f(point1.x, point1.y, point1.z);

	glVertex3f(point1.x, point2.y, point1.z);
	glVertex3f(point1.x, point2.y, point2.z);
	glVertex3f(point1.x, point1.y, point2.z);
	glVertex3f(point1.x, point1.y, point1.z);

	glEnd();
}

void map::drawGround(){
	//draw ground
	glBegin(GL_QUADS);
	glColor3f(0.7f, 0.7f, 0.3f);
	glVertex3f(-5.0f, -5.0f, -0.5f);
	glVertex3f(-5.0f, 14.0f, -0.5f);
	glVertex3f(14.0f, 14.0f, -0.5f);
	glVertex3f(14.0f, -5.0f, -0.5f);
	glEnd();
}

void map::redraw(){
	drawGround();

	drawSky();
	// draw wall
	for (int i = 0; i < mapLength; i++){
		for (int j = 0; j < mapWidth; j++){
			if (mazeMap[i][j] == 1){
				glPushMatrix();
				glScalef(1, 1, 5);
				glTranslatef(i, j, 0);

				//立方体轮廓
				glColor3f(0.0f, 0.0f, 0.0f);
				glLineWidth(1.5f);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glutSolidCube(1);

				//实心立方体 
				glColor3f(0.8f, 0.8f, 0.8f);

				glPolygonOffset(-1.5, -1.0f);
				glEnable(GL_POLYGON_OFFSET_FILL);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glutSolidCube(1);

				glPopMatrix();
			}
		}
	}
}
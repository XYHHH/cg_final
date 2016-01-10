#include "map.h"
#include "Vector.h"
#include "texture.h"
#include <GL/glut.h>

extern unsigned int wall_texture;

void map::drawSky(){
	//draw sky
	Vector point1(-5, -5, -1);
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
	glVertex3f(-5.0f, -5.0f, 0);
	glVertex3f(-5.0f, 14.0f, 0);
	glVertex3f(14.0f, 14.0f, 0);
	glVertex3f(14.0f, -5.0f, 0);
	glEnd();
}

void map::addTexture(Vector point1, Vector point2, unsigned int texture){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glColor3f(0.6, 0.6, 0.2);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(point2.x, point2.y, point2.z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(point2.x, point1.y, point2.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(point1.x, point1.y, point2.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(point1.x, point2.y, point2.z);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(point2.x, point2.y, point2.z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(point2.x, point2.y, point1.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(point1.x, point2.y, point1.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(point1.x, point2.y, point2.z);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(point2.x, point2.y, point2.z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(point2.x, point2.y, point1.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(point2.x, point1.y, point1.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(point2.x, point1.y, point2.z);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(point2.x, point1.y, point1.z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(point2.x, point1.y, point2.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(point1.x, point1.y, point2.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(point1.x, point1.y, point1.z);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(point1.x, point2.y, point1.z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(point1.x, point2.y, point2.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(point1.x, point1.y, point2.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(point1.x, point1.y, point1.z);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void map::redraw(){
	drawGround();

	drawSky();
	// draw wall
	for (int i = 0; i < mapLength; i++){
		for (int j = 0; j < mapWidth; j++){
			if (mazeMap[i][j] == 1){
				glPushMatrix();
				glTranslatef(i, j, wallHeight/2);
				glScalef(1, 1, wallHeight);

				////立方体轮廓
				//glColor3f(0.0f, 0.0f, 0.0f);
				//glLineWidth(1.5f);
				//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				//glutSolidCube(1);

				//实心立方体 
				glColor3f(0.8f, 0.8f, 0.8f);

				glPolygonOffset(-1.5, -1.0f);
				glEnable(GL_POLYGON_OFFSET_FILL);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				//glutSolidCube(1);
				glPopMatrix();
				addTexture(Vector(i-0.5,j-0.5,0),Vector(i+0.5,j+0.5,wallHeight), wall_texture);
				
			}
		}
	}
}
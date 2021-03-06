#include "map.h"
#include "Vector.h"
#include "texture.h"
#include <GL/glut.h>

extern unsigned int wall_texture;
extern unsigned int sky_back;
extern unsigned int sky_front;
extern unsigned int sky_top;
extern unsigned int sky_right;
extern unsigned int sky_left;
extern unsigned int ground_texture;

void Map::drawSky(){
	//draw sky
	Vector point1(-5, -5, -6);
	Vector point2(mapLength + 5, mapWidth + 5, wallHeight + 10);

	addTexture(point1, point2, sky_top, sky_front, sky_back, sky_left, sky_right);

}

void Map::drawGround(){
	//draw ground
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ground_texture);
	glBegin(GL_QUADS);
	glColor3f(0.7f, 0.7f, 0.3f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 14.0f, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(14.0f, 14.0f, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(14.0f, -5.0f, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Map::addTexture(Vector point1, Vector point2, unsigned int top, unsigned int front,unsigned int back, unsigned int left, unsigned right){
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, top);

	glBegin(GL_QUADS);
	glColor3f(0.9, 0.9, 0.9);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(point2.x, point2.y, point2.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(point2.x, point1.y, point2.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(point1.x, point1.y, point2.z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(point1.x, point2.y, point2.z);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, front);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(point2.x, point2.y, point2.z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(point2.x, point2.y, point1.z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(point1.x, point2.y, point1.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(point1.x, point2.y, point2.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, right);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(point2.x, point2.y, point2.z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(point2.x, point2.y, point1.z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(point2.x, point1.y, point1.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(point2.x, point1.y, point2.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, back);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(point2.x, point1.y, point1.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(point2.x, point1.y, point2.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(point1.x, point1.y, point2.z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(point1.x, point1.y, point1.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, left);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(point1.x, point2.y, point1.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(point1.x, point2.y, point2.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(point1.x, point1.y, point2.z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(point1.x, point1.y, point1.z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Map::redraw(){
	drawGround();

	drawSky();
	// draw wall
	
	for (int i = 0; i < mapLength; i++){
		for (int j = 0; j < mapWidth; j++){
			if (mazeMap[i][j] == 1){
				glPushMatrix();
				glTranslatef(i, j, wallHeight/2);
				glScalef(1, 1, wallHeight);

				//实心立方体 
				glColor3f(0.8f, 0.8f, 0.8f);

				glPolygonOffset(-1.5, -1.0f);
				glEnable(GL_POLYGON_OFFSET_FILL);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				//glutSolidCube(1);
				glPopMatrix();
				addTexture(Vector(i - 0.5, j - 0.5, 0), Vector(i + 0.5, j + 0.5, wallHeight), wall_texture, wall_texture, wall_texture, wall_texture, wall_texture);
				
			}
		}
	}
}
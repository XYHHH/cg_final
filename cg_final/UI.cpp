#include <windows.h>  
#include <GL/glut.h>  
#include <cstdlib>  
#include <sstream>
#include <iostream>
#include "player.h"
#include "UI.h"
#include "texture.h"
#define MAX_CHAR 128

using namespace std;

extern player myPlayer;
extern int windowWidth;
extern int windowHeight;
extern double viewNear;
extern double viewFar;
extern double viewAngle;

extern unsigned int bck_texture;

const double WINDOW_SIZE_RATE = 1.0* GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN);



void drawString(const char* str)
{
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR); 
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}


void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}


void showGameUI(){
	string str;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WINDOW_SIZE_RATE, WINDOW_SIZE_RATE, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	showHP();
	showScore();
	showAim();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, (GLfloat)windowWidth / (GLfloat)windowHeight, viewNear, viewFar);
}


void showHP()
{
	string str;
	stringstream ss;
	int HP = myPlayer.get_HP();
	selectFont(36, ANSI_CHARSET, "Comic Sans MS");
	glColor3f(0.2f, 1.0f, 0.2f);
	glRasterPos2f(-0.8f * WINDOW_SIZE_RATE, -0.8f);
	ss << HP;
	ss >> str;
	string hp_str = "HP:";
	hp_str += str;
	drawString(hp_str.c_str());
}


void showScore()
{
	string str;
	stringstream ss;
	int score = myPlayer.get_score();
	selectFont(36, ANSI_CHARSET, "Comic Sans MS");
	glColor3f(0.2f, 1.0f, 0.2f);
	glRasterPos2f(0.65f * WINDOW_SIZE_RATE, -0.8f);
	ss << score;
	ss >> str;
	string score_str = "SCORE:";
	score_str += str;
	drawString(score_str.c_str());
}


void showAim()
{
	double aim_size = 0.05f;
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f, 0.03f);
	glVertex2f(0.0f, 0.03f + aim_size);

	glVertex2f(0.0f, -0.03f);
	glVertex2f(0.0f, -0.03f - aim_size);

	glVertex2f((0.03f + aim_size), 0.0f);
	glVertex2f(0.03f, 0.0f);

	glVertex2f(-0.03f, 0.0f);
	glVertex2f(-0.03f - aim_size, 0.0f);
	glEnd();
}


void showWelcomePage(){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WINDOW_SIZE_RATE, WINDOW_SIZE_RATE, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	//welcome background
	glColor3f(0.7, 0.7, 0.7);
	glBindTexture(GL_TEXTURE_2D, bck_texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-WINDOW_SIZE_RATE,1.0); 
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(WINDOW_SIZE_RATE, 1.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(WINDOW_SIZE_RATE, -1.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-WINDOW_SIZE_RATE, -1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	selectFont(64, ANSI_CHARSET, "Comic Sans MS");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-0.30f * WINDOW_SIZE_RATE, 0.5f);
	drawString("COUNTER STRIKE");

	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	
	//selectFont(16, ANSI_CHARSET, "Calibri Light");
	glRasterPos2f(-0.23f * WINDOW_SIZE_RATE, -0.2f);
	drawString("GAME START");

	glRasterPos2f(-0.1f * WINDOW_SIZE_RATE, -0.5f);
	drawString("EXIT");
	glPopMatrix();


	
	/*glBindTexture(GL_TEXTURE_2D, btn_texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-0.2 * WINDOW_SIZE_RATE, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.2 * WINDOW_SIZE_RATE, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.2 * WINDOW_SIZE_RATE, -0.3);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-0.2 * WINDOW_SIZE_RATE, -0.3);
	glEnd();
	glDisable(GL_TEXTURE_2D);*/


	//glRectf(-6,6,-4.5,4.5);//background

	//glRectf(-2, 2, -2, -1);//button1

	//glRectf(-2, 2, 0.5, 1.5); // button2

	//glRectf(-2, 2, -2.5, -3.5);//button3


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, (GLfloat)windowWidth / (GLfloat)windowHeight, viewNear, viewFar);

}
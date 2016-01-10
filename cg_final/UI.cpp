#include <windows.h>  
#include <GL/glut.h>  
#include <cstdlib>  
#include <sstream>
#include <iostream>
#include "player.h"
#include "UI.h"
#define MAX_CHAR 128

using namespace std;

extern player myPlayer;
extern int windowWidth;
extern int windowHeight;
extern double viewNear;
extern double viewFar;
extern double viewAngle;

unsigned int bck_texture;
unsigned int btn_texture;

const double WINDOW_SIZE_RATE = 1.0* GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN);

void initUI()
{
	bck_texture = LoadBitMap("../welcome_background.bmp");
	if (bck_texture == -1){
		printf("load welcome background error");
		exit(0);
	}
	//btn_texture = LoadBitMap("../button_background.bmp");
	/*if (btn_texture == -1){
		printf("load button background error");
		exit(0);
	}*/
}


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


int LoadBitMap(const char *file)
{
	unsigned int ID, i;
	int width, height;
	byte *image;
	byte t;
	FILE *fp;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;
	fp = fopen(file, "rb");
	if (fp == NULL){
		perror("LoadBitMap");
		return -1;
	}
	fread(&FileHeader, sizeof(BITMAPFILEHEADER),1,fp);
	if (FileHeader.bfType != 0x4D42)  //确保文件是一个位图文件，效验文件类型
	{
		printf("Error: This file is not a bmp file!");
		fclose(fp);
		return -1;
	}
	fread(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	width = InfoHeader.biWidth;
	height = InfoHeader.biHeight;
	if (InfoHeader.biSizeImage == 0)  {
		InfoHeader.biSizeImage = width*height * 3;
	}

	fseek(fp, FileHeader.bfOffBits, SEEK_SET); 
	image = (byte *)malloc(sizeof(byte)*InfoHeader.biSizeImage);
	if (image == NULL)
	{
		free(image);
		printf("Error: No enough space!");
		return -1;
	}
	fread(image, 1, InfoHeader.biSizeImage, fp);
	for (i = 0; i < InfoHeader.biSizeImage; i += 3){
		t = image[i];
		image[i] = image[i + 2];
		image[i + 2] = t;
	}
	fclose(fp);
	glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);

	return ID;
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

	/*selectFont(36, ANSI_CHARSET, "Comic Sans MS");
	glColor3f(0.2f, 1.0f, 0.2f);
	glRasterPos2f(0.65f * WINDOW_SIZE_RATE, -0.8f);
	drawString(score_str.c_str());
*/


	glBindTexture(GL_TEXTURE_2D, btn_texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-WINDOW_SIZE_RATE, 1.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(WINDOW_SIZE_RATE, 1.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(WINDOW_SIZE_RATE, -1.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-WINDOW_SIZE_RATE, -1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//glRectf(-6,6,-4.5,4.5);//background

	//glRectf(-2, 2, -2, -1);//button1

	//glRectf(-2, 2, 0.5, 1.5); // button2

	//glRectf(-2, 2, -2.5, -3.5);//button3


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, (GLfloat)windowWidth / (GLfloat)windowHeight, viewNear, viewFar);

}
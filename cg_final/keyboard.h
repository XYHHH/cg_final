#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <GL/glut.h>
#include "Vector.h"
#include "player.h"

extern player myPlayer;

void specialKeys(int key, int x, int y);

void upSpecialKeys(int key, int x, int y);

void normalKeys(unsigned char key, int x, int y);

void upNormalKeys(unsigned char key, int x, int y);


#endif
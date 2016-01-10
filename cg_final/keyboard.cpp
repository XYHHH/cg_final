#include "keyboard.h"
#include <cstdlib>
void specialKeys(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_LEFT:
		myPlayer.set_move_state(2, true);
		break;
	case GLUT_KEY_RIGHT:
		myPlayer.set_move_state(3, true);
		break;
	case GLUT_KEY_UP:
		myPlayer.set_move_state(0, true);
		break;
	case GLUT_KEY_DOWN:
		myPlayer.set_move_state(1, true);
		break;
	default:break;
	}
}

void upSpecialKeys(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_LEFT:
		myPlayer.set_move_state(2, false);
		break;
	case GLUT_KEY_RIGHT:
		myPlayer.set_move_state(3, false);
		break;
	case GLUT_KEY_UP:
		myPlayer.set_move_state(0, false);
		break;
	case GLUT_KEY_DOWN:
		myPlayer.set_move_state(1, false);
		break;
	default:break;
	}
}

void normalKeys(unsigned char key, int x, int y) 
{
	switch (key){
	case 27: //ESC
		exit(0);
	case 'w':
		myPlayer.set_move_state(0, true);
		break;
	case 'W':
		myPlayer.set_move_state(0, true);
		break;
	case 'a':
		myPlayer.set_move_state(2, true);
		break;
	case 'A':
		myPlayer.set_move_state(2, true);
		break;
	case 's':
		myPlayer.set_move_state(1, true);
		break;
	case 'S':
		myPlayer.set_move_state(1, true);
		break;
	case 'd':
		myPlayer.set_move_state(3, true);
		break;
	case 'D':
		myPlayer.set_move_state(3, true);
		break;
	}
}

void upNormalKeys(unsigned char key, int x, int y){
	switch (key){
	case 'w':
		myPlayer.set_move_state(0, false);
		break;
	case 'W':
		myPlayer.set_move_state(0, false);
		break;
	case 'a':
		myPlayer.set_move_state(2, false);
		break;
	case 'A':
		myPlayer.set_move_state(2, false);
		break;
	case 's':
		myPlayer.set_move_state(1, false);
		break;
	case 'S':
		myPlayer.set_move_state(1, false);
		break;
	case 'd':
		myPlayer.set_move_state(3, false);
		break;
	case 'D':
		myPlayer.set_move_state(3, false);
		break;
	}
}

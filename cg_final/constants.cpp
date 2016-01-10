#include <GL/glut.h>
#include <Windows.h>

int windowWidth = GetSystemMetrics(SM_CXSCREEN);
int windowHeight = GetSystemMetrics(SM_CYSCREEN);
double rotateSpeed = 3.0;
double viewNear = 1e-5;
double viewFar = 50;
double viewAngle = 80.0;
#ifndef MAP_H
#define MAP_H
#include "Vector.h"

static const int mapLength = 10;
static const int mapWidth = 10;
static const double wallHeight = 3;
static const int mazeMap[mapLength][mapWidth] = {
	// -----------  width ------------>
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },	//  |
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },	//  |
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },	//  |
	{ 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 },	//  |
	{ 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 },	//  length
	{ 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 },	//  |
	{ 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 },	//  |
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },	//	|
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },	//	|
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }	//	V
};


class Map
{
public:
	Map(){}

	void addTexture(Vector point1, Vector point2, unsigned int top, unsigned int front, unsigned int back, unsigned int left, unsigned right);

	void drawGround();

	void drawSky();

	void redraw();
};

#endif
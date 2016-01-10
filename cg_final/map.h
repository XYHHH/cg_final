#ifndef MAP_H
#define MAP_H

static const int mapLength = 10;
static const int mapWidth = 10;
static const double wallHeight = 5;
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



class map
{
public:
	map(){}

	void drawGround();

	void drawSky();

	void redraw();
};

#endif
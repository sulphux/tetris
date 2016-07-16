#pragma once
#include "TBrick.h"
#include <Polycode.h>

using namespace Polycode;

class BrickT : public TBrick
{
public:
	BrickT(Scene *scene, Number posX = 0, Number posY = 0);
};

class BrickO : public TBrick
{
public:
	BrickO(Scene *scene, Number posX = 0, Number posY = 0);
	void rotateLeft(){};
	void rotateRight(){};
};

class BrickI : public TBrick
{
public:
	BrickI(Scene *scene, Number posX = 0, Number posY = 0);
};

class BrickJ : public TBrick
{
public:
	BrickJ(Scene *scene, Number posX = 0, Number posY = 0);
};

class BrickL : public TBrick
{
public:
	BrickL(Scene *scene, Number posX = 0, Number posY = 0);
};

class BrickS : public TBrick
{
public:
	BrickS(Scene *scene, Number posX = 0, Number posY = 0);
};

class BrickZ : public TBrick
{
public:
	BrickZ(Scene *scene, Number posX = 0, Number posY = 0);
};

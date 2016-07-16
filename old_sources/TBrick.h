#pragma once
#include <Polycode.h>
#include "Globals.h"

using namespace Polycode;

class TBrick
{
public:
	TBrick();
	virtual ~TBrick();
	virtual void rotateLeft();
	virtual void rotateRight();
	void shiftBrick(Number xShift, Number yShift);
	void placeOnNext();
	SceneSprite *blocks[4];
};


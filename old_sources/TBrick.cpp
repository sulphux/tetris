#include "TBrick.h"

//Scene* TBrick::scene;

TBrick::TBrick()
{
}


TBrick::~TBrick()
{
}

void TBrick::shiftBrick(Number xShift, Number yShift)
{
	for (int i = 0; i < 4; i++)
	{
		blocks[i]->setPosition(blocks[i]->getPosition().x + xShift, blocks[i]->getPosition().y + yShift);
	}
}

void TBrick::rotateLeft()
{
	Number middleBlockX = blocks[0]->getPosition().x;
	Number middleBlockY = blocks[0]->getPosition().y;

	for (int i = 1; i < 4; i++)
	{
		Number newX = (blocks[i]->getPosition().y - middleBlockY) *(-1);
		Number newY = (blocks[i]->getPosition().x - middleBlockX);
		blocks[i]->setPosition(newX + middleBlockX, newY + middleBlockY);
	}
}

void TBrick::rotateRight()
{
	Number middleBlockX = blocks[0]->getPosition().x;
	Number middleBlockY = blocks[0]->getPosition().y;

	for (int i = 1; i < 4; i++)
	{
		Number newX = (blocks[i]->getPosition().y - middleBlockY);
		Number newY = (blocks[i]->getPosition().x - middleBlockX) *(-1);
		blocks[i]->setPosition(newX + middleBlockX, newY + middleBlockY);
	}
}

void TBrick::placeOnNext()
{
	this->shiftBrick(-blocks[0]->getPosition().x, -blocks[0]->getPosition().y);
	this->shiftBrick(-220, 145);
}
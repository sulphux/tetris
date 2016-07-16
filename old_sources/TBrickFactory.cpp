#include "TBrickFactory.h"

Polycode::Scene* TBrickFactory::scene;

TBrickFactory::TBrickFactory(Scene* scene)
{
	this->scene = scene;
}


TBrickFactory::~TBrickFactory()
{
}

void TBrickFactory::createBrick(BrickType brickType)
{
	switch (brickType)
	{// special formating for better readability and to save screen space
	case bT: currentBrick = new BrickT(scene, BRICK_START_X, BRICK_START_Y); break;
	case bO: currentBrick = new BrickO(scene, BRICK_START_X, BRICK_START_Y); break;
	case bL: currentBrick = new BrickL(scene, BRICK_START_X, BRICK_START_Y); break;
	case bJ: currentBrick = new BrickJ(scene, BRICK_START_X, BRICK_START_Y); break;
	case bI: currentBrick = new BrickI(scene, BRICK_START_X, BRICK_START_Y); break;
	case bZ: currentBrick = new BrickZ(scene, BRICK_START_X, BRICK_START_Y); break;
	case bS: currentBrick = new BrickS(scene, BRICK_START_X, BRICK_START_Y); break;
	}
		
}

void TBrickFactory::storeCurrentOnBoard()
{
	for (int i = 0; i < 4; i++)
	{
		Number tmpX = currentBrick->blocks[i]->getPosition().x;
		Number tmpY = currentBrick->blocks[i]->getPosition().y;
		tmpX = (tmpX - TOP_LEFT_CORNER_COORD_X + 0.1) / TILE_SIZE;
		tmpY = (-1)*(tmpY - TOP_LEFT_CORNER_COORD_Y - 0.1) / TILE_SIZE;
		CBoard::setBlockPointer(currentBrick->blocks[i], tmpX, tmpY);
	}
	delete currentBrick;
}
#include "CBoard.h"

Scene* CBoard::scene;
short CBoard::fields[10][20];
SceneSprite *CBoard::blockPointers[10][20];
int CBoard::currBrickX;
int CBoard::currBrickY;
short CBoard::currSide;
CBoard::BrickType CBoard::currentBrickType;

short CBoard::brickCoords[7][6] = 
{//   x1  y1  x2  y2  x3  y3   // brick type:
	{ -1,  0,  0, -1,  1,  0 },// T
	{  0, -1,  1, -1,  1,  0 },// O
	{ -1,  0,  1,  0,  2,  0 },// I
	{ -1,  0, -1, -1,  1,  0 },// J
	{ -1,  0,  1,  0,  1, -1 },// L
	{ -1,  0,  0, -1,  1, -1 },// S
	{ -1, -1,  0, -1,  1,  0 } // Z
};

void CBoard::setCurrentBrickType(CBoard::BrickType brickType)
{
	currentBrickType = brickType;
}

void CBoard::setBlockPointer(SceneSprite *block, int x, int y) // to storage sprite blocks
{
	blockPointers[x][y] = block;
}

SceneSprite *CBoard::getBlockPointer(int x, int y) // to get storage sprite blocks
{
	return blockPointers[x][y];
}

void CBoard::resetBoard()
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			fields[x][y] = 0;
			blockPointers[x][y] = NULL;
		}
	}
}

void CBoard::writeBrickToBoard()
{
	int brickNumber = static_cast<int>(currentBrickType);
	for (int i = 0; i < 3; i++)
	{
		int tmpX = currBrickX + brickCoords[brickNumber][2 * i];
		int tmpY = currBrickY + brickCoords[brickNumber][2 * i + 1];
		fields[tmpX][tmpY] = -1;
	}
	fields[currBrickX][currBrickY] = -1;
	resetSideState();
}

bool CBoard::tryPutNewBrick()
{
	int brickNumber = static_cast<int>(currentBrickType);
	for (int i = 0; i < 3; i++)
	{
		int tmpX = 4 + brickCoords[brickNumber][2 * i];
		int tmpY = 1 + brickCoords[brickNumber][2 * i + 1];
	}
	currBrickX = 4;
	currBrickY = 1;
	return true;
}

bool CBoard::tryShiftDownBrick()
{
	int brickNumber = static_cast<int>(currentBrickType);
	for (int i = 0; i < 3; i++)
	{
		int tmpX = currBrickX + brickCoords[brickNumber][2 * i];
		int tmpY = currBrickY + brickCoords[brickNumber][2 * i + 1];
		if (tmpY>18 || fields[tmpX][tmpY + 1] != 0)
			return false;
	}
	if (currBrickY<20 && fields[currBrickX][currBrickY + 1] != 0) return false;
	currBrickY++;
	return true;
}

bool CBoard::tryShiftLeftBrick()
{
	int brickNumber = static_cast<int>(currentBrickType);
	for (int i = 0; i < 3; i++)
	{
		int tmpX = currBrickX + brickCoords[brickNumber][2 * i];
		int tmpY = currBrickY + brickCoords[brickNumber][2 * i + 1];
		short tmp = fields[tmpX - 1][tmpY];
		if (tmpX<1 || fields[tmpX - 1][tmpY] != 0)
			return false;
	}
	if (currBrickX>0 && fields[currBrickX - 1][currBrickY] != 0) return false;
	currBrickX--;
	return true;
}

bool CBoard::tryShiftRightBrick()
{
	int brickNumber = static_cast<int>(currentBrickType);
	for (int i = 0; i < 3; i++)
	{
		int tmpX = currBrickX + brickCoords[brickNumber][2 * i];
		int tmpY = currBrickY + brickCoords[brickNumber][2 * i + 1];
		if (tmpX>8 || fields[tmpX + 1][tmpY] != 0)
			return false;
	}
	if (currBrickX>0 && fields[currBrickX + 1][currBrickY] != 0) return false;
	currBrickX++;
	return true;
}

void CBoard::rotateBrickSchemeRight(BrickType brickType)
{
	int brickNumber = static_cast<int>(currentBrickType);

	for (int i = 0; i < 3; i++)
	{
		short newX = brickCoords[brickNumber][2 * i + 1] * (-1);
		short newY = brickCoords[brickNumber][2 * i];
		brickCoords[brickNumber][2 * i] = newX;
		brickCoords[brickNumber][2 * i + 1] = newY;
	}
	currSide++;
}

void CBoard::rotateBrickSchemeLeft(BrickType brickType)
{
	int brickNumber = static_cast<int>(currentBrickType);

	for (int i = 0; i < 3; i++)
	{
		short newX = brickCoords[brickNumber][2 * i + 1];
		short newY = brickCoords[brickNumber][2 * i] * (-1);
		brickCoords[brickNumber][2 * i] = newX;
		brickCoords[brickNumber][2 * i + 1] = newY;
	}
	currSide--;
}


bool CBoard::tryRotateRightBrick()
{
	int brickNumber = static_cast<int>(currentBrickType);
	if (brickNumber == 1) return false;
	rotateBrickSchemeRight();
	for (int i = 0; i < 3; i++)
	{
		int tmpX = currBrickX + brickCoords[brickNumber][2 * i];
		int tmpY = currBrickY + brickCoords[brickNumber][2 * i + 1];
		if (tmpX<0 || tmpX>9 || tmpY<0 || tmpY>19 || fields[tmpX][tmpY] != 0)
		{
			rotateBrickSchemeLeft();
			return false;
		}
	}
	return true;
}


bool CBoard::tryRotateLeftBrick()
{
	int brickNumber = static_cast<int>(currentBrickType);
	if (brickNumber == 1) return false;
	rotateBrickSchemeLeft();
	for (int i = 0; i < 3; i++)
	{
		int tmpX = currBrickX + brickCoords[brickNumber][2 * i];
		int tmpY = currBrickY + brickCoords[brickNumber][2 * i + 1];
		if (tmpX<0 || tmpX>9 || tmpY<0 || tmpY>19 || fields[tmpX][tmpY] != 0)
		{
			rotateBrickSchemeRight();
			return false;
		}
	}
	return true;
}

void CBoard::resetSideState()
{
	if (currSide != 0)
	{
		currSide %= 4;

		while (currSide > 0)
			rotateBrickSchemeLeft();

		while (currSide < 0)
			rotateBrickSchemeRight();
	}
}

void CBoard::shiftBoardDown(int indexY)
{
	for (int i = 0; i<10; i++)
	{
		if (blockPointers[i][indexY] != NULL)
			scene->removeEntity(blockPointers[i][indexY]);
	}
	for (int y = indexY; y > 0; y--)
	{
		for (int x = 0; x < 10; x++)
		{
			fields[x][y] = fields[x][y-1];
			if (blockPointers[x][y] != NULL)
			{
				blockPointers[x][y]->setPositionY(blockPointers[x][y]->getPosition().y - TILE_SIZE);
				blockPointers[x][y] = blockPointers[x][y - 1];
			}
		}
	}
}

void CBoard::checkLines()
{
	int y = 19;
	while(y >= 0)
	{
		int x = 0;
		while (x<10 && fields[x][y] == -1)
		{
			x++;
		}
		if (x>9)
		{
			shiftBoardDown(y);
		}
		else
		{
			y--;
		}
	}
}

void CBoard::setScene(Scene* scene)
{ 
	CBoard::scene = scene; 
}

#ifdef _DEBUG_
void CBoard::debugOutput()
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (fields[x][y] != 0)
				OutputDebugString(L"X");
			else
				OutputDebugString(L"O");
		}
		OutputDebugString(L"\n");
	}
	OutputDebugString(L"\n");
}
#endif
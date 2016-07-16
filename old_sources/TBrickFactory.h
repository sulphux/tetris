#pragma once
#include "TBrick.h"
#include "Bricks.h"
#include "Polycode.h"
#include "CBoard.h"

using namespace Polycode;

class TBrickFactory
{
public:
	TBrick* currentBrick;
	TBrickFactory(Scene* scene);
	~TBrickFactory();
	enum BrickType { bT, bO, bI, bJ, bL, bS, bZ};
	void createBrick(BrickType brickType);
	void storeCurrentOnBoard(); // storing current brick sprites on CBoard table of pointers
private:
	static Scene* scene;
};


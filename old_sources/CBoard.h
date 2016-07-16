#pragma once
#include "Polycode.h"
#include "Globals.h"
#include "TBrick.h"

#ifdef _DEBUG_
#include "windows.h"
#endif

using namespace Polycode;

class CBoard
{
public:
	static CBoard& getInstance()
	{
		static CBoard instance;
		return instance;
	}

	static enum BrickType { bT, bO, bI, bJ, bL, bS, bZ };

	static void setCurrentBrickType(BrickType brickType);
	static void setBlockPointer(SceneSprite *block, int x, int y);
	static SceneSprite *getBlockPointer(int x, int y);
	void resetBoard(); // write 0 to every cell of board
	void checkLines(); // checks if there is completed lines
	void writeBrickToBoard(); // saving a place on map for a brick
	// the 'trying' methods to place or rotate brick everywhere.
	bool tryPutNewBrick();
	bool tryShiftDownBrick();
	bool tryShiftLeftBrick();
	bool tryShiftRightBrick();
	bool tryRotateLeftBrick();
	bool tryRotateRightBrick();

	static void setScene(Scene* scene);
#ifdef _DEBUG_
	static void debugOutput();
#endif

private:
	static Scene* scene;
	static short fields[10][20];       // main board binary map
	static SceneSprite *blockPointers[10][20]; // table of brick pointers
	static int currBrickX, currBrickY; // current brick coordinates which player are controlling
	static BrickType currentBrickType; // current brick type
	static short currSide;             // current brick side
	static short brickCoords[7][6];    // binary map of every brick, first param describe type of brick
	static void rotateBrickSchemeLeft(BrickType brickType = currentBrickType);  // rotating to the left map of occupying tiles of the brick
	static void rotateBrickSchemeRight(BrickType brickType = currentBrickType); // rotating to the left map of occupying tiles of the brick
	static void shiftBoardDown(int indexY); //  shift where player made a line
	static void resetSideState(); // resets a state of current side of brick
	

	CBoard(){ currSide = 0; };
	CBoard(const CBoard &);
	CBoard& operator=(const CBoard&);
};


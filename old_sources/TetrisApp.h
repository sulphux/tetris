#include <Polycode.h>
#include "PolycodeView.h"
#include "TBrickFactory.h"
#include "CRandomizer.h"

#include "Bricks.h"
#include "Globals.h"


using namespace Polycode;

class TetrisApp : public EventHandler {
public:
    TetrisApp(PolycodeView *view);
    ~TetrisApp();
    
	void handleEvent(Event *e);
    bool Update();

	Number xMove;
	Number yMove;

	int next;

private:
	Sound* sounds[4];
	TBrickFactory *brickFactory;
	TBrickFactory *brickNextFactory;
	CBoard *mainBoard;
	CRandomizer *randomizer;
	TBrick *currentBrick;
	TBrick *nextBrick;
	SceneSprite *nextBrickBlocks[4];
	void copyNextSprites();
	void delNextSprites();

	Timer *droppingBrickTimer;
    Core *core;
	Scene *scene;
	void InitBackground();
	void InitSounds();
};
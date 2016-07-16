#include "TetrisApp.h"

TetrisApp::TetrisApp(PolycodeView *view) {
	// init core
	core = new Win32Core(view, 760,600,false, false, 0, 0,60);
	scene = new Scene(Scene::SCENE_2D);

	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST); //disabling image blending before loading resources
	// loading assets
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	// setting camera
	scene->getActiveCamera()->setOrthoSize(760, 600);

	// init 1s dropping timer
	droppingBrickTimer = new Timer(true, 1000);
	droppingBrickTimer->addEventListener(this, Timer::EVENT_TRIGGER);

	// init "keypressed" & "keyreleased"
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);

	// init function of whole background
	InitBackground();

	// init "randomizer" and pick first number of piece
	randomizer = &(CRandomizer::getInstance());
	next = randomizer->getNewRand();

	// run brick factory and create first product :
	brickFactory = new TBrickFactory(scene);
	brickFactory->createBrick(static_cast<TBrickFactory::BrickType>(next));
	currentBrick = brickFactory->currentBrick;
	
	// init main board
	mainBoard = &(CBoard::getInstance());
	mainBoard->resetBoard();
	mainBoard->setScene(scene);

	// first use of "brick-collision-mini-map"
	CBoard::setCurrentBrickType(static_cast<CBoard::BrickType>(next));
	bool tmp = mainBoard->tryPutNewBrick();

	// make brick for "next" window and init "next-factory"
	next = randomizer->getNewRand();
	brickNextFactory = new TBrickFactory(scene);
	brickNextFactory->createBrick(static_cast<TBrickFactory::BrickType>(next));
	nextBrick = brickNextFactory->currentBrick;
	nextBrick->placeOnNext();
	copyNextSprites();

	// init sounds
	InitSounds();
	sounds[0]->setVolume(0.25);
	sounds[0]->Play(true);
}
TetrisApp::~TetrisApp() {
    
}

bool TetrisApp::Update() {
	// may will be needed in the future for smooth animations
	Number elapsed = core->getElapsed();
	return core->updateAndRender();
}

// main event handler for keystates and timer-events
void TetrisApp::handleEvent(Event *e) { 
	if (e->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)e;
		switch (e->getEventCode()) {
		case InputEvent::EVENT_KEYDOWN:
			switch (inputEvent->keyCode()) {
			case KEY_LEFT:
				if (mainBoard->tryShiftLeftBrick()){
					currentBrick->shiftBrick(-TILE_SIZE, 0);
					sounds[SOUND_CLICK]->Play(false);
				}
				break;
			case KEY_RIGHT:
				if (mainBoard->tryShiftRightBrick()){
					currentBrick->shiftBrick(TILE_SIZE, 0);
					sounds[SOUND_CLICK]->Play(false);
				}
				break;
			case KEY_UP:
				if (mainBoard->tryRotateRightBrick()){
					currentBrick->rotateRight();
					sounds[SOUND_ROTATE]->Play(false);
				}
				break;
			case KEY_DOWN:
				if (mainBoard->tryRotateLeftBrick()){
					currentBrick->rotateLeft();
					sounds[SOUND_ROTATE]->Play(false);
				}
				break;
			case KEY_SPACE:
				if (mainBoard->tryShiftDownBrick())
					currentBrick->shiftBrick(0, -TILE_SIZE);
			}
			break;
		case InputEvent::EVENT_KEYUP:
			switch (inputEvent->key) {
			case KEY_LEFT:
			case KEY_RIGHT:
			case KEY_DOWN:
			case KEY_UP:
			case KEY_LSHIFT:
				#ifdef _DEBUG_
				CBoard::debugOutput(); // only for debuging
				#endif
				break;
			}
			break;
		}

	}
	if (e->getDispatcher() == droppingBrickTimer && e->getEventCode() == Timer::EVENT_TRIGGER) {
		if (mainBoard->tryShiftDownBrick())
			currentBrick->shiftBrick(0, -TILE_SIZE);
		else
		{
			// make imprint on board
			mainBoard->writeBrickToBoard();       
			// store pointers for sprites
			brickFactory->storeCurrentOnBoard();  
			//check if tetris
			mainBoard->checkLines();
			mainBoard->setCurrentBrickType(static_cast<CBoard::BrickType>(next));  
			bool tmp = mainBoard->tryPutNewBrick();                                /// TODO: "if statement" to service "game over"
			// produce another brick
			brickFactory->createBrick(static_cast<TBrickFactory::BrickType>(next));
			currentBrick = brickFactory->currentBrick;
			// make new "next"
			delNextSprites();
			next = randomizer->getNewRand();
			delete nextBrick;
			brickNextFactory->createBrick(static_cast<TBrickFactory::BrickType>(next));
			nextBrick = brickNextFactory->currentBrick;
			nextBrick->placeOnNext();
			copyNextSprites();
			sounds[SOUND_HAMMER]->Play();
		}
	}
}

void TetrisApp::InitBackground()
{
	SceneImage *backgroundImage = new SceneImage("default/bg_main.png");
	scene->addChild(backgroundImage);

	SceneImage *uiPanelMain = new SceneImage("default/ui_panel_main.png");
	uiPanelMain->setPosition(0, 10);
	scene->addChild(uiPanelMain);

	SceneImage *uiPanelShort = new SceneImage("default/ui_panel_short.png");
	uiPanelShort->setPosition(-240, 160);
	scene->addChild(uiPanelShort);

	SceneImage *uiIconTile = new SceneImage("default/ui_icon_tile_next.png");
	uiIconTile->setPosition(-300, 160);
	scene->addChild(uiIconTile);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			SceneImage *uiGameTileStencil = new SceneImage(TILE_STENCIL_STR);
			uiGameTileStencil->setPosition(x * TILE_SIZE + X_SHIFT, y * TILE_SIZE + Y_SHIFT);
			scene->addChild(uiGameTileStencil);
		}
	}
}

void TetrisApp::InitSounds()
{
	sounds[0] = new Sound("default/music1.ogg");
	sounds[1] = new Sound("default/click.wav");
	sounds[1]->setVolume(1);
	sounds[2] = new Sound("default/rotate.wav");
	sounds[2]->setVolume(0.25);
	sounds[3] = new Sound("default/ham.wav");
	sounds[3]->setVolume(1);
}

void TetrisApp::copyNextSprites()
{
	for (int i = 0; i < 4; i++)
		nextBrickBlocks[i] = nextBrick->blocks[i];
}

void TetrisApp::delNextSprites()
{
	for (int i = 0; i < 4; i++)
		scene->removeEntity(nextBrickBlocks[i]);
}
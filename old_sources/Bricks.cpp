#include "Bricks.h"
#include "Globals.h"

BrickT::BrickT(Scene *scene, Number posX, Number posY)
{
	for (int i = 0; i < 4; i++)
		blocks[i] = new SceneSprite(TILE_DGREEN_STR, 24, 24);

	blocks[0]->setPosition(posX, posY);
	blocks[1]->setPosition(posX + TILE_SIZE, posY);
	blocks[2]->setPosition(posX - TILE_SIZE, posY);
	blocks[3]->setPosition(posX, posY + TILE_SIZE);

	for (int i = 0; i < 4; i++)
		scene->addChild(blocks[i]);
}

BrickO::BrickO(Scene *scene, Number posX, Number posY)
{
	for (int i = 0; i < 4; i++)
		blocks[i] = new SceneSprite(TILE_RED_STR, 24, 24);

	blocks[0]->setPosition(posX, posY);
	blocks[1]->setPosition(posX + TILE_SIZE, posY);
	blocks[2]->setPosition(posX, posY + TILE_SIZE);
	blocks[3]->setPosition(posX + TILE_SIZE, posY + TILE_SIZE);

	for (int i = 0; i < 4; i++)
		scene->addChild(blocks[i]);
}

BrickI::BrickI(Scene *scene, Number posX, Number posY)
{
	for (int i = 0; i < 4; i++)
		blocks[i] = new SceneSprite(TILE_LGREEN_STR, 24, 24);

	blocks[0]->setPosition(posX, posY);
	blocks[1]->setPosition(posX - TILE_SIZE, posY);
	blocks[2]->setPosition(posX + TILE_SIZE, posY);
	blocks[3]->setPosition(posX + 2 * TILE_SIZE, posY);

	for (int i = 0; i < 4; i++)
		scene->addChild(blocks[i]);
}

BrickJ::BrickJ(Scene *scene, Number posX, Number posY)
{
	for (int i = 0; i < 4; i++)
		blocks[i] = new SceneSprite(TILE_ORANGE_STR, 24, 24);

	blocks[0]->setPosition(posX, posY);
	blocks[1]->setPosition(posX - TILE_SIZE, posY + TILE_SIZE);
	blocks[2]->setPosition(posX - TILE_SIZE, posY);
	blocks[3]->setPosition(posX + TILE_SIZE, posY);

	for (int i = 0; i < 4; i++)
		scene->addChild(blocks[i]);
}

BrickL::BrickL(Scene *scene, Number posX, Number posY)
{
	for (int i = 0; i < 4; i++)
		blocks[i] = new SceneSprite(TILE_MAGENTA_STR, 24, 24);

	blocks[0]->setPosition(posX, posY);
	blocks[1]->setPosition(posX + TILE_SIZE, posY);
	blocks[2]->setPosition(posX - TILE_SIZE, posY);
	blocks[3]->setPosition(posX + TILE_SIZE, posY + TILE_SIZE);

	for (int i = 0; i < 4; i++)
		scene->addChild(blocks[i]);
}

BrickS::BrickS(Scene *scene, Number posX, Number posY)
{
	for (int i = 0; i < 4; i++)
		blocks[i] = new SceneSprite(TILE_YELLOW_STR, 24, 24);

	blocks[0]->setPosition(posX, posY);
	blocks[1]->setPosition(posX, posY + TILE_SIZE);
	blocks[2]->setPosition(posX + TILE_SIZE, posY + TILE_SIZE);
	blocks[3]->setPosition(posX - TILE_SIZE, posY);

	for (int i = 0; i < 4; i++)
		scene->addChild(blocks[i]);
}

BrickZ::BrickZ(Scene *scene, Number posX, Number posY)
{
	for (int i = 0; i < 4; i++)
		blocks[i] = new SceneSprite(TILE_VIOLET_STR, 24, 24);

	blocks[0]->setPosition(posX, posY);
	blocks[1]->setPosition(posX + TILE_SIZE, posY);
	blocks[2]->setPosition(posX, posY + TILE_SIZE);
	blocks[3]->setPosition(posX - TILE_SIZE, posY + TILE_SIZE);

	for (int i = 0; i < 4; i++)
		scene->addChild(blocks[i]);
}
#include "Brick.h"


Brick::Brick()
{
}


Brick::~Brick()
{
}

void Brick::setPositionX(Number X)
{
	positionX = X;
}

void Brick::setPositionY(Number Y)
{
	positionY = Y;
}

void Brick::setPosition(Number X, Number Y)
{
	setPositionX(X);
	setPositionY(Y);
}
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "old_sources/CRandomizer.h"

#define TILE_SIZE 26   // with space 2 px
#define TILE_SIZE_W 24 // without space
#define X_SHIFT 251  // coord x of beginning map
#define Y_SHIFT 31 // as above but y

#define CAN_DOWN currBrickY>=19
#define CAN_LEFT currBrickX<=0
#define CAN_RIGHT currBrickX>=9

///-------------------------------

// init "randomizer" and pick first number of piece
CRandomizer* randomizer = &(CRandomizer::getInstance());

bool lShiftingFlag = false;
bool rShiftingFlag = false;
bool dShiftingFlag = false;
Uint32 shiftingSpeed = 100;

short currBrickX;
short currBrickY;
short currSide = 0;

short mainBoard[10][20];
short brickCoords[8][6] =
{//   x1  y1  x2  y2  x3  y3   // brick type:
    {  0,  0,  0,  0,  0,  0 },//0// nothing
	{ -1,  0,  0, -1,  1,  0 },//1// T
	{  0, -1,  1, -1,  1,  0 },//2// O
	{ -1,  0,  1,  0,  2,  0 },//3// I
	{ -1,  0, -1, -1,  1,  0 },//4// J
	{ -1,  0,  1,  0,  1, -1 },//5// L
	{ -1,  0,  0, -1,  1, -1 },//6// S
	{ -1, -1,  0, -1,  1,  0 } //7// Z
};

short currentNextBrickType = randomizer->getNewRand();
short currentBrickType = randomizer->getNewRand();

void pickUpBrick();
void putDownBrick();
void putDownBrick(short, short);
void rotateBrickSchemeLeft();
void rotateBrickSchemeRight();


void resetBoard()
{
	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 10; x++)
            mainBoard[x][y] = 0;
}

void resetSideState()
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

void tryPutNewBrick()
{
    currentBrickType = currentNextBrickType;
    currentNextBrickType = randomizer->getNewRand();

    currBrickX = 4;
	currBrickY = 1;
	int brickNumber = static_cast<int>(currentBrickType);

	for (int i = 0; i < 3; i++)
	{
		int tmpX = 4 + brickCoords[brickNumber][2 * i];
		int tmpY = 1 + brickCoords[brickNumber][2 * i + 1];
        if (mainBoard[tmpX][tmpY] != 0)
			return;
	}

	if (mainBoard[4][1] != 0)
			return;
    putDownBrick();
}

bool tryShift(short xInterval, short yInterval )
{
    int tmpX, tmpY;

    int brickNumber = static_cast<int>(currentBrickType);

    pickUpBrick();

	for (int i = 0; i < 3; i++)
	{
		tmpX = currBrickX + brickCoords[brickNumber][2 * i];
		tmpY = currBrickY + brickCoords[brickNumber][2 * i + 1];

		if (!((tmpX + xInterval)<=9) || !((tmpX + xInterval)>=0) || !((tmpY + yInterval)<=19) || mainBoard[tmpX + xInterval][tmpY + yInterval] != 0)
		{
		    putDownBrick();
		    return false;
		}
	}
    if( !((tmpX + xInterval)<=9) || !((tmpX + xInterval)>=0) || !((tmpY + yInterval)<=19) || mainBoard[currBrickX][currBrickY + 1] != 0)
    {
        putDownBrick();
        return false;
    }

    putDownBrick(xInterval, yInterval);
    currBrickX += xInterval;
	currBrickY += yInterval;
	return true;
}

void tryShiftInfinitlyDown()
{
    while(tryShift(0,1));
}

bool tryRotateRightBrick()
{
	if (currentBrickType == 2) return false;
	pickUpBrick();
	rotateBrickSchemeRight();
	for (int i = 0; i < 3; i++)
	{
		int tmpX = currBrickX + brickCoords[currentBrickType][2 * i];
		int tmpY = currBrickY + brickCoords[currentBrickType][2 * i + 1];
		if (tmpX<0 || tmpX>9 || tmpY<0 || tmpY>19 || mainBoard[tmpX][tmpY] != 0)
		{
			rotateBrickSchemeLeft();
			putDownBrick();
			return false;
		}
	}
	putDownBrick();
	return true;
}

bool tryRotateLeftBrick()
{
	if (currentBrickType == 2) return false;
	pickUpBrick();
	rotateBrickSchemeLeft();
	for (int i = 0; i < 3; i++)
	{
		int tmpX = currBrickX + brickCoords[currentBrickType][2 * i];
		int tmpY = currBrickY + brickCoords[currentBrickType][2 * i + 1];
		if (tmpX<0 || tmpX>9 || tmpY<0 || tmpY>19 || mainBoard[tmpX][tmpY] != 0)
		{
			rotateBrickSchemeRight();
			putDownBrick();
			return false;
		}
	}
	putDownBrick();
	return true;
}

void pickUpBrick()
{
    mainBoard[currBrickX][currBrickY] = 0;
	for (int i = 0; i < 3; i++)
        mainBoard[currBrickX + brickCoords[currentBrickType][2 * i]][currBrickY + brickCoords[currentBrickType][2 * i + 1]] = 0;
}

void putDownBrick()
{
    putDownBrick(0,0);
}

void putDownBrick(short xInterval, short yInterval)
{
    mainBoard[currBrickX + xInterval][currBrickY + yInterval] = currentBrickType;
    for (int i = 0; i < 3; i++)
        mainBoard[currBrickX + brickCoords[currentBrickType][2 * i] + xInterval][currBrickY + brickCoords[currentBrickType][2 * i + 1] + yInterval] = currentBrickType;

}

void rotateBrickSchemeRight()
{
	for (short i = 0; i < 3; i++)
	{
		short newX = brickCoords[currentBrickType][2 * i + 1] * (-1);
		short newY = brickCoords[currentBrickType][2 * i];
		brickCoords[currentBrickType][2 * i] = newX;
		brickCoords[currentBrickType][2 * i + 1] = newY;
	}
	currSide++;
}

void rotateBrickSchemeLeft()
{
	for (int i = 0; i < 3; i++)
	{
		short newX = brickCoords[currentBrickType][2 * i + 1];
		short newY = brickCoords[currentBrickType][2 * i] * (-1);
		brickCoords[currentBrickType][2 * i] = newX;
		brickCoords[currentBrickType][2 * i + 1] = newY;
	}
	currSide--;
}

void shiftBoardDown(short indexY)
{
	for (int y = indexY; y > 0; y--)
	{
		for (int x = 0; x < 10; x++)
		{
			mainBoard[x][y] = mainBoard[x][y-1];
		}
	}
}

void checkLines()
{
	int y = 19;
	while(y >= 0)
	{
		int x = 0;
		while (x<10 && mainBoard[x][y] != 0)
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

Uint32 callback( Uint32 interval, void* param )
{
    if (!tryShift(0, 1))
    {
        resetSideState();
        checkLines();
        tryPutNewBrick();
        shiftingSpeed = 100;
    }

    return interval;
}

Uint32 callback2( Uint32 interval, void* param )
{
    if (rShiftingFlag)
        tryShift(1,0);
    if (lShiftingFlag)
        tryShift(-1,0);
    if (dShiftingFlag)
        tryShift(0,1);
    if ((rShiftingFlag||lShiftingFlag||dShiftingFlag)&&(shiftingSpeed>15))
        shiftingSpeed-= 15;


    return shiftingSpeed;
}


//Screen dimension constants
const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 600;

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path );

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene sprites
SDL_Rect gSpriteClips[ 12 ];
LTexture gSpriteSheetTexture;

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}


void LTexture::render( int x, int y, SDL_Rect* clip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool init()
{
    resetBoard();

    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER  ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "assets/spritesheet/tetris_main_001.png" ) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else
    {
        //bg_main
        gSpriteClips[ 0 ].x =   2;
        gSpriteClips[ 0 ].y =   2;
        gSpriteClips[ 0 ].w = 760;
        gSpriteClips[ 0 ].h = 600;

        //ui_icon_tile_next
        gSpriteClips[ 1 ].x = 2;
        gSpriteClips[ 1 ].y = 1222;
        gSpriteClips[ 1 ].w = 39;
        gSpriteClips[ 1 ].h = 45;

        //ui_panel_main
        gSpriteClips[ 2 ].x =   2;
        gSpriteClips[ 2 ].y = 604;
        gSpriteClips[ 2 ].w = 286;
        gSpriteClips[ 2 ].h = 540;

        //ui_panel_short
        gSpriteClips[ 3 ].x = 2;
        gSpriteClips[ 3 ].y = 1146;
        gSpriteClips[ 3 ].w = 184;
        gSpriteClips[ 3 ].h = 74;

        //stencil
        gSpriteClips[ 4 ].x = 2;
        gSpriteClips[ 4 ].y = 1321;
        gSpriteClips[ 4 ].w = 24;
        gSpriteClips[ 4 ].h = 24;

        //game_object_tile_green_dark
        gSpriteClips[ 5 ].x = 2;
        gSpriteClips[ 5 ].y = 1451;
        gSpriteClips[ 5 ].w = 24;
        gSpriteClips[ 5 ].h = 24;

        //game_object_tile_green_light
        gSpriteClips[ 6 ].x = 2;
        gSpriteClips[ 6 ].y = 1425;
        gSpriteClips[ 6 ].w = 24;
        gSpriteClips[ 6 ].h = 24;

        //game_object_tile_magenta
        gSpriteClips[ 7 ].x = 2;
        gSpriteClips[ 7 ].y = 1399;
        gSpriteClips[ 7 ].w = 24;
        gSpriteClips[ 7 ].h = 24;

        //game_object_tile_orange
        gSpriteClips[ 8 ].x = 2;
        gSpriteClips[ 8 ].y = 1373;
        gSpriteClips[ 8 ].w = 24;
        gSpriteClips[ 8 ].h = 24;

        //game_object_tile_red
        gSpriteClips[ 9 ].x = 2;
        gSpriteClips[ 9 ].y = 1347;
        gSpriteClips[ 9 ].w = 24;
        gSpriteClips[ 9 ].h = 24;

        //game_object_tile_violet
        gSpriteClips[ 10 ].x = 2;
        gSpriteClips[ 10 ].y = 1295;
        gSpriteClips[ 10 ].w = 24;
        gSpriteClips[ 10 ].h = 24;

        //game_object_tile_yellow
        gSpriteClips[ 11 ].x = 2;
        gSpriteClips[ 11 ].y = 1269;
        gSpriteClips[ 11 ].w = 24;
        gSpriteClips[ 11 ].h = 24;
    }

    return success;
}

void close()
{
    //Free loaded images
    gSpriteSheetTexture.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;


            void * nothing;
            SDL_TimerID timerShifting = SDL_AddTimer( 1000, callback, nothing);
            SDL_TimerID timerShiftingVertical = SDL_AddTimer( 60, callback2, nothing);

            tryPutNewBrick();

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    //User requests key
                    else if( e.type == SDL_KEYDOWN)
                    {
                        switch( e.key.keysym.sym )
                        {
                        case SDLK_LEFT:
                            lShiftingFlag = true;
                            break;
                        case SDLK_RIGHT:
                            rShiftingFlag = true;
                            break;
                        case SDLK_DOWN:
                            dShiftingFlag = true;
                            break;
                        case SDLK_LSHIFT:
                            tryRotateRightBrick();
                            printf("%i", currSide);
                            break;
                        case SDLK_LALT:
                            tryRotateLeftBrick();
                            printf("%i", currSide);
                            break;
                        case SDLK_SPACE:
                            tryShiftInfinitlyDown();
                            break;
                        }
                    }
                    else if( e.type == SDL_KEYUP)
                    {
                        switch( e.key.keysym.sym )
                        {
                        case SDLK_LEFT:
                            lShiftingFlag = false;
                            shiftingSpeed = 100;
                            break;
                        case SDLK_RIGHT:
                            rShiftingFlag = false;
                            shiftingSpeed = 100;
                            break;
                        case SDLK_DOWN:
                            dShiftingFlag = false;
                            shiftingSpeed = 100;
                        }
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render background
                gSpriteSheetTexture.render( 0, 0, &gSpriteClips[ 0 ] );

                //Render frame
                gSpriteSheetTexture.render( SCREEN_WIDTH/2 - gSpriteClips[ 2 ].w/2, SCREEN_HEIGHT/2 - gSpriteClips[ 2 ].h/2 - 10, &gSpriteClips[ 2 ] );

                //Render small frame
                gSpriteSheetTexture.render( 140 - gSpriteClips[ 3 ].w/2, 140-gSpriteClips[ 3 ].h/2, &gSpriteClips[ 3 ] );

                //Render button
                gSpriteSheetTexture.render( 80 - gSpriteClips[ 1 ].w/2, 140 - gSpriteClips[ 1 ].h/2, &gSpriteClips[ 1 ] );

                //Render 20x10 stencils
                for( int y = 0; y < 20; y++ )
                {
                    for( int x = 0; x < 10; x++ )
                    {
                        gSpriteSheetTexture.render( x * TILE_SIZE + X_SHIFT, y * TILE_SIZE + Y_SHIFT, &gSpriteClips[ mainBoard[x][y] + 4] );
                    }
                }

                gSpriteSheetTexture.render( 140, 140, &gSpriteClips[currentNextBrickType + 4]);
                for( int i = 0; i < 3; i++ )
                {
                    gSpriteSheetTexture.render( 140 + brickCoords[currentNextBrickType][2 * i] * TILE_SIZE, 140 + brickCoords[currentNextBrickType][2 * i + 1] * TILE_SIZE, &gSpriteClips[currentNextBrickType + 4]);
                }

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        SDL_RemoveTimer( timerShifting );

        }
    }
    //Free resources and close SDL
    close();

    return 0;
}

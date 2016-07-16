#pragma once

#define _DEBUG_

#define TILE_SIZE 26   // with space 2 px
#define TILE_SIZE_W 24 // without space
#define X_SHIFT -118   // coord x of beginning map 
#define Y_SHIFT -236   // as above but y
#define TOP_LEFT_CORNER_COORD_X -118
#define TOP_LEFT_CORNER_COORD_Y 258
#define BRICK_START_X (TOP_LEFT_CORNER_COORD_X+4*TILE_SIZE)
#define BRICK_START_Y (TOP_LEFT_CORNER_COORD_Y-1*TILE_SIZE)
#define TILE_STENCIL_STR "default/game_object_tile_stencil.png"
#define TILE_DGREEN_STR  "default/game_object_tile_green_dark.png"
#define TILE_LGREEN_STR  "default/game_object_tile_green_light.png"
#define TILE_MAGENTA_STR "default/game_object_tile_magenta.png"
#define TILE_ORANGE_STR  "default/game_object_tile_orange.png"
#define TILE_RED_STR     "default/game_object_tile_red.png"
#define TILE_VIOLET_STR  "default/game_object_tile_violet.png"
#define TILE_YELLOW_STR  "default/game_object_tile_yellow.png"

#define SOUND_CLICK 1
#define SOUND_ROTATE 2
#define SOUND_HAMMER 3


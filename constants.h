#ifndef CONSTANTS_H
#define CONSTANTS_H
const short GRID_LENGTH = 16;
const short GRID_HEIGHT = 16;
const short PIXEL_WIDTH = 32;
const short WALL_THICKNESS = 4;
const short SCREEN_HEIGHT = PIXEL_WIDTH * GRID_HEIGHT + 2 * WALL_THICKNESS;
const short SCREEN_WIDTH = PIXEL_WIDTH * GRID_HEIGHT + 2 * WALL_THICKNESS;
const short FRAME_RATE = 4;
const short FRAME_DELAY = 500 / FRAME_RATE;
#endif
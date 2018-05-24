#ifndef ARKANOID_DEFINES_H_
#define ARKANOID_DEFINES_H_

/* Includes */

#include <GL/glfw.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/* Definitions */

#define ARKANOID_PI            4 * atan(1)

#define ARKANOID_WINDOW_WIDTH  600
#define ARKANOID_WINDOW_HEIGHT 800
#define ARKANOID_WINDOW_MODE   GLFW_WINDOW
#define ARKANOID_COLOR_DEPTH   8
#define ARKANOID_TITLE         "ARKANOID - Matteo Ragni Games"
#define ARKANOID_PADDING       30

#define ARKANOID_BLOCK_ROWS    10
#define ARKANOID_BLOCK_COLS    20
#define ARKANOID_BLOCK_HEIGHT  20
#define ARKANOID_BLOCK_WIDTH   (ARKANOID_WINDOW_WIDTH - 2 * ARKANOID_PADDING) / ((float)ARKANOID_BLOCK_COLS)
#define ARKANOID_BLOCK_DIM     ARKANOID_BLOCK_ROWS * ARKANOID_BLOCK_COLS
#define ARKANOID_BLOCKS_X0     (0.5 * ARKANOID_WINDOW_WIDTH - ARKANOID_PADDING - 0.5 * ARKANOID_BLOCK_WIDTH) / (0.5 * (float)ARKANOID_WINDOW_WIDTH)
#define ARKANOID_BLOCKS_Y0     0.8
#define ARKANOID_BLOCKS_W0     2 * ARKANOID_BLOCK_WIDTH / ((float)ARKANOID_WINDOW_WIDTH)
#define ARKANOID_BLOCKS_H0     2 * ARKANOID_BLOCK_HEIGHT / ((float)ARKANOID_WINDOW_HEIGHT)

#define ARKANOID_WALL_X        (ARKANOID_WINDOW_WIDTH - ARKANOID_PADDING) / ((float)ARKANOID_WINDOW_WIDTH)
#define ARKANOID_WALL_Y        (ARKANOID_WINDOW_HEIGHT - ARKANOID_PADDING) / ((float)ARKANOID_WINDOW_HEIGHT)
#define ARKANOID_BLOCK_X_EPS   3.0 / ARKANOID_WINDOW_WIDTH
#define ARKANOID_BLOCK_Y_EPS   3.0 / ARKANOID_WINDOW_HEIGHT

#define ARKANOID_BALL_IC_VX    30.0 / ARKANOID_WINDOW_WIDTH
#define ARKANOID_BALL_IC_VY    30.0 / ARKANOID_WINDOW_HEIGHT
#define ARKANOID_BALL_RADIUS_X 15.0 / ((float)ARKANOID_WINDOW_WIDTH)
#define ARKANOID_BALL_RADIUS_Y 15.0 / ((float)ARKANOID_WINDOW_HEIGHT)
#define ARKANOID_BALL_FACES    15

#define ARKANOID_BAR_Y0        -0.8
#define ARKANOID_BAR_W0        300.0 / ARKANOID_WINDOW_WIDTH
#define ARKANOID_BAR_H0        30.0 / ARKANOID_WINDOW_HEIGHT
#define ARKANOID_BAR_SPEED     50.0 / ARKANOID_WINDOW_HEIGHT

#define ARKANOID_IC_LIFES      3
#define ARKANOID_TEXT_LENGTH   140
#define ARKANOID_LETS_GAME     0
#define ARKANOID_END_LIFES     1
#define ARKANOID_END_BLOCKS    2

#define ARKANOID_sign(x)       (x >= 0 ? 1 : -1)

/* Types */

typedef struct ArkanoidBlock {
  GLfloat x0;
  GLfloat x1;
  GLfloat y0;
  GLfloat y1;
  GLfloat cx;
  GLfloat cy;
  GLfloat r;
  GLfloat g;
  GLfloat b;
  char status;
} ArkanoidBlock;

typedef struct ArkanoidBar {
  GLfloat cx;
  GLfloat vx;
  GLfloat size;
} ArkanoidBar;

typedef struct ArkanoidBall {
  GLfloat vx;
  GLfloat vy;
  GLfloat x;
  GLfloat y;
  GLfloat rx;
  GLfloat ry;
  char run;
} ArkanoidBall;

typedef struct ArkanoidGame {
  int blocks_count;
  ArkanoidBlock blocks[ARKANOID_BLOCK_DIM];
  ArkanoidBar bar;
  ArkanoidBall ball;
  int lifes;
  int status;
} ArkanoidGame;

#endif /* ARKANOID_DEFINES_H_ */
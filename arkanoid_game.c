#include "arkanoid_game.h"

ArkanoidGame game;

ArkanoidGame *ArkanoidGame_get_game() {
  return (&game);
}

void ArkanoidGame_init_game() {
  ArkanoidGame_get_game()->lifes = ARKANOID_IC_LIFES;
  ArkanoidGame_get_game()->status = ARKANOID_LETS_GAME;

  ArkanoidGame_init_blocks();
  ArkanoidGame_init_ball();
  ArkanoidGame_init_bar();
}

void ArkanoidGame_color_map(int row, int col, ArkanoidBlock *block) {
  GLfloat dist = ((float)(col + row)) / ((float)(ARKANOID_BLOCK_ROWS + ARKANOID_BLOCK_COLS));

  // Evaluating red color
  if (dist >= 0.5) {
    block->r = 0;
  } else {
    block->r = 1 - 2 * dist;
  }

  // Evaluating green color
  if (dist <= 0.25) {
    block->g = 0;
  } else if (dist >= 0.75) {
    block->g = 0;
  } else if ((dist >= 0.25) && (dist <= 0.5)) {
    block->g = 4 * (dist - 0.25);
  } else {
    block->g = -4 * (dist - 0.5) + 1;
  }

  // Evaluating blue color
  if (dist <= 0.5) {
    block->b = 0;
  } else {
    block->b = 2 * (dist - 0.5);
  }
}

void ArkanoidGame_move_left(int action) {
  if (action == GLFW_PRESS) {
    ArkanoidGame_get_game()->bar.vx = -ARKANOID_BAR_SPEED;
  } else {
    ArkanoidGame_get_game()->bar.vx = 0;
  }
}

void ArkanoidGame_move_right(int action) {
  if (action == GLFW_PRESS) {
    ArkanoidGame_get_game()->bar.vx = ARKANOID_BAR_SPEED;
  } else {
    ArkanoidGame_get_game()->bar.vx = 0;
  }
}

void ArkanoidGame_start_ball(int action) {
  ArkanoidGame_get_game()->ball.run ^= 0x1;
}

void ArkanoidGame_init_ball() {
  ArkanoidGame *game = ArkanoidGame_get_game();

  game->ball.x = 0;
  game->ball.y = 0;
  game->ball.rx = ARKANOID_BALL_RADIUS_X;
  game->ball.ry = ARKANOID_BALL_RADIUS_Y;
  srand(time(NULL));
  GLfloat angle = (rand() / ((float)RAND_MAX)) * (ARKANOID_PI - ARKANOID_PI / 6) + ARKANOID_PI + ARKANOID_PI / 12.0;
  game->ball.vx = ARKANOID_BALL_IC_VX * cos(angle);
  game->ball.vy = ARKANOID_BALL_IC_VY * sin(angle);
  game->ball.run = 0x0;
}

void ArkanoidGame_init_bar() {
  ArkanoidGame *game = ArkanoidGame_get_game();
  game->bar.cx = 0;
  game->bar.vx = 0;
  game->bar.size = ARKANOID_BAR_W0;
}

void ArkanoidGame_init_blocks() {
  ArkanoidGame *game = ArkanoidGame_get_game();
  game->blocks_count = ARKANOID_BLOCK_DIM;

  for (int col = 0; col < ARKANOID_BLOCK_COLS; col++)
  {
    for (int row = 0; row < ARKANOID_BLOCK_ROWS; row++)
    {
      ArkanoidBlock *block = &(game->blocks[row * ARKANOID_BLOCK_COLS + col]);
      block->status = 0x1;
      block->cx = -ARKANOID_BLOCKS_X0 + col * ARKANOID_BLOCKS_W0;
      block->cy = ARKANOID_BLOCKS_Y0 - row * ARKANOID_BLOCKS_H0;

      block->x0 = block->cx - 0.5 * ARKANOID_BLOCKS_W0 + ARKANOID_BLOCK_X_EPS;
      block->x1 = block->cx + 0.5 * ARKANOID_BLOCKS_W0 - ARKANOID_BLOCK_X_EPS;
      block->y0 = block->cy + 0.5 * ARKANOID_BLOCKS_H0 - ARKANOID_BLOCK_Y_EPS;
      block->y1 = block->cy - 0.5 * ARKANOID_BLOCKS_H0 + ARKANOID_BLOCK_Y_EPS;

      ArkanoidGame_color_map(row, col, block);
    }
  }
}

void ArkanoidGame_main_loop() {
  ArkanoidGame * game = ArkanoidGame_get_game();
  
  // Bar Loop
  GLfloat bar_min = -ARKANOID_WALL_X + (0.5 * game->bar.size);
  GLfloat bar_max = ARKANOID_WALL_X - (0.5 * game->bar.size);
  if (game->ball.run) {
    game->bar.cx += game->bar.vx;
    if (game->bar.cx > bar_max)
      game->bar.cx = bar_max;
    if (game->bar.cx < bar_min)
      game->bar.cx = bar_min;
  }
  // Ball Loop
  if (game->ball.run) {
    game->ball.x += game->ball.vx;
    game->ball.y += game->ball.vy;
  }
  if (game->status == ARKANOID_LETS_GAME) {
    ArkanoidGame_blocks_hit();
    ArkanoidGame_wall_hit();
    ArkanoidGame_bar_hit();
    ArkanoidGame_ball_threshold();
  }
  ArkanoidGame_game_over();
}

void ArkanoidGame_blocks_hit() {
  ArkanoidGame *game = ArkanoidGame_get_game();
  ArkanoidBlock *blocks = game->blocks;

  for (int i = 0; i < ARKANOID_BLOCK_DIM; i++) {
    if (blocks[i].status) {
      char cond_x = (fabs(blocks[i].cx - game->ball.x) < (0.5 * ARKANOID_BLOCKS_W0 - ARKANOID_BLOCK_X_EPS + 0.5 * ARKANOID_BALL_RADIUS_X));
      char cond_y = (fabs(blocks[i].cy - game->ball.y) < (0.5 * ARKANOID_BLOCKS_H0 - ARKANOID_BLOCK_Y_EPS + 0.5 * ARKANOID_BALL_RADIUS_Y));
      if (cond_x && cond_y) {
        blocks[i].status = 0x0;
        game->blocks_count--;
        game->bar.size = ARKANOID_BAR_W0 * (0.33) * (2 * (game->bar.size/(float)ARKANOID_BLOCK_DIM) + 1);
        game->ball.vy = -game->ball.vy;
        break;
      }
    }
  }
}

void ArkanoidGame_wall_hit() {
  ArkanoidBall *ball = &(ArkanoidGame_get_game()->ball);
  char cond_x = (fabs(ball->x) + ARKANOID_BALL_RADIUS_X) >= ARKANOID_WALL_X;
  if (cond_x) {
    ball->vx = -ARKANOID_sign(ball->x) * fabs(ball->vx);
  }
  char cond_y = (fabs(ball->y) + ARKANOID_BALL_RADIUS_Y) >= ARKANOID_WALL_Y;
  if (cond_y) {
    ball->vy = -ARKANOID_sign(ball->y) * fabs(ball->vy);
  }
}

void ArkanoidGame_bar_hit() {
  ArkanoidBall *ball = &(ArkanoidGame_get_game()->ball);
  GLfloat dx = ball->x - (ArkanoidGame_get_game()->bar.cx);
  GLfloat dy = ball->y - ARKANOID_BAR_Y0;

  char cond_x = fabs(dx) <= (0.5 * ArkanoidGame_get_game()->bar.size + ARKANOID_BALL_RADIUS_X);
  char cond_y = (dy > -ARKANOID_BALL_RADIUS_Y) && (dy < (0.5 * ARKANOID_BAR_H0 + ARKANOID_BALL_RADIUS_Y));

  if (cond_x && cond_y && (ball->vy < 0)) {
    GLfloat alpha = -ARKANOID_PI / (2 * ArkanoidGame_get_game()->bar.size) * dx + ARKANOID_PI * 0.5;
    ball->vx = ARKANOID_BALL_IC_VX * cos(alpha);
    ball->vy = ARKANOID_BALL_IC_VY * sin(alpha);
  }
}

void ArkanoidGame_ball_threshold() {
  ArkanoidGame *game = ArkanoidGame_get_game();
  if (game->ball.y < ARKANOID_BAR_Y0 - 2 * ARKANOID_BALL_RADIUS_Y) {
    game->lifes = game->lifes - 1;
    if (game->lifes > 0) {
      ArkanoidGame_init_ball();
    } else {
      // ArkanoidGame_init_game();
      game->ball.run = 0x0;
    }
  }
}

void ArkanoidGame_game_over() {
  ArkanoidGame *game = ArkanoidGame_get_game();
  if (game->blocks_count == 0)
    game->status = ARKANOID_END_BLOCKS;
  if (game->lifes == 0)
    game->status = ARKANOID_END_LIFES;
}
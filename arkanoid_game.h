#ifndef ARKANOID_GAME_H_
#define ARKANOID_GAME_H_

#include "arkanoid_defines.h"
ArkanoidGame * ArkanoidGame_get_game();

void ArkanoidGame_init_game();
void ArkanoidGame_init_blocks();
void ArkanoidGame_init_ball();
void ArkanoidGame_init_bar();

void ArkanoidGame_main_loop();
void ArkanoidGame_color_map(int row, int col, ArkanoidBlock *block);

void ArkanoidGame_move_left(int action);
void ArkanoidGame_move_right(int action);
void ArkanoidGame_start_ball(int action);

void ArkanoidGame_blocks_hit();
void ArkanoidGame_wall_hit();
void ArkanoidGame_bar_hit();
void ArkanoidGame_ball_threshold();
void ArkanoidGame_game_over();

#endif /* ARKANOID_GAME_H_ */
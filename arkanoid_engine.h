#ifndef ARKANOID_ENGINE_H_
#define ARKANOID_ENGINE_H_

#include "arkanoid_defines.h"
#include "arkanoid_game.h"

int ArkanoidEngine_init();
int ArkanoidEngine_terminate();

int ArkanoidEngine_renderer(ArkanoidGame *game);
int ArkanoidEngine_render_field();
int ArkanoidEngine_render_blocks(const ArkanoidBlock *blocks);
int ArkanoidEngine_render_ball(const ArkanoidBall *ball);
int ArkanoidEngine_render_bar(const ArkanoidBar *bar);
int ArkanoidEngine_render_text(ArkanoidGame *game);
int ArkanoidEngine_render_status(ArkanoidGame *game);

void ArkanoidEngine_keyboard_callback(int key, int action);


#endif /* ARKANOID_ENGINE_H_ */
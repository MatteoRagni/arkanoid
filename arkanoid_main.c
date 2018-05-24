/* Arkanoid - Matteo Ragni */

#include "arkanoid_defines.h"
#include "arkanoid_engine.h"
#include "arkanoid_game.h"


int main(int argc, char **argv) {
  glutInit(&argc, argv); // Maybe I should fix this stuff
  int running = ArkanoidEngine_init();
  ArkanoidGame_init_game();

  while (running) {
    ArkanoidEngine_renderer(ArkanoidGame_get_game());

    running = glfwGetWindowParam(GLFW_OPENED);
    glfwPollEvents();
  }

  ArkanoidEngine_terminate();
  return 0;
}
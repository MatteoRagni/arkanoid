#include "arkanoid_engine.h"

int ArkanoidEngine_init() {
  if (!glfwInit()) {
    printf("glfwInit error\n");
    return GL_FALSE;
  }

  glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
  if (!glfwOpenWindow(
          ARKANOID_WINDOW_WIDTH,
          ARKANOID_WINDOW_HEIGHT,
          ARKANOID_COLOR_DEPTH,
          ARKANOID_COLOR_DEPTH,
          ARKANOID_COLOR_DEPTH,
          0, 0, 0, ARKANOID_WINDOW_MODE)) {
    ArkanoidEngine_terminate();
    printf("glfwOpenWindow error\n");
    return GL_FALSE;
  }
  glfwSetWindowTitle(ARKANOID_TITLE);
  glfwSetKeyCallback(ArkanoidEngine_keyboard_callback);
  glClearColor(0.1, 0.1, 0.1, 1);
  glfwPollEvents();

  return GL_TRUE;
}

int ArkanoidEngine_terminate() {
  glfwTerminate();
  return GL_TRUE;
}

int ArkanoidEngine_renderer(ArkanoidGame *game) {
  #ifdef ARKANOID_LOOP_TIME
  clock_t t_start = clock();
  #endif
  ArkanoidGame_main_loop();
  ArkanoidEngine_render_field();
  ArkanoidEngine_render_blocks(game->blocks);
  ArkanoidEngine_render_ball(&(game->ball));
  ArkanoidEngine_render_bar(&(game->bar));
  ArkanoidEngine_render_text(game);
  ArkanoidEngine_render_status(game);

  glfwSwapBuffers();
#ifdef ARKANOID_LOOP_TIME
  clock_t t_end = clock();
  float dt = (t_end - t_start) / ((float)CLOCKS_PER_SEC) * 1e3;
  printf("Loop time: % 3.5f ms\n", dt);
  #endif
  glfwPollEvents();
  return GL_TRUE;
}

int ArkanoidEngine_render_field() {
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 1);
    glVertex2f(-ARKANOID_WALL_X,  ARKANOID_WALL_Y);
    glVertex2f( ARKANOID_WALL_X,  ARKANOID_WALL_Y);
    glVertex2f( ARKANOID_WALL_X, -ARKANOID_WALL_Y);
    glVertex2f(-ARKANOID_WALL_X, -ARKANOID_WALL_Y);
  glEnd();

  return GL_TRUE;
}

int ArkanoidEngine_render_blocks(const ArkanoidBlock *blocks) {
  for (int i = 0; i < ARKANOID_BLOCK_DIM; i++) {
    if (blocks[i].status) {
      glColor3f(blocks[i].r, blocks[i].g, blocks[i].b);
      glRectf(blocks[i].x0, blocks[i].y0, blocks[i].x1, blocks[i].y1);
    }
  }
  return GL_TRUE;
}

int ArkanoidEngine_render_ball(const ArkanoidBall *ball) {
  GLfloat x, y, s;
  glColor3f(1, 1, 1);
  glBegin(GL_POLYGON);
  for (int i = 0; i < ARKANOID_BALL_FACES; i++)   {
    s = i / ((float)ARKANOID_BALL_FACES);
    x = ball->x + ball->rx * cos(2 * ARKANOID_PI * s);
    y = ball->y + ball->ry * sin(2 * ARKANOID_PI * s);
    glVertex2f(x, y);
  }
  
  glEnd();
  return GL_TRUE;
}

int ArkanoidEngine_render_bar(const ArkanoidBar *bar) {
  glColor3f(1, 1, 1);
  glRectf(
      bar->cx - (bar->size * 0.5), ARKANOID_BAR_Y0 + (0.5 * ARKANOID_BAR_H0),
      bar->cx + (bar->size * 0.5), ARKANOID_BAR_Y0 - (0.5 * ARKANOID_BAR_H0));
  return GL_TRUE;
}

void ArkanoidEngine_keyboard_callback(int key, int action) {
  switch(key) {
    case GLFW_KEY_LEFT:
      ArkanoidGame_move_left(action);
    break;
    case GLFW_KEY_RIGHT:
      ArkanoidGame_move_right(action);
    break;
    case GLFW_KEY_LCTRL:
      if (action == GLFW_PRESS)
        ArkanoidGame_start_ball(action);
    break;
    case GLFW_KEY_ESC:
      if (action == GLFW_PRESS)
        ArkanoidGame_init_game(action);
    default:
    break;
  }
}

int ArkanoidEngine_render_text(ArkanoidGame * game) {
  int points = ARKANOID_BLOCK_DIM - game->blocks_count;
  char line[ARKANOID_TEXT_LENGTH];
  int length = snprintf(line, ARKANOID_TEXT_LENGTH, "LIFES: % 1d, POINTS: % 6d bs", game->lifes, points);
  glRasterPos2d(-0.9 , 0.9);
  for (int i = 0; i < length; i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, line[i]);
  }
  return GL_TRUE;
}

int ArkanoidEngine_render_status(ArkanoidGame *game) {
  if (game->status == ARKANOID_END_BLOCKS) {
    glRasterPos2d(-0.1, -0.1);
    char line1[] = "YOU WIN!";
    for (int i = 0; i < 8; i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, line1[i]);
    }
    glRasterPos2d(-0.3, -0.2);
    char line2[] = "Press [ESC] to reset";
    for (int i = 0; i < 21; i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, line2[i]);
    }
  }
  if (game->status == ARKANOID_END_LIFES) {
    glRasterPos2d(-0.15, -0.1);
    char line1[] = "GAME OVER!";
    for (int i = 0; i < 11; i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, line1[i]);
    }
    glRasterPos2d(-0.3, -0.2);
    char line2[] = "Press [ESC] to reset";
    for (int i = 0; i < 21; i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, line2[i]);
    }
  }
  return GL_TRUE;
}
/*
Dado dois objetos na tela, usar:
A-W-S-D para movimentar o da esquerda, ou
as setas para movimentar o da direita.
Os dois não devem se encostar.
*/

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN //remove MFC overhead from windows.h which can cause slowness
#define WIN32_EXTRA_LEAN
#include <windows.h>
#endif

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH  500





void drawScene(void) {
}



void handleMouseClicks(int button, int state, int x, int y) {
  if (state != GLUT_DOWN) return;

  if (button == GLUT_LEFT_BUTTON) {
  } else if (button == GLUT_RIGHT_BUTTON) {
  }
}

void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
    case 27:// ESC para fechar
      exit(1);
  }
}

void handleResize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void init(void) {
  glClearColor(1, 1, 1, 0);

  // glMatrixMode(GL_PROJECTION);
  // gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

  // glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // glViewport(0, 0, 100, 200);

  // TODO: iniciar octree
}


int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);

  glutCreateWindow("Trabalho Final: Octree para Detectar Colisoes");

  init();

  glutDisplayFunc(drawScene);
  glutMouseFunc(handleMouseClicks);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);

  glutMainLoop();
  return 0;
}

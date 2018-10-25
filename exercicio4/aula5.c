/*
Exercício 4:

----- INSTRUÇÕES DE USO -----
- compilar $ g++ aula5.c -o aula5 -lGL -lGLU -lglut
- executar $ ./aula5

Usar o botão esquerdo do mouse para escolher os 3 pontos de controle -> irá gerar a parábola;
Pressionar o botão esquerdo do mouse sobre um dos pontos e arrastá-lo para redesenhar a parábola.
*/

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN //remove MFC overhead from windows.h which can cause slowness
#define WIN32_EXTRA_LEAN
#include <windows.h>
#endif

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MOUSE_SCROLL_UP 3
#define MOUSE_SCROLL_DOWN 4



void display()
{
  glClear(GL_COLOR_BUFFER_BIT); // clear buffers to preset values
  //      ^ Indicates the buffers currently enabled for color writing

  // primitivas:
  // GL_POINTS     //individual points
  // GL_LINES      //pairs of vertices used to draw segments
  // GL_TRIANGLES  //triple of vertices used to draw triangles
  // GL_QUADS      //quandruples of vertices used to draw quadrilaterals
  // GL_POLYGON    //boundary of a polygon
  glBegin(GL_POLYGON);
  //--- commands ---
  glColor3f(1.0, 1.0, 0.0);

  glVertex2f(-0.5, -0.5);
  glVertex2f(-0.5, 0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(0.5, -0.5);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f);

  glVertex2f(-1, 0);
  glVertex2f(1, 0);

  glVertex2f(0, -1);
  glVertex2f(0, 1);
  glEnd();

  glFlush(); //forces execution before the gathering is complete
}


void gerenciaMouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {

  }

  glutPostRedisplay();
}


void init() {
  glClearColor(1, 1, 1, 1.0);
  gluOrtho2D(0.0, 160.0, 4.9, 120.0);
}



double randomEntre0e1() {
  return (double)rand() / (double)RAND_MAX;
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(200, 200);
  glutInitWindowSize(700, 500);

  glutCreateWindow("Exercício 4 - Editor de Parábolas");

  init();

  printf("Usar o botão esquerdo do mouse para escolher os 3 pontos de controle\nPressionar o botão esquerdo do mouse sobre um dos pontos e arrastá-lo para redesenhar a parábola\n");

  glutDisplayFunc(display);
  glutMouseFunc(gerenciaMouse);

  glutMainLoop();
}

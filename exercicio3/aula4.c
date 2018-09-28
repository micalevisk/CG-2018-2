/*
Exercício 3:
praticaCG042018.pptx

----- INSTRUÇÕES DE USO -----
- compilar $ g++ aula4.c -o aula4 -lGL -lGLU -lglut
- executar $ ./aula4

Pressionar a tecla L para lançar o foguete
Pressionar a tecla R para reiniciar
Pressionar a tecla ESC para fechar
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

#define MAX_Y 4.0

GLfloat yLocation, xLocation, zRotationAngle;
GLfloat fireY[] = {.05, .5};
unsigned short curr = 0;
GLfloat y;

bool animacaoIniciada;
int sentido;
float delay = 1.0; // para o controle do tempo


void inicializarEstados(void) {
  xLocation = yLocation = zRotationAngle = 0;
  animacaoIniciada = false;
  sentido = 1;
}

/* ======================================= */

void bico() {
  glBegin(GL_TRIANGLES);
  glColor3f(0.57, 0.38, 0.20);
  glVertex3f(3.0, 6.0, 0);
  glVertex3f(4.0, 8.0, 0);
  glVertex3f(5.0, 6.0, 0);
  glEnd();
}

void corpo() {
  glBegin(GL_QUADS);
  glColor3f(0.80, 0.50, 0.20);
  glVertex3f(3.0, 1.0, 0);
  glVertex3f(5.0, 1.0, 0);
  glVertex3f(5.0, 6.0, 0);
  glVertex3f(3.0, 6.0, 0);
  glEnd();
}

void asasEsquerda() {
  glBegin(GL_TRIANGLES);
  glColor3f(0.8, 0.2, 0.2);
  glVertex3f(1.5, 1.0, 0);
  glVertex3f(3.0, 1.0, 0);
  glVertex3f(3.0, 3.0, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.9, 0.2, 0.2);
  glVertex3f(1.5, 3.0, 0);
  glVertex3f(3.0, 3.5, 0);
  glVertex3f(3.0, 5.0, 0);
  glEnd();
}

void asasDireita() {
  glBegin(GL_TRIANGLES);
  glColor3f(0.8, 0.2, 0.2);
  glVertex3f(5.0, 1.0, 0);
  glVertex3f(6.5, 1.0, 0);
  glVertex3f(5.0, 3.0, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.9, 0.2, 0.2);
  glVertex3f(5, 5, 0);
  glVertex3f(5, 3.5, 0);
  glVertex3f(6.5, 3, 0);
  glEnd();
}

void fogo() {
  glBegin(GL_POLYGON);
  glColor3f(1, 0.24, 0);
  glVertex3f(3.5, 1.5, 0);//D
  glVertex3f(3.0, 1.0, 0);//A
  glVertex3f(4.0, -y, 0);//C
  glVertex3f(5.0, 1.0, 0);//B
  glVertex3f(4.5, 1.5, 0);//E
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1, 0.815, 0);
  glVertex3f(3.5, 1.5, 0);//D
  glVertex3f(3.5, 1.05, 0);//F
  glVertex3f(4.0, y-0.3, 0);//G
  glVertex3f(4.5, 1.05, 0);//H
  glVertex3f(4.5, 1.5, 0);//E
  glEnd();
}


void desenharFoguete(void) {// display
  #ifdef DEBUG
  fprintf(stderr, "(%2f, %.2f)\n", xLocation, yLocation);
  #endif

  // glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (animacaoIniciada) {
    if (yLocation >= MAX_Y) { // começar a descer
      sentido = -1;
      delay = 1.5;
    }

    glTranslatef(xLocation, yLocation, 0);
  } else {
    glPushMatrix();
  }

  bico();
  if (animacaoIniciada) fogo();
  asasEsquerda();
  asasDireita();
  corpo();

  glFlush();
}

/* ======================================= */

void Timer(int value) {
  if (!animacaoIniciada) return;

  yLocation += 0.05 * sentido;
  y = fireY[(curr = !curr)] * sentido;

  if (yLocation < 0) {
    xLocation = yLocation = 0;
  }

  glutPostRedisplay();
  glutTimerFunc(60 * delay, Timer, value);
}

void init() {
  glClearColor(0.9, 0.95, 0.96, 1.0);
  // glClearColor(0.45, 0.81, 0.87, 1);
  gluOrtho2D(0.0, 160.0, 4.9, 120.0);
}


void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'L':// lançar
    case 'l':
      animacaoIniciada = !animacaoIniciada;
      Timer(0);
      break;
    case 'R':// restaurar foguete
    case 'r':
      inicializarEstados();
      glPopMatrix();
      glutPostRedisplay();
      break;
    case 27:// ESC para fechar
      exit(1);
  }
}


int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(200, 200);
  glutInitWindowSize(700, 500);

  glutCreateWindow("Exercício 3 - Foguete Animado");

  init();

  Timer(0);

  inicializarEstados();
  printf("Pressione L para lançar o foguete\nPressione R para reiniciar\nPressione ESC para fechar\n");

  glScalef(3, 4, 3);
  glutDisplayFunc(desenharFoguete);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
}

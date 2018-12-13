/*
Exercício 5:
Algoritmo de De Casteljau aplicado para desenhar uma curva com vários pontos de controle.

----- INSTRUÇÕES DE USO -----
- compilar $ g++ aula6.c -o aula6 -lGL -lGLU -lglut
- executar $ ./aula6
*/

// baseado em https://gist.github.com/ynurmahomed/5969035

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN //remove MFC overhead from windows.h which can cause slowness
#define WIN32_EXTRA_LEAN
#include <windows.h>
#endif

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define CTRL_POINT_DIAMETER 10.0f

#define QTD_PONTOS_CONTROLE 3
#define MOUSE_SCROLL_UP 3
#define MOUSE_SCROLL_DOWN 4

typedef struct { float x, y; } Ponto;

unsigned qtdPontosPlotados, qtdPontosAlocados;
Ponto* pontosControle = (Ponto*) malloc(sizeof(Ponto));



void desenharPonto(Ponto ponto) {
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glPointSize(CTRL_POINT_DIAMETER);
  glColor3f(qtdPontosPlotados / 25.0, qtdPontosPlotados / 255.0, qtdPontosPlotados / 3.0);

  glBegin(GL_POINTS);
  glVertex2f(ponto.x, ponto.y);
  glEnd();

  glFlush();
}

void adicionarPonto(Ponto ponto) {
  qtdPontosPlotados++;

  if (qtdPontosPlotados > qtdPontosAlocados) {
    unsigned novaQtdPontosAlocados = qtdPontosPlotados + 4;
    pontosControle = (Ponto*) realloc(pontosControle, novaQtdPontosAlocados * sizeof(Ponto));
    qtdPontosAlocados = novaQtdPontosAlocados;
  }
  pontosControle[qtdPontosPlotados - 1] = ponto;
}


Ponto deCasteljau(Ponto* ctrlPoints, float t, int n) {
  Ponto *aux = (Ponto*) malloc (sizeof(Ponto) * n);
  memcpy(aux, ctrlPoints, sizeof(Ponto) * n);

  for (int k = 1; k < n; ++k) {
    for (int i = 0; i < n - k; ++i) {
      aux[i].x = (1 - t) * aux[i].x + t * aux[i + 1].x;
      aux[i].y = (1 - t) * aux[i].y + t * aux[i + 1].y;
    }
  }

  Ponto p = aux[0];
  free(aux);

  return p;
}

void desenharCurva() {
  float step = 0.001f;

  glColor3f(0.208f, 0.0f, 0.0f);
  glLineWidth(2);

  // A curva
  glBegin(GL_LINE_STRIP);

  for (float t = 0; t <= 1; t += step) {
    Ponto p = deCasteljau(pontosControle, t, 300);
    glVertex2f(p.x, p.y);
  }

  glEnd();

  glFlush();
}


void display(void) {
  GLint i;
  GLfloat t, x, y; // variável de parametrização `t`

  glClear(GL_COLOR_BUFFER_BIT);
  desenharCurva();
  /*

  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_STRIP);
  for (i = 0; i < QTD_PONTOS_CONTROLE; i++)
  {
    glVertex2f(p[i][0], p[i][1]);
  }
  glEnd();

  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_POINTS);
 


  glEnd();

  */
  glFlush();
}

void onMouseEvent(int botao, int estado, int x, int y) {
  if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
    float cx = ((float)(2.0f * x) / (float) WINDOW_WIDTH)  - 1.0f;
    float cy = ((float)(2.0f * y) / (float) WINDOW_HEIGHT) - 1.0f;
    cy *= -1.0f; // normalizando

    Ponto p = { .x = cx, .y = cy };

    adicionarPonto(p);
    desenharPonto(p);
  }
}


void init(void) {
  qtdPontosPlotados = 0;
  qtdPontosAlocados = 4;

  pontosControle = (Ponto*) malloc(qtdPontosAlocados * sizeof(Ponto));

  glClearColor(1, 1, 1, 0);
}


int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);

  glutCreateWindow("Exercício 5 - ");

  init();
  glutDisplayFunc(display);
  glutMouseFunc(onMouseEvent);

  glutMainLoop();
}

// vide: https://javascript.info/bezier-curve
/*
Exercício 4:

----- INSTRUÇÕES DE USO -----
- compilar $ g++ aula5.c -o aula5 -lGL -lGLU -lglut
- executar $ ./aula5

Usar o botão esquerdo do mouse para escolher os 3 pontos de controle -> irá gerar a parábola;
Pressionar o botão esquerdo do mouse sobre um dos pontos e arrastá-lo para redesenhar a parábola.
botão direito do mouse - limpar pontos.
ESC - fechar o programa.
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

#define QTD_PONTOS_CONTROLE 3

#define X_b(x0, x1, x2, t) ( x0 * pow(1 - t, 2.0) + x1 * 2 * t * (1 - t) + x2 * pow(t, 2) )
#define Y_b(y0, y1, y2, t) ( y0 * pow(1 - t, 2.0) + y1 * 2 * t * (1 - t) + y2 * pow(t, 2) )

/*
|x0|y0|  -- b0
|x1|y1|  -- b1
|x2|y2|  -- b2
*/
GLfloat pontosControle[QTD_PONTOS_CONTROLE][2]; // guarda as coordenadas dos 3 pontos de controle, um ponto por linha da matriz
unsigned PCCorrente; // índice pra linha da matriz acima; indica o ponto de controle corrente; intervalo [0;2]


inline GLfloat X(unsigned b) { return pontosControle[b][0]; }
inline GLfloat Y(unsigned b) { return pontosControle[b][1]; }

void zerarPontosControle(void) {
  PCCorrente = 0;

  pontosControle[0][0] = 0;
  pontosControle[0][1] = 0;

  pontosControle[1][0] = 0;
  pontosControle[1][1] = 0;

  pontosControle[2][0] = 0;
  pontosControle[2][1] = 0;
}

/*
void desenharPontoDeControle(unsigned b) {
  glPointSize(5);

  glBegin(GL_POINTS);
  glColor3f(b+0.8/2, 0.3*b, 0.6*b);
  glVertex2f( X(b), Y(b) );
  glEnd();

  glFlush();
}
*/

void atualizarPlotPonto(int x, int y) {
  // transformando as coordenadas da janela
  float cx = ((float)(2.0f * x) / (float) WINDOW_WIDTH)  - 1.0f;
  float cy = ((float)(2.0f * y) / (float) WINDOW_HEIGHT) - 1.0f;
  cy *= -1.0f; // normalizando

  pontosControle[PCCorrente % QTD_PONTOS_CONTROLE][0] = cx; // atualizar a coordenada x_b
  pontosControle[PCCorrente % QTD_PONTOS_CONTROLE][1] = cy; // atualizar a coordenada y_b
  // printf("[_]> (%.2f,%.2f)\n", cx, cy);

  glutPostRedisplay();
}


void gerenciarCliqueMouse(int button, int state, int x, int y) {
  if (state != GLUT_DOWN) return;

  if (button == GLUT_LEFT_BUTTON) {
    if (PCCorrente < QTD_PONTOS_CONTROLE) {
      // printf("[mouse]> (%d,%d)\n", x,y);
      atualizarPlotPonto(x, y);
      // desenharPontoDeControle(PCCorrente);
      PCCorrente++;
    }
  } else if (button == GLUT_RIGHT_BUTTON) {
    zerarPontosControle();
    glPopMatrix();
    glutPostRedisplay();
  }
}

void gerenciarMovimentoMouse(int x, int y) {
  // TODO: identificar se algum PC foi selecionar, se foi, atualizá-lo para a coordenada movida

  float cx = ((float)(2.0f * x) / (float) WINDOW_WIDTH)  - 1.0f;
  float cy = ((float)(2.0f * y) / (float) WINDOW_HEIGHT) - 1.0f;
  printf("~ (%.2f,%.2f) \n", cx, cy);

  printf("b0(%.2f,%.2f)\n", X(0), Y(0));
  printf("b1(%.2f,%.2f)\n", X(1), Y(1));
  printf("b2(%.2f,%.2f)\n", X(2), Y(2));
  atualizarPlotPonto(x, y);
}

void gerenciarTeclado(unsigned char key, int x, int y) {
  switch (key) {
    case 27:// ESC para fechar
      exit(1);
  }
}


void init(void) {
  zerarPontosControle();
  glClearColor(1, 1, 1, 0);

  // glMatrixMode(GL_PROJECTION);
  // gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

  // glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // glViewport(0, 0, 100, 200);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  /*
  #pragma region cruz
  glBegin(GL_LINES);
  glColor3f(1.0f, .0f, .0f);

  glVertex2f(-1, 0);
  glVertex2f(1, 0);

  glVertex2f(0, -1);
  glVertex2f(0, 1);
  glEnd();
  #pragma endregion
  */

  glColor3f(0, 0, 0);

  if (PCCorrente < 1) glFlush();

  /* 1. Draw control points */
  glPointSize(8);
  glBegin(GL_POINTS);
  for (unsigned b = 0; b < PCCorrente; ++b) {
    glColor3f(b+0.8/2, 0.3*b, 0.6*b);
    glVertex2f( X(b), Y(b) );
    printf("[gl]> (%.2f,%.2f)\n", X(b), Y(b));
  }
  glEnd();

  if (PCCorrente >= QTD_PONTOS_CONTROLE) {
    /* 2. Builds segments between control points 1->2->3 */
    glColor3f(.5098f, .3686f, .1569f);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
      glVertex2f( X(0), Y(0) );
      glVertex2f( X(1), Y(1) );
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex2f( X(1), Y(1) );
      glVertex2f( X(2), Y(2) );
    glEnd();

    /* 3. The parameter t moves from 0 to 1 using 0.001 as step */
    glColor3f(1, .0f, .0f);
    glPointSize(3);
    glBegin(GL_POINTS);
    for (GLfloat t = 0.0f, step = 0.001f; t <= 1.0f; t += step) { // variável de parametrização `t` entre 0 e 1
      GLfloat x = X_b( X(0), X(1), X(2), t );
      GLfloat y = Y_b( Y(0), Y(1), Y(2), t );

      glVertex2f(x, y);
    }
    glEnd();
  }

  glFlush();
}


int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);

  glutCreateWindow("Exercicio 4 - Editor de Parabolas");

  init();

  printf("Usar o botão esquerdo do mouse para escolher os 3 pontos de controle\n"
         "Pressionar o botão esquerdo do mouse sobre um dos pontos e arrastá-lo para redesenhar a parábola\n");

  glutDisplayFunc(display);
  glutMouseFunc(gerenciarCliqueMouse); // definir o callback pro mouse para a janela corrente
  glutMotionFunc(gerenciarMovimentoMouse); // definir o callback pro movimento do mouse
  glutKeyboardFunc(gerenciarTeclado);

  glutMainLoop();
}

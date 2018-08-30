/*
Exercício 1:
praticaCG022018.pptx
slide 08:
(1) Escreva um programa em OpenGL para traçar as figuras ao lado usando segmentos de reta.
(2) Escreva um programa em OpenGL para traçar as figuras ao lado usando triângulos.

----- INSTRUÇÕES DE USO -----
- compilar $ g++ aula2.c -o aula2 -lGL -lGLU -lglut
- executar $ ./aula2
Usar o clique do botão esquerdo do mouse para trocar a estrela
*/

// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html
// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// g++ aula2.c -o aula2 -lGL -lGLU -lglut
GLfloat r = 1, g = .6, b = 0;
GLfloat lineWidth = 1;
GLfloat raio = .4;
GLfloat angle = 0;
GLboolean withCross = 0;
GLfloat delay = 1.0;
GLboolean indiceFnDisplay = 1;

static void (*displayFns[2])(void) = {};


void displayStar1(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glLineWidth(lineWidth);

  // indicar que a parte de trás dos polígonos será desenhada com preenchimento sólido
  glPolygonMode(GL_BACK, GL_FILL);
  glColor3f(r, g, b);

  //glBegin(GL_LINE_STRIP);
  glBegin(GL_POLYGON);

  // primeiro quadrante
  glVertex2f(-.1, 0);

  // meio topo
  glVertex2f(0, raio);

  // segundo quadrante
  glVertex2f(.1, 0);

  glVertex2f(raio, 0.04);

  glVertex2f(.15, -.15);

  // terceiro quadrante
  glVertex2f(.3, -.4);

  glVertex2f(0, -.2);

  // primeiro quadrante
  glVertex2f(-.3, -.4);

  glVertex2f(-.15, -.15);

  glVertex2f(-raio, 0.05);

  glVertex2f(-.1, 0);

  glEnd();


  // estrela borda
  glBegin(GL_LINE_STRIP);
  glColor3f(1, 1, 1);

  // primeiro quadrante
  glVertex2f(-.1, 0);

  // meio topo
  glVertex2f(0, raio);

  // segundo quadrante
  glVertex2f(.1, 0);

  glVertex2f(raio, 0.04);

  glVertex2f(.15, -.15);

  // terceiro quadrante
  glVertex2f(.3, -.4);

  glVertex2f(0, -.2);

  // primeiro quadrante
  glVertex2f(-.3, -.4);

  glVertex2f(-.15, -.15);

  glVertex2f(-raio, 0.05);

  glVertex2f(-.1, 0);

  glEnd();
}

void displayStar2(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(r, g, b);
  glBegin(GL_TRIANGLE_FAN);

  // centro
  glVertex2f(0, 0);
  // B
  glVertex2f(-.05, 0.04);
  // C
  glVertex2f(0, raio);
  // D
  glVertex2f(0.05, 0.04);
  // E
  glColor3f(0.4,0.7,.3);
  glVertex2f(raio, 0.04);
  // F
  glVertex2f(0.08, -0.03);
  // G
  glVertex2f(0.2, -0.3);
  // H
  glVertex2f(0, -0.1);
  // I
  glVertex2f(-0.2, -0.3);
  // J
  glColor3f(0.7,0.3,.4);
  glVertex2f(-0.08, -0.03);
  // K
  glVertex2f(-raio, 0.04);
  // B
  glVertex2f(-.05, 0.04);

  glEnd();
}


void display(void) {
  displayFns[indiceFnDisplay]();

  if (withCross) {
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);

    glVertex2f(-1, 0);
    glVertex2f(1, 0);

    glVertex2f(0, -1);
    glVertex2f(0, 1);
    glEnd();

    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(0, raio);
    glVertex2f(raio, 0);
    glEnd();
  }

  glFlush(); //forces execution before the gathering is complete
}


void keyboard(unsigned char key, int x, int y) {
  if (key == 27) {
    exit(0);
  } else {
    if (key >= 49 && key <= 57) {
      lineWidth = key - 49;
    } else if (key == 'c') {
      withCross = !withCross;
    }

    glutPostRedisplay();
  }
}

void mouse(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) {
        indiceFnDisplay = !indiceFnDisplay;
        glutPostRedisplay();
      }
      break;
  }
}


void alterarCores(void) {
  r = (GLfloat)rand() / (RAND_MAX + 1.0);
  g = (GLfloat)rand() / (RAND_MAX + 1.0);
  b = (GLfloat)rand() / (RAND_MAX + 1.0);
  angle = (GLfloat)rand();
  // marks the current window as needing to be redisplayed
  glutPostRedisplay();
}

void Timer(int value){
  glutTimerFunc(10, Timer, value);
  alterarCores();
}


void init() {
  // GFloat red, green, blue, alpha channel
  glClearColor(0, 0, 0, 0);
  // glOrtho(0, 256, 0, 256, -1, 1);

  glMatrixMode(GL_PROJECTION);
  // coloca a matriz identidade no topo da pilha
  glLoadIdentity();
  // glViewport(20, 30, 1000, 500);
  // definir uma matriz de projeção ortográfica 2D
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
  displayFns[0] = displayStar1;
  displayFns[1] = displayStar2;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(400, 400);

  glutCreateWindow("Aula 2 - Exercício 1");
  glutDisplayFunc(display);

  init();
  Timer(0);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  glutMainLoop();
}

/*
Exercício 1:
praticaCG022018.pptx
slide 08:
(1) Escreva um programa em OpenGL para traçar as figuras ao lado usando segmentos de reta.
(2) Escreva um programa em OpenGL para traçar as figuras ao lado usando triângulos.
*/

// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html
// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// g++ aula2.c -o aula2 -lGL -lGLU -lglut
GLfloat r = 1, g = .6, b = 0;
GLfloat lineWidth = 1;
GLfloat raio = .5;
GLfloat angle = 0;
GLboolean withCross = 0;

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  // desabilitar o desenho de polígonos utilizando padrões de desenho
  glDisable(GL_POLYGON_STIPPLE);

  glLineWidth(lineWidth);

  // indicar que a parte de trás dos polígonos será desenhada com preenchimento sólido
  glPolygonMode(GL_BACK, GL_FILL);
  glColor3f(r, g, b);

  glBegin(GL_LINE_STRIP);

  // primeiro quadrante
  glVertex2f(-.1, 0);

  // meio topo
  glVertex2f(0, raio);

  // segundo quadrante
  glVertex2f(.1, 0);

  glVertex2f(raio, 0.05);

  glVertex2f(-.1, -.1);

  glEnd();

  /*
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2i(143,226); glVertex2i(226,226);
  glVertex2i(226,143); glVertex2i(143,143);
  glEnd();
  */

  if (withCross) {
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);

    glVertex2f(-1, 0);
    glVertex2f(1, 0);

    glVertex2f(0, -1);
    glVertex2f(0, 1);
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
        r = (GLfloat)rand() / (RAND_MAX + 1.0);
        g = (GLfloat)rand() / (RAND_MAX + 1.0);
        b = (GLfloat)rand() / (RAND_MAX + 1.0);
        angle = (GLfloat)rand();
        // marks the current window as needing to be redisplayed
        glutPostRedisplay();
      }
      break;
  }
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
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  // glutInitWindowPosition(200, 200);

  glutCreateWindow("Aula 2 - Exercício 1");
  glutDisplayFunc(display);

  init();
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  glutMainLoop();
}

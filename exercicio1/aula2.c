/*
Exercício 1:
praticaCG022018.pptx
slide 08:
(1) Escreva um programa em OpenGL para traçar as figuras ao lado usando segmentos de reta.
(2) Escreva um programa em OpenGL para traçar as figuras ao lado usando triângulos.
*/

// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/
#include <GL/gl.h>
#include <GL/glut.h>

// g++ aula2.c -o aula2 -lGL -lGLU -lglut

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLineWidth(3);

  glBegin(GL_LINE_STRIP);
  // glBegin(GL_TRIANGLE_FAN);

  glVertex2f(-0.5, -0.5);
  glVertex2f(-0.5, 0.5);

  glEnd();

  glFlush(); //forces execution before the gathering is complete
}

void init()
{
  // GFloat red, green, blue, alpha channel
  glClearColor(0, 0, 0, 0);
  // background
  glColor3f(1.0, 0.7, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); // coloca a matriz identidade no topo da pilha
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // usar 1 buffer & true color
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(200, 200);

  glutCreateWindow("Aula 2");
  glutDisplayFunc(display);

  init();
  glutMainLoop();
}

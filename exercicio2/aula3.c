/*
Exercício 3:
praticaCG032018.pptx

----- INSTRUÇÕES DE USO -----
- compilar $ g++ aula3.c -o aula3 -lGL -lGLU -lglut
- executar $ ./aula3
Pressionar as teclas R, G ou B para alterar as intensidades das cores e as interpoladas
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat vermelho;
GLfloat verde;
GLfloat azul;

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(vermelho, verde, azul);
  glBegin(GL_POLYGON);
  glVertex3f(0.25, 0.25, 0.0);
  glColor3f(azul*3/4, vermelho, verde);
  glVertex3f(0.75, 0.25, 0.0);
  glColor3f(verde, azul, vermelho*1/2);
  glVertex3f(0.75, 0.75, 0.0);
  glColor3f(azul*3, verde, vermelho*rand() / (RAND_MAX + 1.0));
  glVertex3f(0.25, 0.75, 0.0);
  glEnd();
  glFlush();
}

void init(void) {
  vermelho = 1.0;
  verde = 1.0;
  azul = 1.0;
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}


void teclado(unsigned char tecla, int x, int y) {
  switch (tecla) {
  case 'R':
  case 'r':
    vermelho = vermelho - 0.1;
    if (vermelho < 0)
      vermelho = 1;
    break;
  case 'G':
  case 'g':
    verde = verde - 0.1;
    if (verde < 0)
      verde = 1;
    break;
  case 'B':
  case 'b':
    azul = azul - 0.1;
    if (azul < 0)
      azul = 1;
    break;
  case 'O':
  case 'o':
    vermelho = 1.0;
    verde = 1.0;
    azul = 1.0;
    break;
  }
  printf("(%.2f, %.2f, %.2f)\n", vermelho, verde, azul);
  glutPostRedisplay();
}

int main(int argc, char ** argv) {
  glutInit( & argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Aula 3 - Exercício 2");
  glutKeyboardFunc(teclado);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

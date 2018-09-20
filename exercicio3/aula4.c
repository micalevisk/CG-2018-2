/*
Exercício 3:

----- INSTRUÇÕES DE USO -----
- compilar $ g++ aula4.c -o aula4 -lGL -lGLU -lglut
- executar $ ./aula4
Pressionar a tecla L para lançar o foguete
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>

GLfloat yLocation = 0;
GLfloat xLocation = 0;
GLfloat zRotationAngle = 0;

float delay = 1.0; // para o controle do tempo
bool animacaoIniciada = false;
int sentido = 1;

/* ======================================= */

void bico() {
  glBegin(GL_TRIANGLES);
  glColor3f(0,1,0);
  glVertex3f(3.0, 6.0, 0);
  glVertex3f(4.0, 8.0, 0);
  glVertex3f(5.0, 6.0, 0);
  glEnd();
}

void corpo() {
  glBegin(GL_QUADS);
  glColor3f(0, 0, 1);
  glVertex3f(3.0, 1.0, 0);
  glVertex3f(5.0, 1.0, 0);
  glVertex3f(5.0, 6.0, 0);
  glVertex3f(3.0, 6.0, 0);
  glEnd();
}

void asaEsquerda() {
  glBegin(GL_TRIANGLES);
  glColor3f(1, 0, 0);
  glVertex3f(1.5, 1.0, 0);
  glVertex3f(3.0, 1.0, 0);
  glVertex3f(3.0, 3.0, 0);
  glEnd();
}

void asaDireita() {
  glBegin(GL_TRIANGLES);
  glColor3f(1, 0, 0);
  glVertex3f(5.0, 1.0, 0);
  glVertex3f(6.5, 1.0, 0);
  glVertex3f(5.0, 3.0, 0);
  glEnd();
}


void desenharFoguete(void) {// display
  fprintf(stderr, "%f\n", yLocation);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  if (animacaoIniciada) {
    if (yLocation >= 4) { // começar a descer
      sentido = -1;
      delay = 1.5;
    }

    glTranslatef(xLocation, yLocation, 0);
    glRotatef(zRotationAngle, 0.0f, 0.0f, 1.0f);
  }

  bico();
  asaEsquerda();
  asaDireita();
  corpo();

  glFlush();
}

/* ======================================= */

void Timer(int value){
  if (!animacaoIniciada || yLocation >= 4.0) return;
  glutTimerFunc(60 * delay, Timer, value);

  /*
  if (yLocation >= 0.3) {
    xLocation += 0.05 * sentido;
    zRotationAngle += -0.05;
  }
  */

  yLocation += 0.05 * sentido;

  glutPostRedisplay(); // §
}


void init(){
  glClearColor(1.0, 1.0, 1.0, 1.0);
  //glColor3f(1.0, 0.0, 0.0);
  //glViewport(0, 0, 240, 240);
  gluOrtho2D(0.0, 160.0, 4.9, 120.0);
}


void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 'l'://lançar
      animacaoIniciada = !animacaoIniciada;
      if (animacaoIniciada) Timer(0);
      break;
      case 27:
      exit(1);
  }
}


int main(int argc, char** argv){
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition(200, 200);
  glutInitWindowSize(700, 500);

  glutCreateWindow("Trab1 - Foguete Animado");
  printf("Pressionar L para lançar o foguete\n");
  init();

  Timer(0);
  glScalef(3, 4, 3);
  glutDisplayFunc(desenharFoguete);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
}
